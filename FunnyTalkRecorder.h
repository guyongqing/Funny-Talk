#pragma once

// ϵͳ¼����
#include	<IRecorder.h>
#include	<IRecorder_Guid.h>

// ��������
#include	"FunnyTalkSpeaker.h"
// ��ͼ����
#include	"FunnyTalkDraw.h"

// ��ʼ����
#define RECORDER_SAMPLE_WIDTH		8			// �������
#define RECORDER_SAMPLE_RATE		11025		// ������
#define RECORDER_BYTES_PER_SEC		11025		// ÿ������ֽ���
#define RECORDER_CHANNEL_COUNT		1			// ������
#define RECORDER_BLOCK_ALIGN		1			// ÿ���������ֽ���
#define RECORDER_BUFFER_SIZE		512			// ��������С
#define RECORDER_BUFFER_STEP		916			// ���������
#define RECORDER_BUFFER_COUNT		4			// ����������
#define RECORDER_BUFFER_TOTAL		220500		// �ܻ�����
#define RECORDER_BUFFER_END			220499		// �ܻ���������

// ״̬����
#define RECORDER_STATUS_INPUT		0			// ¼��
#define RECORDER_STATUS_PLAY		1			// ����

// ��������
#define RECORDER_WAVE_MIN			0			// ��Сֵ
#define RECORDER_WAVE_MID			128			// �м�ֵ
#define RECORDER_WAVE_MAX			255			// ���ֵ

#define RECORDER_WAVE_MUTE			10			// ������׼
#define RECORDER_WAVE_TIME			15			// ����ʱ��
#define RECORDER_WAVE_LONG			5120		// ���ٲ��ű�׼

//************************************************************************************************
//*************************** ¼ �� ��   *********************************************************
//************************************************************************************************

// ¼������ʼ��
bool RecorderInit(HWND);
// ��¼���豸ǰ�Բ�����������
void RecorderSetParameter(WORD, DWORD, WORD, WORD, WORD, DWORD);
// ��ʼ¼��
void RecorderStart(void);
// ֹͣ¼��
void RecorderStop(void);
// ��ͣ¼��
void RecorderPause(void);
// ����¼��
void RecorderEnd(void);
// ���浽�ܻ���
void RecorderSaveToBuffer(void);
// ����¼��
void RecorderReset(void);
// ������Ƶ����
void RecorderData(UINT, WPARAM, LPARAM);
// �豸��
void RecorderOpen(UINT, WPARAM, LPARAM);
// �豸�ر�
void RecorderClose(UINT, WPARAM, LPARAM);