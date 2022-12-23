/***************************************************
文件名称：main.cpp
文件描述：点电荷电力线的计算机模拟
编译环境：VS 2015
最后修改：
	<2018年6月1日>
***************************************************/
//-----------------------------头文件-------------------------
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
//#include<bios.h>
//#include<dos.h>

//-----------------------------宏定义--------------------------
#define WIN_LENGTH	1200			//窗口长
#define WIN_HEIGHT	700				//窗口高
#define PI_180		(3.1415926/180)	//π/180
#define ANGLE 2						//起始角度

//点电荷
typedef struct
{
	double x;
	double y;
	double q;//电荷量
}CHARGE;



//电场强度
typedef struct
{
	double str;//电场强度的大小
	double strx;//电场强度x分量的大小
	double stry;//电场强度y分量的大小
	double r1; //电场线上某点到点电荷一的距离
	double r2;//电场线上某点到点电荷二的距离
}STRENGTH;

//电力线起点坐标
typedef struct
{
	double x;
	double y;
}ElecSpot;


//----------------------------函数原型-------------------------
void Init_Binary_Charge(double x1, double y1, double q1, double x2, double y2, double q2);		//初始化两个电荷
ElecSpot InitPoint(double x, double y, double r, double angle);//初始化起始点
STRENGTH Strength(double x, double y, double x1, double y1, double q1, double x2, double y2, double q2);//计算所给点的电场强度
ElecSpot _origin(double x, double y, STRENGTH strength);//计算下一点的坐标
void Command(char s[]);//获取用户输入
//double Q_Q(double q1, double q2);


//---------------------------全局变量声明----------------------
double RADIUS = 5;			//电场线起始半径
double STEP = 0.1;//步长
int NUM = 22;			//电力线数量(可取值：2、4、8、16、11、22、44、88)
char com = 0;//指令声明
CHARGE Q1 = { -200,0, -100 };//电荷一
CHARGE	Q2 = { 200,  0,  100 };//电荷二
int Color = RGB(255, 128, 0);//电场线颜色
char ins[50];//用户输入存储
//double Q1_Q2;//(用于控制异种电荷电场线的终止);异种电荷纵向场强为零处有关系：q1/q2=(r1/r2)^3成立。	证明如下k*q1/(r1^2)	*	y/r1	=	k*q2/(r2^2)	*	y/r2。


//-----------------------------主函数--------------------------
int main()
{
	ElecSpot elec1[100], elec2[100];
	double dif_ang;
	int i = 0, j = 0;
	STRENGTH a1;
	ElecSpot bb1;
	double xx1, yy1, xx2, yy2;

	initgraph(WIN_LENGTH, WIN_HEIGHT);
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//清屏
	setorigin(WIN_LENGTH / 2, WIN_HEIGHT / 2);	//设置屏幕中心为坐标原点


	while (1)
	{
		Init_Binary_Charge(Q1.x, Q1.y, Q1.q, Q2.x, Q2.y, Q2.q);

		//在电荷圈上初始化若干个点		从2度到178度取点		以等差角度取点
		dif_ang = (178 - 2) / NUM;
		for (i = 0; i < NUM; i++)
		{
			elec1[i] = InitPoint(Q1.x, Q1.y, RADIUS, (i + 1)*dif_ang);
			elec2[i] = InitPoint(Q2.x, Q2.y, RADIUS, (176 - (i + 1)*dif_ang));
			putpixel((int)elec1[i].x, (int)elec1[i].y, Color);//(int)xx,强制把xx转换为int 型
			putpixel((int)elec1[i].x, -(int)elec1[i].y, Color);
			putpixel((int)elec2[i].x, (int)elec2[i].y, Color);
			putpixel((int)elec2[i].x, -(int)elec2[i].y, Color);
		}

		for (j = 0; j < NUM; j++)
		{
			xx1 = elec1[j].x;
			yy1 = elec1[j].y;
			while (1)
			{
				a1 = Strength(xx1, yy1, Q1.x, Q1.y, Q1.q, Q2.x, Q2.y, Q2.q);
				bb1 = _origin(xx1, yy1, a1);
				putpixel((int)bb1.x, (int)bb1.y, Color);
				putpixel((int)bb1.x, -(int)bb1.y, Color);
				xx1 = bb1.x;
				yy1 = bb1.y;
				if (Q1.q*Q2.q < 0)
				{
					if (((yy1 >= -WIN_HEIGHT / 2) && (yy1 <= WIN_HEIGHT / 2) && (xx1 >= -WIN_LENGTH / 2) && (xx1 <= WIN_LENGTH / 2) && xx1 <= 0) == 0)
						break;
				}
				else
				{
					if (((yy1 >= -WIN_HEIGHT / 2) && (yy1 <= WIN_HEIGHT / 2) && (xx1 >= -WIN_LENGTH / 2) && (xx1 <= WIN_LENGTH / 2)) == 0)
						break;
				}

				//Sleep(1);
				//	printf("%f\t%f\n", bb1.x, bb1.y);
				//getch();
			}



			xx2 = elec2[j].x;
			yy2 = elec2[j].y;
			while (1)
			{
				a1 = Strength(xx2, yy2, Q1.x, Q1.y, Q1.q, Q2.x, Q2.y, Q2.q);
				bb1 = _origin(xx2, yy2, a1);
				putpixel((int)bb1.x, (int)bb1.y, Color);
				putpixel((int)bb1.x, -(int)bb1.y, Color);
				xx2 = bb1.x;
				yy2 = bb1.y;
				if (Q1.q*Q2.q < 0)
				{
					if (((yy2 >= -WIN_HEIGHT / 2) && (yy2 <= WIN_HEIGHT / 2) && (xx2 >= -WIN_LENGTH / 2) && (xx2 <= WIN_LENGTH / 2) && xx2 >= 0) == 0)
						break;
				}
				else
				{
					if (((yy2 >= -WIN_HEIGHT / 2) && (yy2 <= WIN_HEIGHT / 2) && (xx2 >= -WIN_LENGTH / 2) && (xx2 <= WIN_LENGTH / 2)) == 0)
						break;
				}

				//Sleep(1);
				//printf("%f\t%f\n", bb1.x, bb1.y);
				//getch();
			}

		}

		_getch();

		
		//Command();

		InputBox(ins, 50, "请输入指令：\n\t1:\t 改变电场线起点半径\n\t2:\t改变画出的电场线数量\n\t3:\t改变左电荷横坐标\n\t4:\t改变右电荷横坐标\n\t5:\t改变左电荷电荷量\n\t6:\t改变右电荷电荷量\n\t");
		Command(ins);
		cleardevice();
	}


	_getch();
	closegraph();
	return 0;
}



void Init_Binary_Charge(double x1, double y1, double q1, double x2, double y2, double q2)
{
	setcolor(BLACK);//设置颜色
	line(-WIN_LENGTH / 2, 0, WIN_LENGTH / 2, 0);//画坐标轴
	line(0, WIN_HEIGHT / 2, 0, -WIN_HEIGHT / 2);
	putpixel((int)x1, (int)y1, Color);
	putpixel((int)x2, (int)y2, Color);
	setcolor(Color);
	circle((int)x1, (int)y1, (int)RADIUS);
	circle((int)x2, (int)y2, (int)RADIUS);
}


ElecSpot InitPoint(double x, double y, double r, double angle)
{
	ElecSpot point = { x + r*cos(PI_180*(angle + ANGLE)),y + r*sin(PI_180*(angle + ANGLE)) };
	return point;
}


//E=K*Q/(R*R)		K=9.0x10^9N*M^2/(C^2;l;l)
STRENGTH Strength(double x, double y, double x1, double y1, double q1, double x2, double y2, double q2)
{
	STRENGTH i, qf1, qf2;

	double r1, r2, K, dx1, dy1, dx2, dy2;
	
	K = 9E9;

	dx1 = x - x1;
	dy1 = y - y1;
	dx2 = x - x2;
	dy2 = y - y2;


	r1 = sqrt((dx1*dx1) + (dy1*dy1));
	r2 = sqrt((dx2*dx2) + (dy2*dy2));


	qf1.str = K*q1 / (r1*r1);
	qf2.str = K*q2 / (r2*r2);

	qf1.strx = qf1.str*dx1 / r1;
	qf1.stry = qf1.str*dy1 / r1;
	qf2.strx = qf2.str*dx2 / r2;
	qf2.stry = qf2.str*dy2 / r2;

	i.str = qf1.str + qf2.str;
	i.strx = qf1.strx + qf2.strx;
	i.stry = qf1.stry + qf2.stry;
	i.r1 = r1;
	i.r2 = r2;
	return i;
}

ElecSpot _origin(double x,double y, STRENGTH strength)
{
	ElecSpot i;

	i.x = x + STEP*strength.strx / strength.str;
	i.y = y + STEP*strength.stry / strength.str;
	return i;
}




//double Q_Q(double q1, double q2)
//{
//	double qq;
//	qq = q1 / q2;
//	if (qq < 0)
//	{
//		qq = -qq;
//	}
//	qq = pow(qq, 1 / 3);
//	return qq;
//}




void Command(char s[])
{

//	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
//	printf("请输入指令：\n\n");
//	printf("R:\t 改变电场线起点半径\t\t\t     X:\t改变\n");
//	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	

	int com, comm;//转换用户输入
	sscanf(s, "%d", &com);// 将用户输入转换为数字
	
	switch (com)
	{
	case 1:
		InputBox(ins, 50, "请输入电场线起点半径(适宜范围：1到10)：\n");
		sscanf(s, "%d", &comm);
		RADIUS = comm;
		break;
	case 2:
		InputBox(ins, 50, "请输入要画出的电场线数量(可取值：4、8、16、32、22、44、88、176)：\n");
		sscanf(s, "%d", &comm);
		NUM = comm / 2;
		break;
	case 3:
		InputBox(ins, 50, "请输入左电荷横坐标（-400到200）：\n");
		sscanf(s, "%d", &comm);
		Q1.x = comm;
		break;
	case 4:
		InputBox(ins, 50, "请输入右电荷横坐标（-200到400）：\n");
		sscanf(s, "%d", &comm);
		Q2.x = comm;
		break;
	case 5:
		InputBox(ins, 50, "请输入左电荷电荷量（1-1000）：\n");
		sscanf(s, "%d", &comm);
		Q1.q = comm;
		break;
	case 6:
		InputBox(ins, 50, "请输入右电荷电荷量（1-1000）：\n");
		sscanf(s, "%d", &comm);
		Q2.q = comm;
		break;
	default:
		HWND hwnd;
		hwnd = GetHWnd();
		MessageBox(hwnd, "输入错误！请重新输入！", "ERROR", MB_OK);
			break;
	}
}