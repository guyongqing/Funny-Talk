#pragma once

// ¼������
#include "FunnyTalkRecorder.h"
// ��ͼ����
#include "FunnyTalkDraw.h"

// һЩ��������
#define	SPEAKER_DEVICE_COUNT		4			// ����������
#define SPEAKER_SAMPLE_WIDTH		8			// �������
#define SPEAKER_CHANNEL_COUNT		1			// ������
#define SPEAKER_BLOCK_ALIGN			1			// ÿ���������ֽ���

//************************************************************************************************
//*************************** �� �� �� ��   ******************************************************
//************************************************************************************************

// ��ʼ��������
bool SpeakerInit(HWND);
// ������������
void SpeakerEnd(void);
// ���������豸ǰ�Բ�����������
void SpeakerSetParameter(int, WORD, DWORD, WORD, WORD, WORD, DWORD);
// ��������
void SpeakerPlay(BYTE*, int, HWND);
// �������״̬
void SpeakerDone(UINT, WPARAM, LPARAM);
// �豸��
void SpeakerOpen(UINT, WPARAM, LPARAM);
// �豸�ر�
void SpeakerClose(UINT, WPARAM, LPARAM);