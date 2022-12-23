#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define WIN_WIDTH	1520				//窗口宽度
#define WIN_HEIGHT	800					//窗口高度
#define TEXTSIZE	23					//字体大小
#define COL_NUM	(WIN_WIDTH/TEXTSIZE)	//字符列数

#define CharNum	(WIN_HEIGHT/TEXTSIZE)	//一列雨丝字符个数
#define MinCharNum	6					//最少雨丝字符个数
#define MaxCharNum	16					//最多雨丝字符个数

void CreatePicture();					//产生全屏幕的字符串
string createString();					//产生一个字符串
vector<int> Create_One_SlidingWindow();	//产生一列雨丝初始位置和终止位置
void Create_All_SlidingWindow();		//产生每列雨丝初始位置和终止位置
void pulsRain();						//如果这列雨丝落地，产生一个新的
void InitModel();						//初始化内存变量

extern vector<string> str;
extern vector<vector<int>> address;
