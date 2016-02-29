// FunnyTalk.cpp : 定义应用程序的入口点。
//

// 预编译
#include "stdafx.h"
// 头文件
#include "FunnyTalk.h"

// 全局应用程序对象
MyApp TheApp;

// 主窗口
MyWindow TheWindow;

// 窗口全局变量
HWND	TheHwnd;

// USB 处理
int TheUsbNotify;
// 来电处理
UINT TheCallNotify;
// 短信处理
UINT TheSmsNotify;
// 彩信处理
UINT TheMmsNotify;
// 蓝牙处理
UINT TheBlueToothNotify;

// 来电消息
DWORD TheCallMessage;
// 短信消息
DWORD TheSmsMessage;
// 彩信消息
DWORD TheMmsMessage;

// 收费验证
bool TheLicenseVerify = false;

// MZFC窗口类及派生类的窗口类名定义宏
MZ_IMPLEMENT_DYNAMIC(MyWindow)

//************************************************************************************************
//*************************** 主 窗 口 ***********************************************************
//************************************************************************************************

// 构造函数
MyWindow::MyWindow(void)
{
}

// 析构函数
MyWindow::~MyWindow(void)
{
}

// 初始化
BOOL MyWindow::OnInitDialog()
{
	
	// 必须先执行父对象的初始化方法
	if (!CMzWndEx::OnInitDialog())
	{
		return false;
	}

	// 成功
	return true;

}

// 当HOME键被按下时
int MyWindow::OnShellHomeKey(UINT message, WPARAM wParam, LPARAM lParam)
{

	// 默认退出
	return SHK_RET_DEFAULT;

}

// 鼠标双击
void MyWindow::OnLButtonDblClk(UINT fwKeys, int xPos, int yPos)
{

	// 处理鼠标事件
	MouseClick(xPos,yPos);

}

// 鼠标抬起时
void MyWindow::OnLButtonUp(UINT fwKeys, int xPos, int yPos) 
{

	// 处理鼠标事件
	MouseUp(xPos,yPos);

}

// 鼠标移动时
void MyWindow::OnMouseMove(UINT fwKeys, int xPos, int yPos) 
{

	// 处理鼠标事件
	MouseMove(xPos,yPos);

}

// 鼠标按下时
void  MyWindow::OnLButtonDown(UINT fwKeys, int xPos, int yPos) 
{

	// 处理鼠标事件
	MouseDown(xPos,yPos);

}

// 消息处理
LRESULT MyWindow::MzDefWndProc(UINT message, WPARAM  wParam, LPARAM  lParam) 
{

	// 某些状态
	int id = int(lParam);

	// 处理消息
	switch(message){

		// 混音控制事件
		case MM_MIXM_CONTROL_CHANGE:
			// 耳机状态有变化
			if((id==HEADPHONE_MODE_CHANGE_CONTROL_ID)||(id==CHANGE_HEADPHONE_TYPE_CONTROL_ID)){		
				// 设置混音器状态
				MixerModeSetting();
			}
			break;

		// 处理键盘事件
		case WM_KEYUP:

			// 降低音量		
			if(wParam==VK_VOLUME_DOWN){				
				// 混音器音量降低
				MixerVolumeDown(SOUND_VOLUME_STEP);
			}

			// 音量升高
			if(wParam==VK_VOLUME_UP){				
				// 混音器音量升高
				MixerVolumeUp(SOUND_VOLUME_STEP);
				break;

			}
			break;

		// 得到焦点
		case WM_SETFOCUS:
			
			// 激活游戏
			GameLive();
			break;

		// 失去焦点	
		case WM_KILLFOCUS:

			// 停止游戏
			GameDead();
			break;

		// 任务管理器消息
		case MZ_WM_TASKMAN_ONOFF:

			// 显示任务管理器消息
			if(lParam==TASKMAN_SHOW_WND){
				// 停止游戏
				GameDead();
			}

			// 从任务栏激活
			if(lParam==TASKMAN_EXEC_PROG){
				// 激活游戏
				GameLive();				
			}

			// 隐藏任务管理器消息
			if(lParam==TASKMAN_QUIT_WND){
				if (GetForegroundWindow()==m_hWnd){
					// 激活游戏
					GameLive();					
				}
			}
			break;

		
		// 数据满
		case MM_WIM_DATA: 
			
			// 处理音频数据
			RecorderData(message, wParam, lParam);
			// 重绘窗口
			GameRun();
			break;


		// 设备打开
		case MM_WIM_OPEN: 

			// 处理设备打开
			RecorderOpen(message, wParam, lParam);
			break;

		// 设备关闭
		case MM_WIM_CLOSE: 

			// 处理设备关闭
			RecorderClose(message, wParam, lParam);
			break;

		// 播放完毕
		case MM_WOM_DONE: 
			
			// 处理完毕状态
			SpeakerDone(message, wParam, lParam);			
			break;


		// 设备打开
		case MM_WOM_OPEN: 

			// 处理设备打开
			SpeakerOpen(message, wParam, lParam);
			break;

		// 设备关闭
		case MM_WOM_CLOSE: 

			// 处理设备关闭
			SpeakerClose(message, wParam, lParam);
			break;

	}

	// 来电事件,短消息事件,彩信事件
	if((message==TheCallNotify)||(message==TheSmsNotify)||(message==TheMmsNotify)){
	
		// 有系统消息
		MixerSetMessage(true);

	}

	// 来电消息,短消息消息,彩信消息
	if((message==TheCallMessage)||(message==TheSmsMessage)||(message==TheMmsMessage)){
	
		// 有系统消息
		MixerSetMessage(true);

	}

	// U盘事件
	if(message==TheUsbNotify){

		// U盘接入
		if(wParam==USB_MASSSTORAGE_ATTACH){
			PostQuitMessage(0);
		}
	
	}

	// 蓝牙事件
	if(message==TheBlueToothNotify){

		// 停止游戏
		PostQuitMessage(0);
	
	}

	// 返回系统默认消息处理结果
	return CMzWndEx::MzDefWndProc(message,wParam,lParam);

}

// 创建窗口
bool MyWindow::CreateWindowNow(void)
{

	// 创建主窗口
	Create(0,0,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT, 0, 0, 0);
	SetWindowText(APP_WINDOW_TEXT);
	SetBgColor(DRAW_COLOR_WHITE);

	// 窗口动画效果
	if(MzGetParam(MZGP_APP_START_ANIMATION)){
		AnimateWindow(MZ_ANIMTYPE_ZOOM_IN,true);
	}

	// 显示主窗口
	Show();

	// 窗口句柄
	TheHwnd = m_hWnd;

	if(TheHwnd<=0){
		return false;
	}

	return true;

}

//************************************************************************************************
//*************************** 主 程 序 ***********************************************************
//************************************************************************************************


// 构造函数
MyApp::MyApp(void)
{
}

// 析构函数
MyApp::~MyApp(void)
{
}

// 消息处理
void MyApp::MessageRegister(void)
{

	// 注册USB消息
	TheUsbNotify = RegisterUsbNotifyMsg();

	// 来电事件
	TheCallNotify = RegisterWindowMessage(WM_CALL_MESSAGE);
	// 短消息事件
	TheSmsNotify = RegisterWindowMessage(WM_SMS_MESSAGE);
	// 彩信事件
	TheMmsNotify = RegisterWindowMessage(WM_MMS_MESSAGE);
	// 蓝牙事件
	TheBlueToothNotify = RegisterWindowMessage(WM_BT_MESSAGE);

	// 来电消息
	TheCallMessage = GetCallRegisterMessage();
	// 短信消息
	TheSmsMessage = GetSmsRegisterMessage();
	// 彩信消息
	TheMmsMessage = GetMmsRegisterMessage();

}

// 单例判断
bool MyApp::IsAppRunning(void)
{

	//检测是否已经有另外的实例在运行中:
    bool bFound = false;

	// 获取句柄
    HANDLE hMutexOneInstantance = CreateMutex(NULL, true, APP_MUTEX_NAME);

	// 找到实例
	if (GetLastError()==ERROR_ALREADY_EXISTS){
		bFound = true;
	}

	// 释放句柄
    if(hMutexOneInstantance){
		ReleaseMutex(hMutexOneInstantance);
    }

	// 如果找到实例
	if(bFound){
		
		//激活已经在运行的实例的窗口   
		HWND pwndFirst = FindWindow((LPCTSTR)MyWindow::m_pwszMyWindowClassName, (LPCTSTR)NULL);

		// 已经找到窗口实例
		if(pwndFirst){

			// 如果窗口被隐藏
            if(!IsWindowVisible(pwndFirst)){
				// 显示窗口
				ShowWindow(pwndFirst, SW_SHOW);
            }

			// 激活窗口
			SetForegroundWindow(pwndFirst);

			// 已经存在
			return true;

        }

	}

	// 返回状态
	return false;

}

// 初始化
BOOL MyApp::Init(void)
{

	// 如果已经运行
	if(IsAppRunning()){
		return false;
	}

	// 注册COM
	CoInitializeEx(0, COINIT_MULTITHREADED);
	
	// 窗口创建失败
	if(!TheWindow.CreateWindowNow()){
		return false;
	}

	// 注册各种消息
	MessageRegister();

	// 获取当前程序运行目录
	FileGetPath();

	// 初始化游戏失败
	if(!GameInit(TheHwnd)){
		GameError(GAME_ERROR_INIT);
	}

	// 成功
	return true;

}

// 完成
int MyApp::Done(void)
{

	// 窗口有创建
	if(TheHwnd){

		// 游戏结束
		GameEnd();

	}

	// 调用基类方法
	return  CMzApp::Done();

}