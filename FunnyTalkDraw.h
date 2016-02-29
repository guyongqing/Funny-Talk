#pragma once

// ��Ϸ����
#include "FunnyTalkGame.h"
// �ļ�����
#include "FunnyTalkFile.h"
// ������
#include "FunnyTalkMixer.h"

// ��Ļ����
#define	DRAW_SCREEN_WIDTH			480			// ��Ļ���
#define	DRAW_SCREEN_HEIGHT			720			// ��Ļ�߶�
#define	DRAW_SCREEN_WIDTH_MID		240			// ��Ļ���һ��
#define	DRAW_SCREEN_HEIGHT_MID		360			// ��Ļ�߶�һ��
#define DRAW_SCREEN_COLOR			16			// 16 λɫ
#define DRAW_SCREEN_SIZE			345600		// ��Ļռ���ֽ���

// ������ɫ
#define DRAW_COLOR_BLACK			0x000000	// ��ɫ
#define DRAW_COLOR_WHITE			0xFFFFFF	// ��ɫ

// �����Ƿ�͸��
#define DRAW_BLT_NORMAL				0				// �������
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// ͸�����

// ��͸������
#define DRAW_ALPHA_MIN				0				// ��С��͸��ɫ
#define DRAW_ALPHA_MID				128				// 50% ��͸��ɫ
#define DRAW_ALPHA_MAX				255				// ����͸��ɫ

// ͼ�񻺳�
#define DRAW_BACKGROUND_WIDTH			480			// �������
#define DRAW_BACKGROUND_HEIGHT			720			// �����߶�
#define DRAW_BACKGROUND_SIZE			691200		// ������С
#define DRAW_BACKGROUND_FILE			L"FunnyTalk.img"		// �����ļ�

#define DRAW_FOREGROUND_WIDTH			480			// ǰ�����
#define DRAW_FOREGROUND_HEIGHT			250			// ǰ���߶�
#define DRAW_FOREGROUND_SIZE			240000		// ǰ����С
#define DRAW_FOREGROUND_FILE			L"FunnyTalk.rar"		// ǰ���ļ�

// ���ﲿ��
#define DRAW_BABY_COUNT					4			// һ���ĸ�����
#define DRAW_BABY_IMG_COUNT				6			// һ�����ֱ���

// ��������
#define DRAW_BABY_NAME_MOUSE			0			// ����
#define	DRAW_BABY_NAME_DOG				1			// ��
#define	DRAW_BABY_NAME_CAT				2			// è
#define	DRAW_BABY_NAME_CRAZY			3			// �蹷

// ����״̬
#define DRAW_BABY_STATUS_NORMAL			0			// ����״̬
#define DRAW_BABY_STATUS_SPEAK			1			// ˵��״̬

// �������
#define DRAW_BABY_FACE_NORMAL_FIRST		0			// ����״̬(��)
#define DRAW_BABY_FACE_NORMAL_SECOND	1			// ����״̬(��)

#define DRAW_BABY_FACE_RUN_1			2			// ����״̬
#define DRAW_BABY_FACE_RUN_2			3			// ����״̬
#define DRAW_BABY_FACE_RUN_3			4			// ����״̬
#define DRAW_BABY_FACE_RUN_4			5			// ����״̬

// �˵�����
#define DRAW_MENU_COUNT					5			// �˵�������
#define DRAW_MENU_NAME_NONE				-1			// û��ѡ��
#define DRAW_MENU_NAME_CLOSE			0			// �ر�
#define DRAW_MENU_NAME_PREV				1			// ��һ��
#define DRAW_MENU_NAME_NEXT				2			// ��һ��
#define DRAW_MENU_NAME_PLUS				3			// ��
#define DRAW_MENU_NAME_DIMINISH			4			// ��

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��ͼ�����
void Draw(void);
// ��ͼ��ʼ��
bool DrawInit(void);
// ���ò˵�λ��
void DrawSetMenuIndex(int,int,bool);
// ��ȡ��ǰ������
int DrawGetBabyIndex(void);
// ���ó���״̬
void DrawSetBabyStatus(int);
// �л�����
void DrawNext(int);
// ��ͼ����
void DrawEnd(void);
// ����������
void DrawPrimary(void);
// ��������Ƿ���ĳ��������
bool DrawRectArea(RECT*, int, int);

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}
#define _RGB16BIT565(r,g,b) ((b&31)+((g&63)<<5)+((r&31)<<11))

// ��ʼ��
bool DirectDrawInit(HWND);
// ����
void DirectDrawEnd(void);
// ��������
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** �� �� �� ȡ ********************************************************
//************************************************************************************************

// ��ȡͼ���ļ�
bool LoadingImageFile(LPTSTR, int, LPDIRECTDRAWSURFACE);

//************************************************************************************************
//*************************** �� �� �� �� ********************************************************
//************************************************************************************************

// ���ƾ���
void DrawRectNormal(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// ���ٻ��ƾ��Σ���͸����
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);