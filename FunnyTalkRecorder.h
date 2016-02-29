#pragma once

// 系统录音类
#include	<IRecorder.h>
#include	<IRecorder_Guid.h>

// 声音播放
#include	"FunnyTalkSpeaker.h"
// 绘图控制
#include	"FunnyTalkDraw.h"

// 初始数据
#define RECORDER_SAMPLE_WIDTH		8			// 采样宽度
#define RECORDER_SAMPLE_RATE		11025		// 采样率
#define RECORDER_BYTES_PER_SEC		11025		// 每秒采样字节数
#define RECORDER_CHANNEL_COUNT		1			// 声道数
#define RECORDER_BLOCK_ALIGN		1			// 每个样本的字节数
#define RECORDER_BUFFER_SIZE		512			// 缓冲区大小
#define RECORDER_BUFFER_STEP		916			// 缓冲区间隔
#define RECORDER_BUFFER_COUNT		4			// 缓冲区数量
#define RECORDER_BUFFER_TOTAL		220500		// 总缓冲区
#define RECORDER_BUFFER_END			220499		// 总缓冲区结束

// 状态数据
#define RECORDER_STATUS_INPUT		0			// 录音
#define RECORDER_STATUS_PLAY		1			// 播放

// 声音数据
#define RECORDER_WAVE_MIN			0			// 最小值
#define RECORDER_WAVE_MID			128			// 中间值
#define RECORDER_WAVE_MAX			255			// 最大值

#define RECORDER_WAVE_MUTE			10			// 静音标准
#define RECORDER_WAVE_TIME			15			// 静间时间
#define RECORDER_WAVE_LONG			5120		// 最少播放标准

//************************************************************************************************
//*************************** 录 音 机   *********************************************************
//************************************************************************************************

// 录音机初始化
bool RecorderInit(HWND);
// 打开录音设备前对参数进行设置
void RecorderSetParameter(WORD, DWORD, WORD, WORD, WORD, DWORD);
// 开始录音
void RecorderStart(void);
// 停止录音
void RecorderStop(void);
// 暂停录音
void RecorderPause(void);
// 结束录音
void RecorderEnd(void);
// 保存到总缓存
void RecorderSaveToBuffer(void);
// 重置录音
void RecorderReset(void);
// 处理音频数据
void RecorderData(UINT, WPARAM, LPARAM);
// 设备打开
void RecorderOpen(UINT, WPARAM, LPARAM);
// 设备关闭
void RecorderClose(UINT, WPARAM, LPARAM);