#pragma once

// 游戏控制
#include "FunnyTalkGame.h"
// 文件管理
#include "FunnyTalkFile.h"
// 混音器
#include "FunnyTalkMixer.h"

// 屏幕属性
#define	DRAW_SCREEN_WIDTH			480			// 屏幕宽度
#define	DRAW_SCREEN_HEIGHT			720			// 屏幕高度
#define	DRAW_SCREEN_WIDTH_MID		240			// 屏幕宽度一半
#define	DRAW_SCREEN_HEIGHT_MID		360			// 屏幕高度一半
#define DRAW_SCREEN_COLOR			16			// 16 位色
#define DRAW_SCREEN_SIZE			345600		// 屏幕占用字节数

// 常用颜色
#define DRAW_COLOR_BLACK			0x000000	// 黑色
#define DRAW_COLOR_WHITE			0xFFFFFF	// 白色

// 定义是否透明
#define DRAW_BLT_NORMAL				0				// 正常填充
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// 透明填充

// 半透明数据
#define DRAW_ALPHA_MIN				0				// 最小半透明色
#define DRAW_ALPHA_MID				128				// 50% 半透明色
#define DRAW_ALPHA_MAX				255				// 最大半透明色

// 图像缓冲
#define DRAW_BACKGROUND_WIDTH			480			// 背景宽度
#define DRAW_BACKGROUND_HEIGHT			720			// 背景高度
#define DRAW_BACKGROUND_SIZE			691200		// 背景大小
#define DRAW_BACKGROUND_FILE			L"FunnyTalk.img"		// 背景文件

#define DRAW_FOREGROUND_WIDTH			480			// 前景宽度
#define DRAW_FOREGROUND_HEIGHT			250			// 前景高度
#define DRAW_FOREGROUND_SIZE			240000		// 前景大小
#define DRAW_FOREGROUND_FILE			L"FunnyTalk.rar"		// 前景文件

// 宠物部分
#define DRAW_BABY_COUNT					4			// 一共四个宠物
#define DRAW_BABY_IMG_COUNT				6			// 一共六种表情

// 宠物名称
#define DRAW_BABY_NAME_MOUSE			0			// 老鼠
#define	DRAW_BABY_NAME_DOG				1			// 狗
#define	DRAW_BABY_NAME_CAT				2			// 猫
#define	DRAW_BABY_NAME_CRAZY			3			// 疯狗

// 宠物状态
#define DRAW_BABY_STATUS_NORMAL			0			// 正常状态
#define DRAW_BABY_STATUS_SPEAK			1			// 说话状态

// 宠物表情
#define DRAW_BABY_FACE_NORMAL_FIRST		0			// 正常状态(静)
#define DRAW_BABY_FACE_NORMAL_SECOND	1			// 正常状态(动)

#define DRAW_BABY_FACE_RUN_1			2			// 播放状态
#define DRAW_BABY_FACE_RUN_2			3			// 播放状态
#define DRAW_BABY_FACE_RUN_3			4			// 播放状态
#define DRAW_BABY_FACE_RUN_4			5			// 播放状态

// 菜单部分
#define DRAW_MENU_COUNT					5			// 菜单项数量
#define DRAW_MENU_NAME_NONE				-1			// 没有选中
#define DRAW_MENU_NAME_CLOSE			0			// 关闭
#define DRAW_MENU_NAME_PREV				1			// 上一个
#define DRAW_MENU_NAME_NEXT				2			// 下一个
#define DRAW_MENU_NAME_PLUS				3			// 加
#define DRAW_MENU_NAME_DIMINISH			4			// 减

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 绘图总入口
void Draw(void);
// 绘图初始化
bool DrawInit(void);
// 设置菜单位置
void DrawSetMenuIndex(int,int,bool);
// 获取当前宠物编号
int DrawGetBabyIndex(void);
// 设置宠物状态
void DrawSetBabyStatus(int);
// 切换宠物
void DrawNext(int);
// 绘图结束
void DrawEnd(void);
// 绘制主表面
void DrawPrimary(void);
// 鼠标坐标是否在某个矩阵中
bool DrawRectArea(RECT*, int, int);

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}
#define _RGB16BIT565(r,g,b) ((b&31)+((g&63)<<5)+((r&31)<<11))

// 初始化
bool DirectDrawInit(HWND);
// 销毁
void DirectDrawEnd(void);
// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************

// 读取图像文件
bool LoadingImageFile(LPTSTR, int, LPDIRECTDRAWSURFACE);

//************************************************************************************************
//*************************** 矩 形 绘 制 ********************************************************
//************************************************************************************************

// 绘制矩形
void DrawRectNormal(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);