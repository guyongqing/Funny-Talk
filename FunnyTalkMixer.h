#pragma once

// 混音器
#include <IMixer.h>
#include <IMixer_GUID.h>

// 参数定义
#define	SOUND_VOLUME_DEFAULT	20			// 默认音量
#define SOUND_VOLUME_MIN		0			// 最小声音
#define SOUND_VOLUME_MAX		100			// 最大声音
#define SOUND_VOLUME_STEP		10			// 音量步伐

//************************************************************************************************
//*************************** 混音处理 ***********************************************************
//************************************************************************************************

// 初始化混音器
bool MixerInit(HWND);
// 混音器音量降低
void MixerVolumeDown(int);
// 混音器音量升高
void MixerVolumeUp(int);
// 喇叭状态设置
void MixerModeSetting(void);
// 释放混音器对象
void MixerEnd(void);
// 设置是否有系统消息
void MixerSetMessage(bool);		
// 获取当前音量
int MixerGetVolume(void);