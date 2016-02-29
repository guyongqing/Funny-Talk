
// 预编译
#include "stdafx.h"

// 自定义头文件
#include "FunnyTalkGame.h"

// 窗口句柄
HWND TheGameHwnd;

// 游戏全局变量
bool TheGameLive = false;		// 游戏活动状态
bool TheGamePause = false;		// 游戏暂停状态

// 当前游戏状态
int TheGameStatus = GAME_STATUS_START;

//************************************************************************************************
//*************************** 游 戏 控 制 ********************************************************
//************************************************************************************************

// 游戏错误
void GameError(LPTSTR msg)
{

	// 游戏暂停
	GamePause();

	// 游戏结束
	GameEnd();

	// 显示错误信息
	MzMessageBox(0,msg,GAME_ERROR,MB_OK,0,false);

	// 退出程序
	PostQuitMessage(0);

}

// 游戏初始化
bool GameInit(HWND hwnd)
{

	// 窗口没有正确创建
	if(!hwnd){
		return false;
	}

	// 窗口句柄
	TheGameHwnd = hwnd;

	// 初始化 DirectDraw 失败
	if(!DirectDrawInit(hwnd)){
		return false;
	}

	// 录音机对象创建失败
	if(!RecorderInit(hwnd)){		
		return false;
	}

	// 扬声器对象创建失败
	if(!SpeakerInit(hwnd)){
		return false;
	}

	// 创建混音设备
	if(!MixerInit(hwnd)){
		return false;
	}

	// 图形初始化失败
	if(!DrawInit()){
		return false;
	}

	// 初始化成功，进入显示标志过程
	GameStatus(GAME_STATUS_RUN);

	// 激活游戏
	GameLive();

	// 返回成功
	return true;

}

// 游戏开始
void GameRun(void)
{

	// 游戏处于激活状态
	if(TheGameLive){

		// 保存到总缓存
		RecorderSaveToBuffer();

		// 重绘窗口
		Draw();

	}

}

// 继续游戏
void GameContinue(void)
{

	// 暂停游戏
	TheGamePause = false;

}		

// 暂停游戏
void GamePause(void)
{

	// 暂停游戏
	TheGamePause = true;	

}

// 停止游戏
void GameDead(void)
{

	// 解除SHELL捕获音量控制键
	UnHoldShellUsingSomeKeyFunction(TheGameHwnd, MZ_HARDKEY_VOLUME_UP | MZ_HARDKEY_VOLUME_DOWN);	
	// 混音器状态设置
	MixerModeSetting();
	// 关闭游戏状态
	TheGameLive = false;	
	// 暂停游戏
	GamePause();	
	// 停止录音
	RecorderStop();

}

// 游戏结束
void GameEnd(void)
{

	// 停止游戏
	GameDead();	
	// 绘图结束
	DrawEnd();	
	// 结束声音播放
	SpeakerEnd();
	// 结束录音
	RecorderEnd();
	// 销毁 DDraw 对象
	DirectDrawEnd();	
	// 释放混音器对象
	MixerEnd();

}

// 游戏激活
void GameLive(void)
{

	// 窗口句柄
	if(TheGameHwnd>0){
		
		// 阻止SHELL捕获音量控制键
		HoldShellUsingSomeKeyFunction(TheGameHwnd, MZ_HARDKEY_VOLUME_UP | MZ_HARDKEY_VOLUME_DOWN);
		// 没有系统消息
		MixerSetMessage(false);		
		// 混音器状态设置
		MixerModeSetting();
		// 打开游戏状态
		TheGameLive = true;		
		// 开始录音
		RecorderStart();
		
	}

}

// 设置游戏状态
void GameStatus(int s)
{

	// 设置游戏状态
	TheGameStatus = s;

}

// 是否激活
bool GameIsLive(void)
{

	return TheGameLive;

}