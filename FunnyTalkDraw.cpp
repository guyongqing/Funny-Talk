// 预编译
#include "stdafx.h"

// 自定义头文件
#include "FunnyTalkDraw.h"

// 以下是全局变量

// DirectDraw 全局变量

DDSURFACEDESC			TheDDrawSurface;		// DirectDraw 表面结构
DDCOLORKEY				TheDDrawColorKey;		// DirectDraw 透明色
DDALPHABLTFX			TheDDrawAlphaBltfx;		// DirectDraw 半透明色	
DDPIXELFORMAT			TheDDrawPixelFormat;	// DirectDraw 像素格式结构

LPDIRECTDRAW			TheDDraw;				// DirectDraw 界面
LPDIRECTDRAWCLIPPER		TheDDrawClipper;		// DirectDraw 裁剪器
LPDIRECTDRAWSURFACE		TheDDrawPrimary;		// DirectDraw 主表面
LPDIRECTDRAWSURFACE		TheDDrawBackBuffer;		// DirectDraw 后备表面
LPDIRECTDRAWSURFACE		TheDDrawBackground;		// DirectDraw 背景表面
LPDIRECTDRAWSURFACE		TheDDrawForeground;		// DirectDraw 前景表面

//************************** 全局矩阵 *********************************************//

// 屏幕矩阵
RECT	TheRectScreen = {0,0,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT};
// 黑色矩阵
RECT	TheRectColorBlack = {0,0,0,0};
// 白色矩阵
RECT	TheRectColorWhite = {2,2,3,3};
// 目标矩阵
RECT	TheRectTarget = {50,600,425,693};
// 来源矩阵
RECT	TheRectSource = {95,0,470,94};

// 音量
RECT	TheRectVolume[SOUND_VOLUME_STEP] = {{1,203,47,249},{48,203,94,249},{95,203,141,249},{142,203,188,249},{189,203,235,249},{236,203,282,249},{283,203,329,249},{330,203,376,249},{377,203,423,249},{424,203,470,249}};
RECT	TheRectVolumeTarget = {23,50,69,96};

// 菜单项（正常）
RECT	TheRectMenuSource[DRAW_MENU_COUNT] = {{1,1,94,94},{95,1,188,94},{189,1,282,94},{283,1,376,94},{377,1,470,94}};
// 菜单项（选中）
RECT	TheRectMenuSelected[DRAW_MENU_COUNT] = {{1,95,94,188},{95,95,188,188},{189,95,282,188},{283,95,376,188},{377,95,470,188}};
// 菜单项（目标）
RECT	TheRectMenuTarget[DRAW_MENU_COUNT] = {{370,50,463,143},{19,608,112,701},{368,608,461,701},{252,608,345,701},{135,608,228,701}};

//** 宠物部分 ********************************************************************************************** //

// 当前宠物编号
int TheBabyIndex = DRAW_BABY_NAME_CAT;
// 当前宠物状态
int TheBabyStatus = DRAW_BABY_STATUS_NORMAL;
// 当前宠物表情编号
int TheBabyFace = DRAW_BABY_FACE_NORMAL_FIRST;

//** 文件部分 ********************************************************************************************** //

LPTSTR	TheImageFile[DRAW_BABY_COUNT] = {L"FunnyTalk.r00",L"FunnyTalk.r01",L"FunnyTalk.r02",L"FunnyTalk.r03"};
int	TheImageFileSize[DRAW_BABY_COUNT] = {691200,624000,435840,503040};

//** 矩阵部分 ********************************************************************************************** //

// 图形来源矩阵
RECT TheRectBabyMouse[DRAW_BABY_IMG_COUNT] = {{2,2,238,238},{242,2,478,238},{2,242,238,478},{242,242,478,478},{2,482,238,718},{242,482,478,718}};
RECT TheRectBabyDog[DRAW_BABY_IMG_COUNT] = {{2,2,157,322},{162,2,317,322},{322,2,478,322},{2,327,157,647},{162,327,317,647},{322,327,478,647}};
RECT TheRectBabyCat[DRAW_BABY_IMG_COUNT] = {{2,2,157,224},{162,2,317,224},{322,2,478,224},{2,229,157,451},{162,229,317,451},{322,229,478,451}};
RECT TheRectBabyCrazy[DRAW_BABY_IMG_COUNT] = {{2,2,157,259},{162,2,317,259},{322,2,478,259},{2,264,157,521},{162,264,317,521},{322,264,478,521}};

// 宠物图形来源
RECT* TheRectBabySource[DRAW_BABY_COUNT] = {TheRectBabyMouse,TheRectBabyDog,TheRectBabyCat,TheRectBabyCrazy};
// 宠物目标矩阵
RECT TheRectBabyTarget[DRAW_BABY_COUNT] = {{122,242,358,478},{162,200,318,521},{162,249,317,471},{162,231,317,488}};

// 程序控制
bool	TheDrawIsFirst = true;
// 菜单位置
int		TheDrawMenuIndex = DRAW_MENU_NAME_NONE;

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 绘图总入口
void Draw(void)
{

	// 第一次运行
	if(TheDrawIsFirst){

		// 清屏幕
		DrawRectNormal(TheDDrawBackground,&TheRectColorWhite,&TheRectScreen,DRAW_BLT_NORMAL);	
		TheDrawIsFirst = false;

	}

	// 绘制当前宠物的当前表情
	DrawRectNormal(TheDDrawBackground,&TheRectBabySource[TheBabyIndex][TheBabyFace],&TheRectBabyTarget[TheBabyIndex],DRAW_BLT_NORMAL);	

	TheBabyFace++;

	// 等待状态
	if(TheBabyStatus==DRAW_BABY_STATUS_NORMAL){

		// 切换画面
		if(TheBabyFace>DRAW_BABY_FACE_NORMAL_SECOND){
			TheBabyFace = DRAW_BABY_FACE_NORMAL_FIRST;
		}

	// 播放状态
	}else{

		// 播放动画
		if(TheBabyFace>DRAW_BABY_FACE_RUN_4){
			TheBabyFace = DRAW_BABY_FACE_RUN_1;
		}

	}

	// 绘制音量
	DrawRectNormal(TheDDrawForeground,&TheRectVolume[MixerGetVolume()],&TheRectVolumeTarget,DRAW_BLT_NORMAL);

	// 绘制菜单
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_CLOSE],&TheRectMenuTarget[DRAW_MENU_NAME_CLOSE],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_PREV],&TheRectMenuTarget[DRAW_MENU_NAME_PREV],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_NEXT],&TheRectMenuTarget[DRAW_MENU_NAME_NEXT],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_PLUS],&TheRectMenuTarget[DRAW_MENU_NAME_PLUS],DRAW_BLT_NORMAL);	
	DrawRectNormal(TheDDrawForeground,&TheRectMenuSource[DRAW_MENU_NAME_DIMINISH],&TheRectMenuTarget[DRAW_MENU_NAME_DIMINISH],DRAW_BLT_NORMAL);	

	// 绘制选中项
	if((TheDrawMenuIndex>DRAW_MENU_NAME_NONE)&&(TheDrawMenuIndex<DRAW_MENU_COUNT)){
		DrawRectNormal(TheDDrawForeground,&TheRectMenuSelected[TheDrawMenuIndex],&TheRectMenuTarget[TheDrawMenuIndex],DRAW_BLT_NORMAL);	
	}	

	// 绘制主表面
	DrawPrimary();	

}

// 设置宠物状态
void DrawSetBabyStatus(int i)
{

	// 设置状态
	TheBabyStatus = i;

}

// 获取当前宠物编号
int DrawGetBabyIndex(void)
{

	// 返回宠物编号
	return TheBabyIndex;

}

// 切换宠物
void DrawNext(int i)
{
	// 清屏幕
	DrawRectNormal(TheDDrawBackground,&TheRectColorWhite,&TheRectBabyTarget[TheBabyIndex],DRAW_BLT_NORMAL);	

	// 切换下一个宠物
	TheBabyIndex+=i;

	// 超出最大值
	if(TheBabyIndex>DRAW_BABY_NAME_CRAZY){
		TheBabyIndex = DRAW_BABY_NAME_MOUSE; 
	}

	// 低于最小值
	if(TheBabyIndex<DRAW_BABY_NAME_MOUSE){
		TheBabyIndex = DRAW_BABY_NAME_CRAZY;
	}

	// 载入图象
	LoadingImageFile(TheImageFile[TheBabyIndex],TheImageFileSize[TheBabyIndex],TheDDrawBackground);

}

// 绘图初始化
bool DrawInit(void)
{

	// 载入第一个图象
	if(!LoadingImageFile(TheImageFile[TheBabyIndex],TheImageFileSize[TheBabyIndex],TheDDrawBackground)){
		return false;
	}

	// 载入前景图象
	if(!LoadingImageFile(DRAW_FOREGROUND_FILE,DRAW_FOREGROUND_SIZE,TheDDrawForeground)){
		return false;
	}

	// 成功
	return true;

}

// 设置菜单位置
void DrawSetMenuIndex(int x, int y, bool isUp)
{

	// 判断鼠标是否按中菜单
	for(int i=DRAW_MENU_NAME_CLOSE;i<DRAW_MENU_COUNT;i++){

		if(DrawRectArea(&TheRectMenuTarget[i],x,y)){

			// 设置全局变量位置
			TheDrawMenuIndex = i;

			// 鼠标抬起
			if(isUp){

				// 判断是哪一个被选中
				switch(TheDrawMenuIndex){

					// 关闭
					case DRAW_MENU_NAME_CLOSE:

						// 退出程序
						PostQuitMessage(0);
						break;

					// 上一个宠物
					case DRAW_MENU_NAME_PREV:

						// 选择上一个宠物
						DrawNext(-1);
						break;

					// 下一个宠物
					case DRAW_MENU_NAME_NEXT:

						// 选择下一个宠物
						DrawNext(1);
						break;

					// 降低声音
					case DRAW_MENU_NAME_DIMINISH:

						// 降低声音
						MixerVolumeDown(SOUND_VOLUME_STEP);
						break;

					// 升高声音
					case DRAW_MENU_NAME_PLUS:

						// 升高声音
						MixerVolumeUp(SOUND_VOLUME_STEP);
						break;

				}

				// 恢复没有被选中状态
				TheDrawMenuIndex = DRAW_MENU_NAME_NONE;

			}
			return;

		}

	}

	// 没有任何菜单被选中
	TheDrawMenuIndex = DRAW_MENU_NAME_NONE;	

}

// 鼠标坐标是否在某个矩阵中
bool DrawRectArea(RECT* rect, int x, int y)
{

	// 横坐标
	if((x>rect->left)&&(x<rect->right)){

		// 纵坐标
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

// 绘图结束
void DrawEnd(void)
{

	

}

// 绘制主表面
void DrawPrimary(void)
{
	
	// 将后备表面复制到主表面
	TheDDrawPrimary->Blt(&TheRectScreen,TheDDrawBackBuffer,&TheRectScreen,DDBLT_WAITNOTBUSY,NULL);	

}

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************


// 初始化
bool DirectDrawInit(HWND hwnd)
{

	// 创建DirectDraw对象
	if(DirectDrawCreate(NULL,&TheDDraw,NULL)!=DD_OK){
		return false;
	}

	// 设置协作方式
	if(TheDDraw->SetCooperativeLevel(hwnd,DDSCL_NORMAL)!=DD_OK){
		return false;
	}

	/********************************主表面****************************************/

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	TheDDrawSurface.dwFlags = DDSD_CAPS;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// 创建主表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,&TheDDrawPrimary,NULL)!=DD_OK){
		return false;
	}

	// 设置像素格式	
	DDRAW_INIT_STRUCT(TheDDrawPixelFormat);
	// 获取像素格式
	TheDDrawPrimary->GetPixelFormat(&TheDDrawPixelFormat);

	// 如果不是16位色模式
	if(TheDDrawPixelFormat.dwRGBBitCount!=DRAW_SCREEN_COLOR){
		return false;
	}

	// 创建裁剪器
	if(TheDDraw->CreateClipper(0,&TheDDrawClipper,NULL)!=DD_OK){
		return false;
	}
	
	// 设置裁剪器窗口句柄
	if(TheDDrawClipper->SetHWnd(0,hwnd)!=DD_OK){
		return false;
	}

	// 关联裁剪器
	if(TheDDrawPrimary->SetClipper(TheDDrawClipper)!=DD_OK){
		return false;
	}

	// 创建后备表面
	if(!DirectDrawCreateSurface(&TheDDrawBackBuffer,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT)){
		return false;
	}

	// 创建背景表面
	if(!DirectDrawCreateSurface(&TheDDrawBackground,DRAW_BACKGROUND_WIDTH,DRAW_BACKGROUND_HEIGHT)){
		return false;
	}

	// 创建前景表面
	if(!DirectDrawCreateSurface(&TheDDrawForeground,DRAW_FOREGROUND_WIDTH,DRAW_FOREGROUND_HEIGHT)){
		return false;
	}

	// 设置透明色	
	TheDDrawColorKey.dwColorSpaceHighValue = DRAW_COLOR_BLACK;
	TheDDrawColorKey.dwColorSpaceLowValue = DRAW_COLOR_BLACK;
	TheDDrawBackground->SetColorKey(DDCKEY_SRCBLT,&TheDDrawColorKey);

	// 初始化半透明结构
	DDRAW_INIT_STRUCT(TheDDrawAlphaBltfx);

	return true;

}

// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE* s, int w, int h)
{

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 设置资料读取中表面参数
	TheDDrawSurface.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
	TheDDrawSurface.dwWidth = w;
	TheDDrawSurface.dwHeight = h;

	// 创建资料读取中表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,s,NULL)!=DD_OK){
		return false;
	}

	return true;

}

// 销毁
void DirectDrawEnd(void)
{

	// 释放前景表面
	if(TheDDrawForeground){
		TheDDrawForeground->Release();
		TheDDrawForeground = NULL;
	}

	// 释放背景表面
	if(TheDDrawBackground){
		TheDDrawBackground->Release();
		TheDDrawBackground = NULL;
	}

	// 释放后备表面
	if(TheDDrawBackBuffer){
		TheDDrawBackBuffer->Release();
		TheDDrawBackBuffer = NULL;
	}

	// 释放主表面
	if(TheDDrawPrimary){
		TheDDrawPrimary->Release();
		TheDDrawPrimary = NULL;
	}

	// 销毁剪切版
	if(TheDDrawClipper){
		TheDDrawClipper->Release();
		TheDDrawClipper = NULL;
	}

	// 释放内部分配资源
	if(TheDDraw){
		TheDDraw->Release();
		TheDDraw = NULL;
	}

}

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************


// 读取图像文件
bool LoadingImageFile(LPTSTR imgFile, int imgSize, LPDIRECTDRAWSURFACE imgSurface)
{

	bool flag = false;

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 锁定主角表面
	if(imgSurface->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return false;
	}

	// 缓冲数据
	CHAR* bb = (CHAR *)TheDDrawSurface.lpSurface;

	// 读取文件
	flag = FileGetData(imgFile,bb,imgSize);

	// 解锁主角表面
	imgSurface->Unlock(NULL);

	// 操作成功
	return flag;	

}

//************************************************************************************************
//*************************** 矩 形 绘 制 ********************************************************
//************************************************************************************************

// 快速绘制矩形
void DrawRectNormal(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int colorkey)
{

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->Blt(rTarget,ddSurface,rSource,DDBLT_WAITNOTBUSY|colorkey,NULL);

}

// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int alpha)
{

	// 设置半透明程度
	TheDDrawAlphaBltfx.ddargbScaleFactors.alpha = alpha;

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->AlphaBlt(rTarget,ddSurface,rSource,DDABLT_WAITNOTBUSY|DDABLT_ALPHASRCNEG,&TheDDrawAlphaBltfx);

}