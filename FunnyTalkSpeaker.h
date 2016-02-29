#pragma once

// 录音控制
#include "FunnyTalkRecorder.h"
// 绘图控制
#include "FunnyTalkDraw.h"

// 一些参数定义
#define	SPEAKER_DEVICE_COUNT		4			// 扬声器数量
#define SPEAKER_SAMPLE_WIDTH		8			// 采样宽度
#define SPEAKER_CHANNEL_COUNT		1			// 声道数
#define SPEAKER_BLOCK_ALIGN			1			// 每个样本的字节数

//************************************************************************************************
//*************************** 声 音 播 放   ******************************************************
//************************************************************************************************

// 初始化扬声器
bool SpeakerInit(HWND);
// 结束声音播放
void SpeakerEnd(void);
// 打开扬声器设备前对参数进行设置
void SpeakerSetParameter(int, WORD, DWORD, WORD, WORD, WORD, DWORD);
// 播放声音
void SpeakerPlay(BYTE*, int, HWND);
// 处理完毕状态
void SpeakerDone(UINT, WPARAM, LPARAM);
// 设备打开
void SpeakerOpen(UINT, WPARAM, LPARAM);
// 设备关闭
void SpeakerClose(UINT, WPARAM, LPARAM);