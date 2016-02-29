// Ԥ����
#include "stdafx.h"

// �Զ���ͷ�ļ�
#include "FunnyTalkMixer.h"

// ������ȫ�ֱ���
IMixer*		TheMixer;							// ����������
int			TheMixerVolume = 0;					// ����������
bool		TheMixerSystemMessage = false;		// �Ƿ���ϵͳ��Ϣ

//************************************************************************************************
//*************************** �������� ***********************************************************
//************************************************************************************************

// ��������������
void MixerVolumeDown(int i)
{

	// ������״̬
	int h = TheMixer->HeadphoneDetect();

	// �����������
	if(h==TURNON_HEADPHONE){

		// ��ȡ������������������
		TheMixerVolume = TheMixer->GetHeadphoneVolume() - i;

	}else{

		// ��ȡ������������������
		TheMixerVolume = TheMixer->GetSpeakerVolume() - i;

	}
	
	// �������С����Сֵ
	if(TheMixerVolume<SOUND_VOLUME_MIN){
		TheMixerVolume = SOUND_VOLUME_MIN;
	}

	// �����������
	if(h==TURNON_HEADPHONE){

		// ���ö�������
		TheMixer->SetHeadphoneVolume(TheMixerVolume);

	}else{

		// ������������
		TheMixer->SetSpeakerVolume(TheMixerVolume);

	}

}

// ��������������
void MixerVolumeUp(int i)
{

	// ��ǰ״̬
	int h = TheMixer->HeadphoneDetect();

	// �����������
	if(h==TURNON_HEADPHONE){

		// ��ȡ������������������
		TheMixerVolume = TheMixer->GetHeadphoneVolume() + i;

	}else{

		// ��ȡ������������������
		TheMixerVolume = TheMixer->GetSpeakerVolume() + i;

	}
	
	// ��������������ֵ
	if(TheMixerVolume>SOUND_VOLUME_MAX){
		TheMixerVolume = SOUND_VOLUME_MAX;
	}

	// �����������
	if(h==TURNON_HEADPHONE){

		// ���ö�������
		TheMixer->SetHeadphoneVolume(TheMixerVolume);

	}else{

		// ������������
		TheMixer->SetSpeakerVolume(TheMixerVolume);

	}

}

// ��ʼ��������
bool MixerInit(HWND hwnd)
{
	
	// ע�������COM�����������������
	if(FAILED(CoCreateInstance(CLSID_Mixer,NULL,CLSCTX_INPROC_SERVER,IID_MZ_Mixer,(void **)&TheMixer))){
		return false;
    }

	// �򿪻����豸
	if(!TheMixer->OpenMixerDevice(hwnd)){
		return false;
	}

	// ����������ʵ����Ϊ�˻�ȡ��ǰ����
	MixerVolumeDown(0);

	// ��ʼ���ɹ�
	return true;

}

// ���û�����״̬
void MixerModeSetting(void)
{

	// ��ϵͳ��Ϣ
	if(TheMixerSystemMessage){
		
		// �趨���������ͬʱ����
		TheMixer->SetHeadphoneMode(HEADPHONE_ON);
		TheMixer->SetSpeakerMode(SPEAKER_AUTO);

		return;

	}

	// �����������
	if(TheMixer->HeadphoneDetect()==TURNON_HEADPHONE){

		// �򿪶������ر����
		TheMixer->SetHeadphoneMode(HEADPHONE_ON);
		TheMixer->SetSpeakerMode(SPEAKER_OFF);

	}else{

		// �رն����������
		TheMixer->SetHeadphoneMode(HEADPHONE_OFF);
		TheMixer->SetSpeakerMode(SPEAKER_AUTO);

	}

	// ����������ʵ����Ϊ�˻�ȡ��ǰ����
	MixerVolumeDown(0);

}

// �ͷŻ���������
void MixerEnd(void)
{

	// �ͷŶ���
	if(TheMixer){
		TheMixer->Release();
	}

}

// �����Ƿ���ϵͳ��Ϣ
void MixerSetMessage(bool i)
{

	// �����Ƿ���ϵͳ��Ϣ
	TheMixerSystemMessage = i;

}

// ��ȡ��ǰ����
int MixerGetVolume(void)
{

	// ��������
	int v = TheMixerVolume / SOUND_VOLUME_STEP;

	// ��Сֵ
	if(v<SOUND_VOLUME_MIN){
		return SOUND_VOLUME_MIN;
	}

	// ���ֵ
	if(v>=SOUND_VOLUME_STEP){
		return SOUND_VOLUME_STEP-1;
	}

	// ���ص�ǰ����
	return  v;

}