#pragma once

//====================ͷ�ļ���������=======================
#include<graphics.h>								//Ҫ���ڶ�ý���豸�ӿ�ǰ��
#include<mmsystem.h>  //��ý���豸�ӿ�
#include<conio.h>
#include<time.h>

//=====================���ļ���������======================
#pragma comment (lib,"winmm.lib")

//=====================ȫ�ֱ���������======================
#define WINDOW_WIDTH	1000
#define WINDOW_HEIGHT	800
#define Num				18				//������
#define PanLength		720				//���̱߳�
#define GeLength		(PanLength/Num)  //���ӱ߳�/*****�궨��û�����ų�����******/
#define Leftjie			80				//���
#define Rightjie		200				//�ҽ�
#define UpDownjie		40				//���½�
#define SUM_Songs		5				//�������
#define SUM_Pictures	10				//����ͼƬ������
#define hong			RGB(255,0,0)
#define cheng			RGB(255,125,0)
#define huang			RGB(255,255,0)
#define lv				RGB(0,255,0)
#define lan				RGB(0,0,255)
#define dian			RGB(0,255,255)
#define zi				RGB(255,0,255)
#define heise			BLACK			//������ɫ
#define baise			lv			//������ɫ

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
//int Record[];			//�������������¼
int drawX = 0, drawY = 0;//�������
int X = 0, Y = 0;			//��������
int cnt;	//�ߵĲ���
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
}Record;		//�������������¼


TCHAR hei[] = _T("����:���1");
TCHAR bai[] = _T("����:���2");
TCHAR heibu[] = _T("��������  ��");
TCHAR baibu[] = _T("��������  ��");
TCHAR luozi[] = _T("���  ����");
TCHAR again[] = _T("������Ϸ");
TCHAR huiqi[] = _T("����");
TCHAR gaoxiao[] = _T("����");
TCHAR qiege[] = _T("����и�");
TCHAR qiebkp[] = _T("����б���");

//======================ȫ�ֺ�������=======================
VOID GameInit();
VOID PlayGame();
VOID MouseClick();
VOID Judge();
VOID Back();
VOID ChangeSong();
VOID ChangePictures();
VOID Initbefore();
