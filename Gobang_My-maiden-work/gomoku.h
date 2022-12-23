#pragma once

//====================头文件包含部分=======================
#include<graphics.h>								//要放在多媒体设备接口前边
#include<mmsystem.h>  //多媒体设备接口
#include<conio.h>
#include<time.h>

//=====================库文件包含部分======================
#pragma comment (lib,"winmm.lib")

//=====================全局变量的声明======================
#define WINDOW_WIDTH	1000
#define WINDOW_HEIGHT	800
#define Num				18				//格子数
#define PanLength		720				//棋盘边长
#define GeLength		(PanLength/Num)  //格子边长/*****宏定义没加括号出问题******/
#define Leftjie			80				//左界
#define Rightjie		200				//右界
#define UpDownjie		40				//上下界
#define SUM_Songs		5				//歌的数量
#define SUM_Pictures	10				//背景图片的数量
#define hong			RGB(255,0,0)
#define cheng			RGB(255,125,0)
#define huang			RGB(255,255,0)
#define lv				RGB(0,255,0)
#define lan				RGB(0,0,255)
#define dian			RGB(0,255,255)
#define zi				RGB(255,0,255)
#define heise			BLACK			//黑棋颜色
#define baise			lv			//白棋颜色

IMAGE Background1;
IMAGE Background2;
IMAGE Background3;
IMAGE Background4;
IMAGE Background5;
IMAGE Background6;
IMAGE Background7;
IMAGE Background8;
IMAGE Background9;
IMAGE Background10;
HWND hWnd;

int Map[Num + 1][Num + 1] = { 0 };
//int Record[];			//所有棋子坐标记录
int drawX = 0, drawY = 0;//棋的坐标
int X = 0, Y = 0;			//数组坐标
int cnt;	//走的步数
int i, j;
TCHAR heibuS[30];
TCHAR baibuS[30];
TCHAR wanjia[30];
MOUSEMSG msg = { 0 };
int flag;
int chongwan;
int NO_Songs = 0;
int NO_Pictures = 0;
struct {
	int rx[(Num + 1)*(Num + 1)];
	int ry[(Num + 1)*(Num + 1)];
}Record;		//所有棋子坐标记录


TCHAR hei[] = _T("黑棋:玩家1");
TCHAR bai[] = _T("粉棋:玩家2");
TCHAR heibu[] = _T("黑棋已走  步");
TCHAR baibu[] = _T("粉棋已走  步");
TCHAR luozi[] = _T("玩家  落子");
TCHAR again[] = _T("重玩游戏");
TCHAR huiqi[] = _T("悔棋");
TCHAR gaoxiao[] = _T("作弊");
TCHAR qiege[] = _T("随机切歌");
TCHAR qiebkp[] = _T("随机切背景");

//======================全局函数声明=======================
VOID GameInit();
VOID PlayGame();
VOID MouseClick();
VOID Judge();
VOID Back();
VOID ChangeSong();
VOID ChangePictures();
VOID Initbefore();
