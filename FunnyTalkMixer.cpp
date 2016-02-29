// 预编译
#include "stdafx.h"

// 自定义头文件
#include "FunnyTalkMixer.h"

// 以下是全局变量
IMixer*		TheMixer;							// 混音器对象
int			TheMixerVolume = 0;					// 混音器音量
bool		TheMixerSystemMessage = false;		// 是否有系统消息

//************************************************************************************************
//*************************** 混音处理 ***********************************************************
//************************************************************************************************

// 混音器音量降低
void MixerVolumeDown(int i)
{

	// 检测耳机状态
	int h = TheMixer->HeadphoneDetect();

	// 如果耳机插入
	if(h==TURNON_HEADPHONE){

		// 获取耳机音量并减低音量
		TheMixerVolume = TheMixer->GetHeadphoneVolume() - i;

	}else{

		// 获取喇叭音量并减低音量
		TheMixerVolume = TheMixer->GetSpeakerVolume() - i;

	}
	
	// 如果音量小于最小值
	if(TheMixerVolume<SOUND_VOLUME_MIN){
		TheMixerVolume = SOUND_VOLUME_MIN;
	}

	// 如果耳机插入
	if(h==TURNON_HEADPHONE){

		// 设置耳机音量
		TheMixer->SetHeadphoneVolume(TheMixerVolume);

	}else{

		// 设置喇叭音量
		TheMixer->SetSpeakerVolume(TheMixerVolume);

	}

}

// 混音器音量升高
void MixerVolumeUp(int i)
{

	// 当前状态
	int h = TheMixer->HeadphoneDetect();

	// 如果耳机插入
	if(h==TURNON_HEADPHONE){

		// 获取耳机音量并升高音量
		TheMixerVolume = TheMixer->GetHeadphoneVolume() + i;

	}else{

		// 获取喇叭音量并升高音量
		TheMixerVolume = TheMixer->GetSpeakerVolume() + i;

	}
	
	// 如果音量大于最大值
	if(TheMixerVolume>SOUND_VOLUME_MAX){
		TheMixerVolume = SOUND_VOLUME_MAX;
	}

	// 如果耳机插入
	if(h==TURNON_HEADPHONE){

		// 设置耳机音量
		TheMixer->SetHeadphoneVolume(TheMixerVolume);

	}else{

		// 设置喇叭音量
		TheMixer->SetSpeakerVolume(TheMixerVolume);

	}

}

// 初始化混音器
bool MixerInit(HWND hwnd)
{
	
	// 注册混音器COM组件，用来控制音量
	if(FAILED(CoCreateInstance(CLSID_Mixer,NULL,CLSCTX_INPROC_SERVER,IID_MZ_Mixer,(void **)&TheMixer))){
		return false;
    }

	// 打开混音设备
	if(!TheMixer->OpenMixerDevice(hwnd)){
		return false;
	}

	// 降低音量，实际是为了获取当前音量
	MixerVolumeDown(0);

	// 初始化成功
	return true;

}

// 设置混音器状态
void MixerModeSetting(void)
{

	// 有系统消息
	if(TheMixerSystemMessage){
		
		// 设定耳机与外放同时插入
		TheMixer->SetHeadphoneMode(HEADPHONE_ON);
		TheMixer->SetSpeakerMode(SPEAKER_AUTO);

		return;

	}

	// 如果耳机插入
	if(TheMixer->HeadphoneDetect()==TURNON_HEADPHONE){

		// 打开耳机，关闭外放
		TheMixer->SetHeadphoneMode(HEADPHONE_ON);
		TheMixer->SetSpeakerMode(SPEAKER_OFF);

	}else{

		// 关闭耳机，打开外放
		TheMixer->SetHeadphoneMode(HEADPHONE_OFF);
		TheMixer->SetSpeakerMode(SPEAKER_AUTO);

	}

	// 降低音量，实际是为了获取当前音量
	MixerVolumeDown(0);

}

// 释放混音器对象
void MixerEnd(void)
{

	// 释放对象
	if(TheMixer){
		TheMixer->Release();
	}

}

// 设置是否有系统消息
void MixerSetMessage(bool i)
{

	// 返回是否有系统消息
	TheMixerSystemMessage = i;

}

// 获取当前音量
int MixerGetVolume(void)
{

	// 音量计算
	int v = TheMixerVolume / SOUND_VOLUME_STEP;

	// 最小值
	if(v<SOUND_VOLUME_MIN){
		return SOUND_VOLUME_MIN;
	}

	// 最大值
	if(v>=SOUND_VOLUME_STEP){
		return SOUND_VOLUME_STEP-1;
	}

	// 返回当前音量
	return  v;

}