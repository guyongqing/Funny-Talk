#pragma once

// Ԥ����
#include "stdafx.h"

// ¼����
#include "FunnyTalkRecorder.h"
// ͼ�ο���
#include "FunnyTalkDraw.h"

// ȫ������������
HWAVEOUT		TheSpeakerWaveOut[SPEAKER_DEVICE_COUNT];
// �����ṹ
WAVEFORMATEX	TheSpeakerWaveFormat[SPEAKER_DEVICE_COUNT];
// �������
WAVEHDR		TheSpeakerWaveHandle[SPEAKER_DEVICE_COUNT];

// ������
DWORD			TheSpeakerWaveSampleRate[SPEAKER_DEVICE_COUNT] = {21000,9000,14000,18000};
// ÿ�������
DWORD			TheSpeakerWaveBytePerSec[SPEAKER_DEVICE_COUNT] = {21000,9000,14000,18000};

//************************************************************************************************
//*************************** �� �� �� ��   ******************************************************
//************************************************************************************************

// ��ʼ��������
bool SpeakerInit(HWND hwnd)
{

	// �����豸
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// ���������豸ǰ�Բ�����������
		SpeakerSetParameter(i,SPEAKER_SAMPLE_WIDTH,TheSpeakerWaveSampleRate[i],SPEAKER_CHANNEL_COUNT,WAVE_FORMAT_PCM,SPEAKER_BLOCK_ALIGN,TheSpeakerWaveBytePerSec[i]);

		// ���������豸ʧ��
		if(waveOutOpen(&TheSpeakerWaveOut[i],WAVE_MAPPER,&TheSpeakerWaveFormat[i],(DWORD)hwnd,NULL,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
			return false;
		}

	}

	// ������
	return true;

}

// ������������
void SpeakerEnd(void)
{

	// �����豸
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// ֹͣ����
		waveOutReset(TheSpeakerWaveOut[i]);	

		// �ر��豸
		waveOutClose(TheSpeakerWaveOut[i]);

	}

}

// ���������豸ǰ�Բ�����������
void SpeakerSetParameter(int spkDevice, WORD sampleWidth, DWORD sampleRate, WORD channelCount, WORD dataType, WORD blockAlign, DWORD bytesPerSec)
{

	// ��Ƶ��ʽ����
	TheSpeakerWaveFormat[spkDevice].wFormatTag = dataType;
	// ������
	TheSpeakerWaveFormat[spkDevice].nChannels = channelCount;
	// ����Ƶ��
	TheSpeakerWaveFormat[spkDevice].nSamplesPerSec = sampleRate;
	// �������
	TheSpeakerWaveFormat[spkDevice].wBitsPerSample = sampleWidth;
	// ÿ���������ֽ���
	TheSpeakerWaveFormat[spkDevice].nBlockAlign = blockAlign;
	// ÿ��ɼ����ֽ���
	TheSpeakerWaveFormat[spkDevice].nAvgBytesPerSec = bytesPerSec;

}

// ��������
void SpeakerPlay(BYTE* data, int length, HWND hwnd)
{

	// ��ȡ��ǰ������
	int baby = DrawGetBabyIndex();
	

	/*// �����ڴ���
	TheSpeakerWaveHandle=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));*/

	// �����������ṹ
	TheSpeakerWaveHandle[baby].lpData = (LPSTR)data;	
	TheSpeakerWaveHandle[baby].dwBufferLength = length;
	TheSpeakerWaveHandle[baby].dwBytesRecorded = 0;
	TheSpeakerWaveHandle[baby].dwUser = 0;
	TheSpeakerWaveHandle[baby].dwFlags = 0;
	TheSpeakerWaveHandle[baby].dwLoops = 1;
	TheSpeakerWaveHandle[baby].lpNext = NULL;
	TheSpeakerWaveHandle[baby].reserved = 0;

	// ׼��������
	waveOutPrepareHeader(TheSpeakerWaveOut[baby],&TheSpeakerWaveHandle[baby],sizeof(WAVEHDR));
	// �������
	waveOutWrite(TheSpeakerWaveOut[baby],&TheSpeakerWaveHandle[baby],sizeof(WAVEHDR)); 

}

// �������״̬
void SpeakerDone(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// �����豸
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// ֹͣ����
		waveOutReset(TheSpeakerWaveOut[i]);	

	}

	// ������ϣ����¿�ʼ¼��
	RecorderReset();

}

// �豸��
void SpeakerOpen(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	

}

// �豸�ر�
void SpeakerClose(UINT message, WPARAM  wParam, LPARAM  lParam)
{
	
	// �����豸
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// �ͷŻ�����	
		waveOutUnprepareHeader(TheSpeakerWaveOut[i], &TheSpeakerWaveHandle[i],sizeof(WAVEHDR));

		// �ͷ��ڴ�
		if(&TheSpeakerWaveHandle[i]){
			free(&TheSpeakerWaveHandle[i]);
		}

	}

}