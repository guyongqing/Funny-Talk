
// Ԥ����
#include "stdafx.h"

// �Զ���ͷ�ļ�
#include "FunnyTalkGame.h"

// ���ھ��
HWND TheGameHwnd;

// ��Ϸȫ�ֱ���
bool TheGameLive = false;		// ��Ϸ�״̬
bool TheGamePause = false;		// ��Ϸ��ͣ״̬

// ��ǰ��Ϸ״̬
int TheGameStatus = GAME_STATUS_START;

//************************************************************************************************
//*************************** �� Ϸ �� �� ********************************************************
//************************************************************************************************

// ��Ϸ����
void GameError(LPTSTR msg)
{

	// ��Ϸ��ͣ
	GamePause();

	// ��Ϸ����
	GameEnd();

	// ��ʾ������Ϣ
	MzMessageBox(0,msg,GAME_ERROR,MB_OK,0,false);

	// �˳�����
	PostQuitMessage(0);

}

// ��Ϸ��ʼ��
bool GameInit(HWND hwnd)
{

	// ����û����ȷ����
	if(!hwnd){
		return false;
	}

	// ���ھ��
	TheGameHwnd = hwnd;

	// ��ʼ�� DirectDraw ʧ��
	if(!DirectDrawInit(hwnd)){
		return false;
	}

	// ¼�������󴴽�ʧ��
	if(!RecorderInit(hwnd)){		
		return false;
	}

	// ���������󴴽�ʧ��
	if(!SpeakerInit(hwnd)){
		return false;
	}

	// ���������豸
	if(!MixerInit(hwnd)){
		return false;
	}

	// ͼ�γ�ʼ��ʧ��
	if(!DrawInit()){
		return false;
	}

	// ��ʼ���ɹ���������ʾ��־����
	GameStatus(GAME_STATUS_RUN);

	// ������Ϸ
	GameLive();

	// ���سɹ�
	return true;

}

// ��Ϸ��ʼ
void GameRun(void)
{

	// ��Ϸ���ڼ���״̬
	if(TheGameLive){

		// ���浽�ܻ���
		RecorderSaveToBuffer();

		// �ػ洰��
		Draw();

	}

}

// ������Ϸ
void GameContinue(void)
{

	// ��ͣ��Ϸ
	TheGamePause = false;

}		

// ��ͣ��Ϸ
void GamePause(void)
{

	// ��ͣ��Ϸ
	TheGamePause = true;	

}

// ֹͣ��Ϸ
void GameDead(void)
{

	// ���SHELL�����������Ƽ�
	UnHoldShellUsingSomeKeyFunction(TheGameHwnd, MZ_HARDKEY_VOLUME_UP | MZ_HARDKEY_VOLUME_DOWN);	
	// ������״̬����
	MixerModeSetting();
	// �ر���Ϸ״̬
	TheGameLive = false;	
	// ��ͣ��Ϸ
	GamePause();	
	// ֹͣ¼��
	RecorderStop();

}

// ��Ϸ����
void GameEnd(void)
{

	// ֹͣ��Ϸ
	GameDead();	
	// ��ͼ����
	DrawEnd();	
	// ������������
	SpeakerEnd();
	// ����¼��
	RecorderEnd();
	// ���� DDraw ����
	DirectDrawEnd();	
	// �ͷŻ���������
	MixerEnd();

}

// ��Ϸ����
void GameLive(void)
{

	// ���ھ��
	if(TheGameHwnd>0){
		
		// ��ֹSHELL�����������Ƽ�
		HoldShellUsingSomeKeyFunction(TheGameHwnd, MZ_HARDKEY_VOLUME_UP | MZ_HARDKEY_VOLUME_DOWN);
		// û��ϵͳ��Ϣ
		MixerSetMessage(false);		
		// ������״̬����
		MixerModeSetting();
		// ����Ϸ״̬
		TheGameLive = true;		
		// ��ʼ¼��
		RecorderStart();
		
	}

}

// ������Ϸ״̬
void GameStatus(int s)
{

	// ������Ϸ״̬
	TheGameStatus = s;

}

// �Ƿ񼤻�
bool GameIsLive(void)
{

	return TheGameLive;

}