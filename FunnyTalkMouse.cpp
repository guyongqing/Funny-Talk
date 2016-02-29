
// Ԥ����
#include "stdafx.h"
// ͷ�ļ�
#include "FunnyTalkMouse.h"
#include "FunnyTalkGame.h"

//************************************************************************************************
//*************************** ��괦�� ***********************************************************
//************************************************************************************************

// �������
int TheMouseLocationX = 0;
int TheMouseLocationY = 0;

/************************ ���˫��ʱ **********************************/

// ���˫��ʱ
void MouseClick(int x, int y)
{

}

/************************ ����ƶ�ʱ **********************************/

// ����ƶ�ʱ
void MouseMove(int x, int y)
{

	// �ж��Ƿ���в˵�
	DrawSetMenuIndex(x,y,false);	

}

/************************ ���̧��ʱ **********************************/

// ���̧��ʱ
void MouseUp(int x, int y)
{

	// ����˵�ѡ��״̬
	DrawSetMenuIndex(x,y,true);

	// ����ˮƽ����
	if(abs(y-TheMouseLocationY)>200){
		return;
	}

	// ����������
	if(abs(x-TheMouseLocationX)<200){
		return;
	}

	// ���һ���
	if(x>TheMouseLocationX){
		DrawNext(1);
	// ���󻬶�
	}else{
		DrawNext(-1);
	}

}

/************************ ��갴��ʱ **********************************/

// ��갴��ʱ
void MouseDown(int x, int y)
{

	// ��������
	TheMouseLocationX = x;
	TheMouseLocationY = y;

	// ������Ϸ
	if(!GameIsLive()){
		GameLive();		
	}

	// �ж��Ƿ���в˵�
	DrawSetMenuIndex(x,y,false);

}