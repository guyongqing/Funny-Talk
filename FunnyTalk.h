#pragma once

// ϵͳ�����ļ�
#include <initguid.h>				// GUID
#include <mzfc_inc.h>				// MZFC ͷ�ļ�
#include <ShellNotifyMsg.h>			// Shell ͷ�ļ�
#include <UsbNotifyApi.h>			// USB �¼�
#include <CallNotifyApi.h>			// �����¼�

// �Զ��������ļ�
#include "FunnyTalkGame.h"			// ��Ϸ����
#include "FunnyTalkFile.h"			// �ļ�����
#include "FunnyTalkDraw.h"			// ���Ʋ���
#include "FunnyTalkMouse.h"			// ������
#include "FunnyTalkRecorder.h"		// ��˷����
#include "FunnyTalkSpeaker.h"		// ����������
#include "FunnyTalkMixer.h"			// ����������

// ����
#define APP_MUTEX_NAME			L"FunnyTalkMutex"
#define APP_WINDOW_TEXT			L"��������"
#define APP_GUID				L"{BF58047B-D21F-44c7-B63B-92806A417811}"
#define APP_VERSION_MAIN		1
#define APP_VERSION_MIDDLE		0
#define APP_VERSION_LAST		0

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************

// �����ڶ���
class MyWindow : public CMzWndEx
{

	// MZFC�����༰������Ĵ�������������
	MZ_DECLARE_DYNAMIC(MyWindow);

	// ���г�Ա
	public:

		// ���캯��
		MyWindow(void);
		// ��������
		~MyWindow(void);

		// ��������
		bool CreateWindowNow(void);

	// ������Ա
	protected:

		// ��ʼ��
		virtual BOOL OnInitDialog();
		// ��HOME����ʱ
		virtual int OnShellHomeKey(UINT, WPARAM, LPARAM);
		// ��Ϣ����
		virtual LRESULT MzDefWndProc(UINT, WPARAM, LPARAM);
		// ���˫��
		virtual void OnLButtonDblClk(UINT, int, int);
		// ����ƶ�ʱ
		virtual void OnMouseMove(UINT, int, int);		
		// ���̧��ʱ
		virtual void OnLButtonUp(UINT, int, int);
		// ��갴��ʱ
		virtual void  OnLButtonDown(UINT, int, int);

	// ˽�г�Ա
	private:



};

//************************************************************************************************
//*************************** �� �� �� ***********************************************************
//************************************************************************************************


// �� CMzApp ������Ӧ�ó�����
class MyApp : public CMzApp
{

	// ���г�Ա
	public:

		// ���캯��
		MyApp(void);
		// ��������
		~MyApp(void);

	// ������Ա
	protected:

		// ��ʼ��
		virtual BOOL Init(void);
		// ����
		// virtual int Run(void);
		// ֹͣ
		virtual int Done(void);


	// ˽�г�Ա
	private:

		// �����ж�
		bool IsAppRunning(void);
		// ��Ϣ����
		void MessageRegister(void);

};