#pragma once

// ������
#include <IMixer.h>
#include <IMixer_GUID.h>

// ��������
#define	SOUND_VOLUME_DEFAULT	20			// Ĭ������
#define SOUND_VOLUME_MIN		0			// ��С����
#define SOUND_VOLUME_MAX		100			// �������
#define SOUND_VOLUME_STEP		10			// ��������

//************************************************************************************************
//*************************** �������� ***********************************************************
//************************************************************************************************

// ��ʼ��������
bool MixerInit(HWND);
// ��������������
void MixerVolumeDown(int);
// ��������������
void MixerVolumeUp(int);
// ����״̬����
void MixerModeSetting(void);
// �ͷŻ���������
void MixerEnd(void);
// �����Ƿ���ϵͳ��Ϣ
void MixerSetMessage(bool);		
// ��ȡ��ǰ����
int MixerGetVolume(void);