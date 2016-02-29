
// 预编译
#include "stdafx.h"
// 头文件
#include "FunnyTalkMouse.h"
#include "FunnyTalkGame.h"

//************************************************************************************************
//*************************** 鼠标处理 ***********************************************************
//************************************************************************************************

// 鼠标坐标
int TheMouseLocationX = 0;
int TheMouseLocationY = 0;

/************************ 鼠标双击时 **********************************/

// 鼠标双击时
void MouseClick(int x, int y)
{

}

/************************ 鼠标移动时 **********************************/

// 鼠标移动时
void MouseMove(int x, int y)
{

	// 判断是否点中菜单
	DrawSetMenuIndex(x,y,false);	

}

/************************ 鼠标抬起时 **********************************/

// 鼠标抬起时
void MouseUp(int x, int y)
{

	// 清除菜单选中状态
	DrawSetMenuIndex(x,y,true);

	// 不是水平滑动
	if(abs(y-TheMouseLocationY)>200){
		return;
	}

	// 滑动不够长
	if(abs(x-TheMouseLocationX)<200){
		return;
	}

	// 向右滑动
	if(x>TheMouseLocationX){
		DrawNext(1);
	// 向左滑动
	}else{
		DrawNext(-1);
	}

}

/************************ 鼠标按下时 **********************************/

// 鼠标按下时
void MouseDown(int x, int y)
{

	// 复制坐标
	TheMouseLocationX = x;
	TheMouseLocationY = y;

	// 激活游戏
	if(!GameIsLive()){
		GameLive();		
	}

	// 判断是否点中菜单
	DrawSetMenuIndex(x,y,false);

}