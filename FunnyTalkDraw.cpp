// Ԥ����
#include "stdafx.h"

// �Զ���ͷ�ļ�
#include "FunnyTalkDraw.h"

// ������ȫ�ֱ���

// DirectDraw ȫ�ֱ���

DDSURFACEDESC			TheDDrawSurface;		// DirectDraw ����ṹ
DDCOLORKEY				TheDDrawColorKey;		// DirectDraw ͸��ɫ
DDALPHABLTFX			TheDDrawAlphaBltfx;		// DirectDraw ��͸��ɫ	
DDPIXELFORMAT			TheDDrawPixelFormat;	// DirectDraw ���ظ�ʽ�ṹ

LPDIRECTDRAW			TheDDraw;				// DirectDraw ����
LPDIRECTDRAWCLIPPER		TheDDrawClipper;		// DirectDraw �ü���
LPDIRECTDRAWSURFACE		TheDDrawPrimary;		// DirectDraw ������
LPDIRECTDRAWSURFACE		TheDDrawBackBuffer;		// DirectDraw �󱸱���
LPDIRECTDRAWSURFACE		TheDDrawBackground;		// DirectDraw ��������
LPDIRECTDRAWSURFACE		TheDDrawForeground;		// DirectDraw ǰ������

//************************** ȫ�־��� *********************************************//

// ��Ļ����
RECT	TheRectScreen = {0,0,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT};
// ��ɫ����
RECT	TheRectColorBlack = {0,0,0,0};
// ��ɫ����
RECT	TheRectColorWhite = {2,2,3,3};
// Ŀ�����
RECT	TheRectTarget = {50,600,425,693};
// ��Դ����
RECT	TheRectSource = {95,0,470,94};

// ����
RECT	TheRectVolume[SOUND_VOLUME_STEP] = {{1,203,47,249},{48,203,94,249},{95,203,141,249},{142,203,188,249},{189,203,235,249},{236,203,282,249},{283,203,329,249},{330,203,376,249},{377,203,423,249},{424,203,470,249}};
RECT	TheRectVolumeTarget = {23,50,69,96};

// �˵��������
RECT	TheRectMenuSource[DRAW_MENU_COUNT] = {{1,1,94,94},{95,1,188,94},{189,1,282,94},{283,1,376,94},{377,1,470,94}};
// �˵��ѡ�У�
RECT	TheRectMenuSelected[DRAW_MENU_COUNT] = {{1,95,94,188},{95,95,188,188},{189,95,282,188},{283,95,376,188},{377,95,470,188}};
// �˵��Ŀ�꣩
RECT	TheRectMenuTarget[DRAW_MENU_COUNT] = {{370,50,463,143},{19,608,112,701},{368,608,461,701},{252,608,345,701},{135,608,228,701}};

//** ���ﲿ�� ********************************************************************************************** //

// ��ǰ������
int TheBabyIndex = DRAW_BABY_NAME_CAT;
// ��ǰ����״̬
int TheBabyStatus = DRAW_BABY_STATUS_NORMAL;
// ��ǰ���������
int TheBabyFace = DRAW_BABY_FACE_NORMAL_FIRST;

//** �ļ����� ********************************************************************************************** //

LPTSTR	TheImageFile[DRAW_BABY_COUNT] = {L"FunnyTalk.r00",L"FunnyTalk.r01",L"FunnyTalk.r02",L"FunnyTalk.r03"};
int	TheImageFileSize[DRAW_BABY_COUNT] = {691200,624000,435840,503040};

//** ���󲿷� ********************************************************************************************** //

// ͼ����Դ����
RECT TheRectBabyMouse[DRAW_BABY_IMG_COUNT] = {{2,2,238,238},{242,2,478,238},{2,242,238,478},{242,242,478,478},{2,482,238,718},{242,482,478,718}};
RECT TheRectBabyDog[DRAW_BABY_IMG_COUNT] = {{2,2,157,322},{162,2,317,322},{322,2,478,322},{2,327,157,647},{162,327,317,647},{322,327,478,647}};
RECT TheRectBabyCat[DRAW_BABY_IMG_COUNT] = {{2,2,157,224},{162,2,317,224},{322,2,478,224},{2,229,157,451},{162,229,317,451},{322,229,478,451}};
RECT TheRectBabyCrazy[DRAW_BABY_IMG_COUNT] = {{2,2,157,259},{162,2,317,259},{322,2,478,259},{2,264,157,521},{162,264,317,521},{322,264,478,521}};

// ����ͼ����Դ
RECT* TheRectBabySource[DRAW_BABY_COUNT] = {TheRectBabyMouse,TheRectBabyDog,TheRectBabyCat,TheRectBabyCrazy};
// ����Ŀ�����
RECT TheRectBabyTarget[DRAW_BABY_COUNT] = {{122,242,358,478},{162,200,318,521},{162,249,317,471},{162,231,317,488}};

// �������
bool	TheDrawIsFirst = true;
// �˵�λ��
int		TheDrawMenuIndex = DRAW_MENU_NAME_NONE;

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��ͼ�����
void Draw(void)
{

	// ��һ������
	if(TheDrawIsFirst){

		// ����Ļ
		DrawRectNormal(TheDDrawBackground,&TheRectColorWhite,&TheRectScreen,DRAW_BLT_NORMAL);	
		TheDrawIsFirst = false;

	}

	// ���Ƶ�ǰ����ĵ�ǰ����
	DrawRectNormal(TheDDrawBackground,&TheRectBabySource[TheBabyIndex][TheBabyFace],&TheRectBabyTarget[TheBabyIndex],DRAW_BLT_NORMAL);	

	TheBabyFace++;

	// �ȴ�״̬
	if(TheBabyStatus==DRAW_BABY_STATUS_NORMAL){

		// �л�����
		if(TheBabyFace>DRAW_BABY_FACE_NORMAL_SECOND){
			TheBabyFace = DRAW_BABY_FACE_NORMAL_FIRST;
		}

	// ����״̬
	}else{

		// ���Ŷ���
		if(TheBabyFace>DRAW_BABY_FACE_RUN_4){
			TheBabyFace = DRAW_BABY_FACE_RUN_1;
		}

	}

	// ��������
	DrawRectNormal(TheDDrawForeground,&TheRectVolume[MixerGetVolume()],&TheRectVolumeTarget,DRAW_BLT_NORMAL);

	// ���Ʋ˵�
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_CLOSE],&TheRectMenuTarget[DRAW_MENU_NAME_CLOSE],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_PREV],&TheRectMenuTarget[DRAW_MENU_NAME_PREV],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_NEXT],&TheRectMenuTarget[DRAW_MENU_NAME_NEXT],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_PLUS],&TheRectMenuTarget[DRAW_MENU_NAME_PLUS],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_DIMINISH],&TheRectMenuTarget[DRAW_MENU_NAME_DIMINISH],DRAW_BLT_NORMAL);	

	// ����ѡ����
	if((TheDrawMenuIndex>DRAW_MENU_NAME_NONE)&&(TheDrawMenuIndex<DRAW_MENU_COUNT)){
		DrawRectNormal(TheDDrawForeground,&TheRectMenuSelected[TheDrawMenuIndex],&TheRectMenuTarget[TheDrawMenuIndex],DRAW_BLT_NORMAL);	
	}	

	// ����������
	DrawPrimary();	

}

// ���ó���״̬
void DrawSetBabyStatus(int i)
{

	// ����״̬
	TheBabyStatus = i;

}

// ��ȡ��ǰ������
int DrawGetBabyIndex(void)
{

	// ���س�����
	return TheBabyIndex;

}

// �л�����
void DrawNext(int i)
{
	// ����Ļ
	DrawRectNormal(TheDDrawBackground,&TheRectColorWhite,&TheRectBabyTarget[TheBabyIndex],DRAW_BLT_NORMAL);	

	// �л���һ������
	TheBabyIndex+=i;

	// �������ֵ
	if(TheBabyIndex>DRAW_BABY_NAME_CRAZY){
		TheBabyIndex = DRAW_BABY_NAME_MOUSE; 
	}

	// ������Сֵ
	if(TheBabyIndex<DRAW_BABY_NAME_MOUSE){
		TheBabyIndex = DRAW_BABY_NAME_CRAZY;
	}

	// ����ͼ��
	LoadingImageFile(TheImageFile[TheBabyIndex],TheImageFileSize[TheBabyIndex],TheDDrawBackground);

}

// ��ͼ��ʼ��
bool DrawInit(void)
{

	// �����һ��ͼ��
	if(!LoadingImageFile(TheImageFile[TheBabyIndex],TheImageFileSize[TheBabyIndex],TheDDrawBackground)){
		return false;
	}

	// ����ǰ��ͼ��
	if(!LoadingImageFile(DRAW_FOREGROUND_FILE,DRAW_FOREGROUND_SIZE,TheDDrawForeground)){
		return false;
	}

	// �ɹ�
	return true;

}

// ���ò˵�λ��
void DrawSetMenuIndex(int x, int y, bool isUp)
{

	// �ж�����Ƿ��в˵�
	for(int i=DRAW_MENU_NAME_CLOSE;i<DRAW_MENU_COUNT;i++){

		if(DrawRectArea(&TheRectMenuTarget[i],x,y)){

			// ����ȫ�ֱ���λ��
			TheDrawMenuIndex = i;

			// ���̧��
			if(isUp){

				// �ж�����һ����ѡ��
				switch(TheDrawMenuIndex){

					// �ر�
					case DRAW_MENU_NAME_CLOSE:

						// �˳�����
						PostQuitMessage(0);
						break;

					// ��һ������
					case DRAW_MENU_NAME_PREV:

						// ѡ����һ������
						DrawNext(-1);
						break;

					// ��һ������
					case DRAW_MENU_NAME_NEXT:

						// ѡ����һ������
						DrawNext(1);
						break;

					// ��������
					case DRAW_MENU_NAME_DIMINISH:

						// ��������
						MixerVolumeDown(SOUND_VOLUME_STEP);
						break;

					// ��������
					case DRAW_MENU_NAME_PLUS:

						// ��������
						MixerVolumeUp(SOUND_VOLUME_STEP);
						break;

				}

				// �ָ�û�б�ѡ��״̬
				TheDrawMenuIndex = DRAW_MENU_NAME_NONE;

			}
			return;

		}

	}

	// û���κβ˵���ѡ��
	TheDrawMenuIndex = DRAW_MENU_NAME_NONE;	

}

// ��������Ƿ���ĳ��������
bool DrawRectArea(RECT* rect, int x, int y)
{

	// ������
	if((x>rect->left)&&(x<rect->right)){

		// ������
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

// ��ͼ����
void DrawEnd(void)
{

	

}

// ����������
void DrawPrimary(void)
{
	
	// ���󱸱��渴�Ƶ�������
	TheDDrawPrimary->Blt(&TheRectScreen,TheDDrawBackBuffer,&TheRectScreen,DDBLT_WAITNOTBUSY,NULL);	

}

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************


// ��ʼ��
bool DirectDrawInit(HWND hwnd)
{

	// ����DirectDraw����
	if(DirectDrawCreate(NULL,&TheDDraw,NULL)!=DD_OK){
		return false;
	}

	// ����Э����ʽ
	if(TheDDraw->SetCooperativeLevel(hwnd,DDSCL_NORMAL)!=DD_OK){
		return false;
	}

	/********************************������****************************************/

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	TheDDrawSurface.dwFlags = DDSD_CAPS;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// ����������
	if(TheDDraw->CreateSurface(&TheDDrawSurface,&TheDDrawPrimary,NULL)!=DD_OK){
		return false;
	}

	// �������ظ�ʽ	
	DDRAW_INIT_STRUCT(TheDDrawPixelFormat);
	// ��ȡ���ظ�ʽ
	TheDDrawPrimary->GetPixelFormat(&TheDDrawPixelFormat);

	// �������16λɫģʽ
	if(TheDDrawPixelFormat.dwRGBBitCount!=DRAW_SCREEN_COLOR){
		return false;
	}

	// �����ü���
	if(TheDDraw->CreateClipper(0,&TheDDrawClipper,NULL)!=DD_OK){
		return false;
	}
	
	// ���òü������ھ��
	if(TheDDrawClipper->SetHWnd(0,hwnd)!=DD_OK){
		return false;
	}

	// �����ü���
	if(TheDDrawPrimary->SetClipper(TheDDrawClipper)!=DD_OK){
		return false;
	}

	// �����󱸱���
	if(!DirectDrawCreateSurface(&TheDDrawBackBuffer,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT)){
		return false;
	}

	// ������������
	if(!DirectDrawCreateSurface(&TheDDrawBackground,DRAW_BACKGROUND_WIDTH,DRAW_BACKGROUND_HEIGHT)){
		return false;
	}

	// ����ǰ������
	if(!DirectDrawCreateSurface(&TheDDrawForeground,DRAW_FOREGROUND_WIDTH,DRAW_FOREGROUND_HEIGHT)){
		return false;
	}

	// ����͸��ɫ	
	TheDDrawColorKey.dwColorSpaceHighValue = DRAW_COLOR_BLACK;
	TheDDrawColorKey.dwColorSpaceLowValue = DRAW_COLOR_BLACK;
	TheDDrawBackground->SetColorKey(DDCKEY_SRCBLT,&TheDDrawColorKey);

	// ��ʼ����͸���ṹ
	DDRAW_INIT_STRUCT(TheDDrawAlphaBltfx);

	return true;

}

// ��������
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE* s, int w, int h)
{

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// �������϶�ȡ�б������
	TheDDrawSurface.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
	TheDDrawSurface.dwWidth = w;
	TheDDrawSurface.dwHeight = h;

	// �������϶�ȡ�б���
	if(TheDDraw->CreateSurface(&TheDDrawSurface,s,NULL)!=DD_OK){
		return false;
	}

	return true;

}

// ����
void DirectDrawEnd(void)
{

	// �ͷ�ǰ������
	if(TheDDrawForeground){
		TheDDrawForeground->Release();
		TheDDrawForeground = NULL;
	}

	// �ͷű�������
	if(TheDDrawBackground){
		TheDDrawBackground->Release();
		TheDDrawBackground = NULL;
	}

	// �ͷź󱸱���
	if(TheDDrawBackBuffer){
		TheDDrawBackBuffer->Release();
		TheDDrawBackBuffer = NULL;
	}

	// �ͷ�������
	if(TheDDrawPrimary){
		TheDDrawPrimary->Release();
		TheDDrawPrimary = NULL;
	}

	// ���ټ��а�
	if(TheDDrawClipper){
		TheDDrawClipper->Release();
		TheDDrawClipper = NULL;
	}

	// �ͷ��ڲ�������Դ
	if(TheDDraw){
		TheDDraw->Release();
		TheDDraw = NULL;
	}

}

//************************************************************************************************
//*************************** �� �� �� ȡ ********************************************************
//************************************************************************************************


// ��ȡͼ���ļ�
bool LoadingImageFile(LPTSTR imgFile, int imgSize, LPDIRECTDRAWSURFACE imgSurface)
{

	bool flag = false;

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// �������Ǳ���
	if(imgSurface->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return false;
	}

	// ��������
	CHAR* bb = (CHAR *)TheDDrawSurface.lpSurface;

	// ��ȡ�ļ�
	flag = FileGetData(imgFile,bb,imgSize);

	// �������Ǳ���
	imgSurface->Unlock(NULL);

	// �����ɹ�
	return flag;	

}

//************************************************************************************************
//*************************** �� �� �� �� ********************************************************
//************************************************************************************************

// ���ٻ��ƾ���
void DrawRectNormal(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int colorkey)
{

	// ����Դ�����������󱸻���
	TheDDrawBackBuffer->Blt(rTarget,ddSurface,rSource,DDBLT_WAITNOTBUSY|colorkey,NULL);

}

// ���ٻ��ƾ��Σ���͸����
void DrawRectAlpha(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int alpha)
{

	// ���ð�͸���̶�
	TheDDrawAlphaBltfx.ddargbScaleFactors.alpha = alpha;

	// ����Դ�����������󱸻���
	TheDDrawBackBuffer->AlphaBlt(rTarget,ddSurface,rSource,DDABLT_WAITNOTBUSY|DDABLT_ALPHASRCNEG,&TheDDrawAlphaBltfx);

}