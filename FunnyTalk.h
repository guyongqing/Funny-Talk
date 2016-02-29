#pragma once

// 系统引用文件
#include <initguid.h>				// GUID
#include <mzfc_inc.h>				// MZFC 头文件
#include <ShellNotifyMsg.h>			// Shell 头文件
#include <UsbNotifyApi.h>			// USB 事件
#include <CallNotifyApi.h>			// 来电事件

// 自定义引用文件
#include "FunnyTalkGame.h"			// 游戏控制
#include "FunnyTalkFile.h"			// 文件操作
#include "FunnyTalkDraw.h"			// 绘制部分
#include "FunnyTalkMouse.h"			// 鼠标控制
#include "FunnyTalkRecorder.h"		// 麦克风控制
#include "FunnyTalkSpeaker.h"		// 扬声器控制
#include "FunnyTalkMixer.h"			// 扬声器控制

// 程序
#define APP_MUTEX_NAME			L"FunnyTalkMutex"
#define APP_WINDOW_TEXT			L"巴拉巴拉"
#define APP_GUID				L"{BF58047B-D21F-44c7-B63B-92806A417811}"
#define APP_VERSION_MAIN		1
#define APP_VERSION_MIDDLE		0
#define APP_VERSION_LAST		0

//************************************************************************************************
//*************************** 主 窗 口 ***********************************************************
//************************************************************************************************

// 主窗口对象
class MyWindow : public CMzWndEx
{

	// MZFC窗口类及派生类的窗口类名声名宏
	MZ_DECLARE_DYNAMIC(MyWindow);

	// 公有成员
	public:

		// 构造函数
		MyWindow(void);
		// 析构函数
		~MyWindow(void);

		// 创建窗口
		bool CreateWindowNow(void);

	// 保护成员
	protected:

		// 初始化
		virtual BOOL OnInitDialog();
		// 当HOME按下时
		virtual int OnShellHomeKey(UINT, WPARAM, LPARAM);
		// 消息处理
		virtual LRESULT MzDefWndProc(UINT, WPARAM, LPARAM);
		// 鼠标双击
		virtual void OnLButtonDblClk(UINT, int, int);
		// 鼠标移动时
		virtual void OnMouseMove(UINT, int, int);		
		// 鼠标抬起时
		virtual void OnLButtonUp(UINT, int, int);
		// 鼠标按下时
		virtual void  OnLButtonDown(UINT, int, int);

	// 私有成员
	private:



};

//************************************************************************************************
//*************************** 主 程 序 ***********************************************************
//************************************************************************************************


// 从 CMzApp 派生的应用程序类
class MyApp : public CMzApp
{

	// 公有成员
	public:

		// 构造函数
		MyApp(void);
		// 析构函数
		~MyApp(void);

	// 保护成员
	protected:

		// 初始化
		virtual BOOL Init(void);
		// 运行
		// virtual int Run(void);
		// 停止
		virtual int Done(void);


	// 私有成员
	private:

		// 单例判断
		bool IsAppRunning(void);
		// 消息处理
		void MessageRegister(void);

};