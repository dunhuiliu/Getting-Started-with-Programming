#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>

//----------------------------宏定义------------------------------
#define WIN_LENGTH 1200//窗口长
#define WIN_HEIGHT 800//窗口高
#define PI_180 (3.1415926/180)	//π/180
#define hc 1.24					//组合常数hc=1.24nm*keV			λ=hc/E=1.24/E nm*keV
#define R1 0.053				//基态轨道半径(单位：nm)
#define E1 -13.6				//基态能量（单位：ev）
#define NUM 7					//能级数
#define ENLARGE 150				//做图半径放大系数
#define CHAR_TIME 200			//字符渐变时间
#define CHAR_X -150				//字符横坐标
#define CHAR_Y -50				//字符纵坐标

//--------------------------自定义变量类型--------------------------
typedef struct    //电子属性
{
	double r;//电子半径
	double e;//电子能量
}ELEC;

typedef struct		//电子位置
{
	double x;//电子横坐标
	double y;//电子纵坐标
}COORDINATE;

//-----------------------------函数原型----------------------------
void InitBkimg();//初始化轨道
double radius(int n);//计算轨道半径
double Energy(int n);//计算电子能量
COORDINATE Coor(int x, double R);//计算电子位置



void Xi_Name_Print(int xi);//谱线系名显示
void Put_Photon(int x, int y);//释放光子
void Demo_Line(double x1, double y1, double x2, double y2);//画演示线（箭头）
void attribute(double e1, double e2, int xii, int kk);//跃迁属性显示

//----------------------------全局变量声明-------------------------
ELEC elec;//电子属性
COORDINATE pos;//电子位置

//-------------------------------主函数-----------------------------
int main()
{
	int i, j,k,xi,o=0, count = 1,cnt;//辅助变量定义
	int PX, PY;//光子移动坐标
	initgraph(WIN_LENGTH, WIN_HEIGHT);//初始化窗口

	setbkcolor(WHITE);//设置背景色
	cleardevice();//清屏
	Sleep(500);//开始暂停0.5秒显示效果更好

	setorigin(WIN_LENGTH / 2, WIN_HEIGHT / 2);//设置坐标原点

	setlinecolor(BLACK);//设置画线颜色
	//设置图案填充色
	setfillcolor(RGB(255, 128, 0));		//橘黄
//	setfillcolor(RGB(0, 255, 255));			//靛

	for (xi = 1; xi < NUM-1; xi++)//所有系
	{
		Xi_Name_Print(xi);//打印系名
		for (k = xi+1; k <= NUM; k++)//每个系的遍历
		{
			
			for (j = k, elec.e = Energy(j), elec.r = radius(j), cnt = 2; cnt; j = xi,elec.r = radius(j))//每一条谱线
			{
				if (cnt == 2)
				{
					Demo_Line(-radius(j), 0, -radius(xi), 0);//画演示线
					//printf("e1=%lf\te2=%lf", elec.e, Energy(xi));
					attribute(elec.e, Energy(xi), xi, k);//打印能力、波长、光子颜色信息
				}
				cnt--;//辅助变量
				for (i = 180, o = 0; i != 177 && i != 178 && i != 176; i += 8, o += 1)//以等角度做图的每一帧
				{
					if (i >= 360)
					{
						i=0;
					}

				pos = Coor(i, elec.r);//计算电子坐标


				if (i == int(elec.r) || i == -int(elec.r))
				{
					count++;
				}
			
				setlinestyle(PS_SOLID, 1);	//设置画线样式为直线
				setlinecolor(BLACK);
				fillcircle(pos.x, pos.y, 5);//h画电子——————填充圆

				if (cnt == 0 && PX - 5 * o>-WIN_LENGTH / 2)//根据跃迁能级不同画不同颜色的辐射光子
				{
					if (xi == 1)
					{
						setlinecolor(RGB(172, 0, 172));
					}
					else if (xi == 2)
					{
						if (k == 3)    //可见光设置
						{
							setlinecolor(RED);
						}
						else if (k == 4)
						{
							setlinecolor(GREEN);
						}
						else if (k == 5)
						{
							setlinecolor(BLUE);
						}
						else if (k == 6)
						{
							setlinecolor(RGB(172, 0, 172));
						}
						else
						{
							setlinecolor(RGB(172, 0, 172));
						}
					}
					else
					{
						setlinecolor(RED);
					}
					Put_Photon(PX - 5 * o, PY);//画光子
				}

				Sleep(100);


				InitBkimg();//初始化背景能级圆
				}

				if (cnt == 1)//光子移动坐标置零
				{
					PX = pos.x;
					PY = 0;
				}
			}
		}
	}

	_getch();
	return 0;
}

//-----------------------------自定义函数------------------------------
void InitBkimg()
{
	int i;
	cleardevice();
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	fillcircle(0, 0, 2);
	for (i = 1; i <= NUM; i++)
	{
		circle(0, 0, radius(i));
	}
	settextstyle(15, 15, L"宋体");
	settextcolor(BLUE);
	outtextxy(radius(1) + 1, 0, 'K');
	outtextxy(radius(2) + 5, 0, 'L');
	outtextxy(radius(3) + 5, 0, 'M');
	outtextxy(radius(4) + 5, 0, 'N');
	outtextxy(radius(5) + 5, 0, 'O');
	outtextxy(radius(6) + 5, 0, 'P');
	outtextxy(radius(7) + 5, 0, 'Q');
}

double radius(int n)//求轨道半径
{
	return R1*n*n*ENLARGE;
}

double Energy(int n)//求能级能量
{
	return E1 / (n*n);
}

COORDINATE Coor(int x, double R)//计算电子位置
{
	COORDINATE E;
	E.x = R*cos(x*PI_180);
	E.y = R*sin(x*PI_180);
	return E;
}


void Xi_Name_Print(int xi)//打印系名
{
	float count;
	cleardevice();
	settextstyle(50, 50, L"宋体");//设置字的大小和样式
	switch (xi)
	{
	case 1:
		for (count=0;count<=10;count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));//颜色渐变————变浅
			outtextxy(CHAR_X, CHAR_Y, L"莱曼系");
			Sleep(CHAR_TIME);//停留时间
			cleardevice();
		}
		break; 
	case 2:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"巴耳末系");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break;
	case 3:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"帕邢系");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break; 
	case 4:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"布拉开系");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break; 
	case 5:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"普丰德系");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break;
	}
}

void Put_Photon(int x,int y)//(x,y)为光子尾部坐标，根据参数画光子，使光子移动
{
	int length = 5;
	setlinestyle(PS_SOLID, 3);//设置画线样式
	line(x, y, x - length, y);
	line(x - length, y, x - 2*length, y + length);
	line(x - 2*length, y + length, x - 5*length, y - length);
	line(x - 5 * length, y - length, x - 7 * length, y + length);
	line(x - 7 * length, y + length, x - 9 * length, y - length);
	line(x - 9 * length, y - length, x - 10 * length, y);
	line(x - 10 * length, y, x - 14 * length, y);
	line(x - 14 * length, y, x - 13 * length, y + length);
	line(x - 14 * length, y, x - 13 * length, y - length);
	Sleep(20);
}

void Demo_Line(double x1, double y1, double x2, double y2)//画演示线
{
	for (int i = 0; i <= x2 - x1; i+=1)
	{
		cleardevice();
		InitBkimg();
		setlinecolor(RED);
		line(x1, y1, x1 + i, y1);
		line(x1 + i, y1, x1 + i - 10, y1 - 10);
		line(x1 + i, y1, x1 + i - 10, y1 + 10);
		Sleep(10);
	}

	settextstyle(50, 50, L"宋体");
	settextcolor(RED);
	outtextxy(500, -350, L"按");
	outtextxy(500, -250, L"任");
	outtextxy(500, -150, L"意");
	outtextxy(500, -50, L"键");
	outtextxy(500, 50, L"继");
	outtextxy(500, 150, L"续");
}

void attribute(double e1, double e2, int xii, int kk)//打印波长、能量、辐射光子颜色等信息
{
	TCHAR s[50], d[50];
	settextstyle(15, 15, L"宋体");
	settextcolor(BLACK);
	outtextxy(-580, -380, L"能级能差:      eV");
	outtextxy(-580, -300, L"光子波长:      nm");
	_stprintf_s(s, _T("%.2f"), e1 - e2);
	_stprintf_s(d, _T("%.2f"), 1000 * hc / (e1 - e2));
	settextcolor(RGB(255, 128, 0));
	//printf("\n%lf\t%lf\n", e1 - e2, 1000 * hc / (e1 - e2));
	outtextxy(-450, -380, s);
	outtextxy(-450, -300, d);
	if (xii == 1 || (xii == 2 && kk > 6))
	{
		settextcolor(RGB(172, 0, 172));
		outtextxy(-560, -220, L"紫外光");
	}
	else if (xii == 2 && kk == 3)
	{
		settextcolor(RED);
		outtextxy(-560, -220, L"可见光（红色）");
	}
	else if (xii == 2 && kk == 4)
	{
		settextcolor(GREEN);
		outtextxy(-560, -220, L"可见光（绿色）");
	}
	else if (xii == 2 && kk == 5)
	{
		settextcolor(BLUE);
		outtextxy(-560, -220, L"可见光（蓝色）");
	}
	else if (xii == 2 && kk == 6)
	{
		settextcolor(RGB(172, 0, 172));
		outtextxy(-560, -220, L"可见光（紫色）");
	}
	else {
		settextcolor(RED);
		outtextxy(-560, -220, L"红外光");
	}

	_getch();
}