#pragma once

// Ԥ����
#include "stdafx.h"

// ¼������
#include "FunnyTalkRecorder.h"

// ���ھ��
HWND			TheRecorderHwnd;

// �����ṹ
WAVEFORMATEX	TheRecorderWaveFormat;

// �����豸���
HWAVEIN			TheRecorderWaveIn;

// ������
BYTE			TheRecorderBuffer[RECORDER_BUFFER_COUNT][RECORDER_BUFFER_SIZE];

// ���ݱ���
BYTE			TheRecorderWaveData[RECORDER_BUFFER_SIZE];

// �ܻ���
BYTE			TheRecorderBufferTotal[RECORDER_BUFFER_TOTAL];

// �������
PWAVEHDR		TheRecorderWaveHandle[RECORDER_BUFFER_COUNT];

// ϵͳ¼��������
IRecord*		TheRecorder;

// �Ƿ���¼��״̬
bool	TheRecorderStatus = false;

// ��ǰ�ܻ���λ��
int		TheRecorderBufferIndex = 0;
// ��ǰ¼���ɼ�״̬
int		TheRecorderInputStatus = RECORDER_STATUS_INPUT;
// �ɼ�����
int		TheRecorderCount = 0;

//************************************************************************************************
//*************************** ¼ �� ��   *********************************************************
//************************************************************************************************

// ¼������ʼ��
bool RecorderInit(HWND hwnd)
{

	// ע��¼����COM����
	if(FAILED( CoCreateInstance(CLSID_Recorder,NULL,CLSCTX_INPROC_SERVER,IID_MZ_Record,(void **)&TheRecorder))){
      return false;
    }

	// �趨�ص�����
	TheRecorder->SetCallBackWindow(hwnd, RECORDER_MODE);

	// �ͷ�ϵͳ¼����
	if(TheRecorder){
		TheRecorder->Release();
	}

	// ׼������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// ���뻺����
		ZeroMemory(TheRecorderBuffer[i],RECORDER_BUFFER_SIZE);
		// ������������ڴ�
		TheRecorderWaveHandle[i]=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));

	}

	// ��ʼ�������ṹ
	RecorderSetParameter(RECORDER_SAMPLE_WIDTH,RECORDER_SAMPLE_RATE,RECORDER_CHANNEL_COUNT,WAVE_FORMAT_PCM, RECORDER_BLOCK_ALIGN, RECORDER_BYTES_PER_SEC);

	// ��¼���豸ʧ��
	if(waveInOpen(&TheRecorderWaveIn,WAVE_MAPPER,&TheRecorderWaveFormat,(DWORD)hwnd,NULL,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
		return false;
	}

	// ��ʼ���������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// �����������ṹ
		TheRecorderWaveHandle[i]->lpData = (LPSTR)TheRecorderBuffer[i];	
		TheRecorderWaveHandle[i]->dwBufferLength = RECORDER_BUFFER_SIZE;
		TheRecorderWaveHandle[i]->dwBytesRecorded = 0;
		TheRecorderWaveHandle[i]->dwUser = 0;
		TheRecorderWaveHandle[i]->dwFlags = 0;
		TheRecorderWaveHandle[i]->dwLoops = 1;
		TheRecorderWaveHandle[i]->lpNext = NULL;
		TheRecorderWaveHandle[i]->reserved = 0;

		// ׼��������
		waveInPrepareHeader(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof(WAVEHDR));
		// ��ӻ�����
		waveInAddBuffer(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof (WAVEHDR)) ;

	}

	// �����������
	ZeroMemory(TheRecorderWaveData,RECORDER_BUFFER_SIZE);

	// ���ô��ھ��
	TheRecorderHwnd = hwnd;

	// ������
	return true;

}

// ��¼���豸ǰ�Բ�����������
void RecorderSetParameter(WORD sampleWidth, DWORD sampleRate, WORD channelCount, WORD dataType, WORD blockAlign, DWORD bytesPerSec)
{

	// ��Ƶ��ʽ����
	TheRecorderWaveFormat.wFormatTag = dataType;
	// ������
	TheRecorderWaveFormat.nChannels = channelCount;
	// ����Ƶ��
	TheRecorderWaveFormat.nSamplesPerSec = sampleRate;
	// �������
	TheRecorderWaveFormat.wBitsPerSample = sampleWidth;
	// ÿ���������ֽ���
	TheRecorderWaveFormat.nBlockAlign = blockAlign;
	// ÿ��ɼ����ֽ���
	TheRecorderWaveFormat.nAvgBytesPerSec = bytesPerSec;

}

// ��ʼ¼��
void RecorderStart(void)
{

	// ��ʼ¼��
	waveInStart(TheRecorderWaveIn);

	// ����Ϊ¼��״̬
	TheRecorderInputStatus = RECORDER_STATUS_INPUT;

}

// ֹͣ¼��
void RecorderStop(void)
{

	// ��Ϊ����״̬
	TheRecorderInputStatus = RECORDER_STATUS_PLAY;

}

// ����¼��
void RecorderEnd(void)
{

	// ֹͣ¼��
	waveInReset(TheRecorderWaveIn);	

	// �ر��豸
	waveInClose(TheRecorderWaveIn);

	// �ͷ��������
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		if(TheRecorderWaveHandle[i]){free(TheRecorderWaveHandle[i]);}
	}

}

// ���浽�ܻ���
void RecorderSaveToBuffer(void)
{

	// ����ǲ���״̬
	if(TheRecorderInputStatus==RECORDER_STATUS_PLAY){
		return;
	}

	// ������־
	int i = 0;
	int min = RECORDER_WAVE_MID;
	int max = RECORDER_WAVE_MID;

	// ��ȡ��ǰ��������
	for(i=0;i<RECORDER_BUFFER_SIZE;i++){

		// ��������
		TheRecorderBufferTotal[TheRecorderBufferIndex] = TheRecorderWaveData[i];

		// ��¼��һ����Ϣ
		TheRecorderBufferIndex++;

		// ��������
		if(TheRecorderBufferIndex>RECORDER_BUFFER_END){
			TheRecorderBufferIndex = RECORDER_BUFFER_END;
			break;
		}

		// ��Сֵ
		if(TheRecorderWaveData[i]<min){
			min = TheRecorderWaveData[i];
		}

		// ���ֵ
		if(TheRecorderWaveData[i]>max){
			max = TheRecorderWaveData[i];
		}

	}

	// ������
	if((max-min)>RECORDER_WAVE_MUTE){

		// ����
		TheRecorderCount = 0;

		// �Ѿ�����
		if(TheRecorderBufferIndex==RECORDER_BUFFER_END){

			// ��Ϊ����״̬
			TheRecorderInputStatus = RECORDER_STATUS_PLAY;
			// ���ó���״̬
			DrawSetBabyStatus(DRAW_BABY_STATUS_SPEAK);
			// ��������
			SpeakerPlay(TheRecorderBufferTotal+RECORDER_BUFFER_STEP,TheRecorderBufferIndex-RECORDER_BUFFER_STEP,TheRecorderHwnd);

		}

	// û������
	}else{

		// ��������һ
		TheRecorderCount++;
		// ����
		TheRecorderBufferIndex -=i;

		if(TheRecorderBufferIndex<0){
			TheRecorderBufferIndex = 0;
		}

		// ���¼���
		if(TheRecorderCount>RECORDER_WAVE_TIME){

			// ����
			TheRecorderCount = 0;
			// ���
			TheRecorderBufferIndex +=i;

			// ��������
			if(TheRecorderBufferIndex>RECORDER_BUFFER_END){
				TheRecorderBufferIndex = RECORDER_BUFFER_END;			
			}

			// ���ٲ��ű�׼
			if(TheRecorderBufferIndex>=RECORDER_WAVE_LONG){

				// ��Ϊ����״̬
				TheRecorderInputStatus = RECORDER_STATUS_PLAY;
				// ���ó���״̬
				DrawSetBabyStatus(DRAW_BABY_STATUS_SPEAK);
				// ��������
				SpeakerPlay(TheRecorderBufferTotal+RECORDER_BUFFER_STEP,TheRecorderBufferIndex-RECORDER_BUFFER_STEP,TheRecorderHwnd);

			// ������ͱ�׼
			}else{

				// ����
				TheRecorderBufferIndex = 0;

			}

		}

	}

}

// ����¼��
void RecorderReset(void)
{

	// ���ü�����
	TheRecorderBufferIndex = 0;
	// ����������
	TheRecorderCount = 0;
	// ���ó���״̬
	DrawSetBabyStatus(DRAW_BABY_STATUS_NORMAL);
	// ��Ϊ����״̬
	TheRecorderInputStatus = RECORDER_STATUS_INPUT;

}

// ����¼������
void RecorderData(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// �Ѿ�¼������
	DWORD size = ((PWAVEHDR)lParam)->dwBytesRecorded;
	LPSTR data = ((PWAVEHDR)lParam)->lpData;

	// ��Ȳ����
	if(size!=RECORDER_BUFFER_SIZE){
		return;		
	}

	// ��������
	CopyMemory(TheRecorderWaveData,data,size);
	
	// ������������ϵͳ
	waveInAddBuffer(TheRecorderWaveIn, (PWAVEHDR)lParam, sizeof(WAVEHDR));

}

// �豸��
void RecorderOpen(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// ��ʼ¼��
	TheRecorderStatus = true;

}

// �豸�ر�
void RecorderClose(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// �ͷŻ�����
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		waveInUnprepareHeader(TheRecorderWaveIn, TheRecorderWaveHandle[i], sizeof (WAVEHDR));
	}

	// ��ʼ¼��
	TheRecorderStatus = false;

}