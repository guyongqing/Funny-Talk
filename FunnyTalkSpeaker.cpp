#pragma once

// 预编译
#include "stdafx.h"

// 录音机
#include "FunnyTalkRecorder.h"
// 图形控制
#include "FunnyTalkDraw.h"

// 全局声音输出句柄
HWAVEOUT		TheSpeakerWaveOut[SPEAKER_DEVICE_COUNT];
// 声音结构
WAVEFORMATEX	TheSpeakerWaveFormat[SPEAKER_DEVICE_COUNT];
// 声音句柄
WAVEHDR		TheSpeakerWaveHandle[SPEAKER_DEVICE_COUNT];

// 采样率
DWORD			TheSpeakerWaveSampleRate[SPEAKER_DEVICE_COUNT] = {21000,9000,14000,18000};
// 每秒采样数
DWORD			TheSpeakerWaveBytePerSec[SPEAKER_DEVICE_COUNT] = {21000,9000,14000,18000};

//************************************************************************************************
//*************************** 声 音 播 放   ******************************************************
//************************************************************************************************

// 初始化扬声器
bool SpeakerInit(HWND hwnd)
{

	// 遍历设备
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// 打开扬声器设备前对参数进行设置
		SpeakerSetParameter(i,SPEAKER_SAMPLE_WIDTH,TheSpeakerWaveSampleRate[i],SPEAKER_CHANNEL_COUNT,WAVE_FORMAT_PCM,SPEAKER_BLOCK_ALIGN,TheSpeakerWaveBytePerSec[i]);

		// 打开扬声器设备失败
		if(waveOutOpen(&TheSpeakerWaveOut[i],WAVE_MAPPER,&TheSpeakerWaveFormat[i],(DWORD)hwnd,NULL,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
			return false;
		}

	}

	// 返回真
	return true;

}

// 结束声音播放
void SpeakerEnd(void)
{

	// 遍历设备
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// 停止播放
		waveOutReset(TheSpeakerWaveOut[i]);	

		// 关闭设备
		waveOutClose(TheSpeakerWaveOut[i]);

	}

}

// 打开扬声器设备前对参数进行设置
void SpeakerSetParameter(int spkDevice, WORD sampleWidth, DWORD sampleRate, WORD channelCount, WORD dataType, WORD blockAlign, DWORD bytesPerSec)
{

	// 音频格式类型
	TheSpeakerWaveFormat[spkDevice].wFormatTag = dataType;
	// 声道数
	TheSpeakerWaveFormat[spkDevice].nChannels = channelCount;
	// 采样频率
	TheSpeakerWaveFormat[spkDevice].nSamplesPerSec = sampleRate;
	// 采样宽度
	TheSpeakerWaveFormat[spkDevice].wBitsPerSample = sampleWidth;
	// 每个样本的字节数
	TheSpeakerWaveFormat[spkDevice].nBlockAlign = blockAlign;
	// 每秒采集的字节数
	TheSpeakerWaveFormat[spkDevice].nAvgBytesPerSec = bytesPerSec;

}

// 播放声音
void SpeakerPlay(BYTE* data, int length, HWND hwnd)
{

	// 获取当前宠物编号
	int baby = DrawGetBabyIndex();
	

	/*// 分配内存句柄
	TheSpeakerWaveHandle=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));*/

	// 填充声音句柄结构
	TheSpeakerWaveHandle[baby].lpData = (LPSTR)data;	
	TheSpeakerWaveHandle[baby].dwBufferLength = length;
	TheSpeakerWaveHandle[baby].dwBytesRecorded = 0;
	TheSpeakerWaveHandle[baby].dwUser = 0;
	TheSpeakerWaveHandle[baby].dwFlags = 0;
	TheSpeakerWaveHandle[baby].dwLoops = 1;
	TheSpeakerWaveHandle[baby].lpNext = NULL;
	TheSpeakerWaveHandle[baby].reserved = 0;

	// 准备缓冲区
	waveOutPrepareHeader(TheSpeakerWaveOut[baby],&TheSpeakerWaveHandle[baby],sizeof(WAVEHDR));
	// 输出声音
	waveOutWrite(TheSpeakerWaveOut[baby],&TheSpeakerWaveHandle[baby],sizeof(WAVEHDR)); 

}

// 处理完毕状态
void SpeakerDone(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// 遍历设备
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// 停止播放
		waveOutReset(TheSpeakerWaveOut[i]);	

	}

	// 播放完毕，重新开始录音
	RecorderReset();

}

// 设备打开
void SpeakerOpen(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	

}

// 设备关闭
void SpeakerClose(UINT message, WPARAM  wParam, LPARAM  lParam)
{
	
	// 遍历设备
	for(int i=0;i<SPEAKER_DEVICE_COUNT;i++){

		// 释放缓冲区	
		waveOutUnprepareHeader(TheSpeakerWaveOut[i], &TheSpeakerWaveHandle[i],sizeof(WAVEHDR));

		// 释放内存
		if(&TheSpeakerWaveHandle[i]){
			free(&TheSpeakerWaveHandle[i]);
		}

	}

}