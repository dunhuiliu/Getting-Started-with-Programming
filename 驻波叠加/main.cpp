#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include <windows.h>

#define WIN_LENGTH 1200//窗口长
#define WIN_HEIGHT 800//窗口高
#define PI 3.14159//π
#define XO	50//横坐标坐标开始
#define X_X (WIN_HEIGHT/4)//三个x轴间距


void screen();//清屏并坐标轴初始化
void MouseMessage();//鼠标消息


MOUSEMSG msg = { 0 };//鼠标消息
HWND hwnd;//窗口句柄

int speed = 10;//时间增量

typedef struct//波函数的系数结构体
{
	double y;
	double a;
	double w;
	double v;
	double w1;
}COEF;

COEF F1 = { 0, 100, 6 * PI / 1000 ,1,0 }, F2 = { 0,100,6 * PI / 1000,1,0 };//初始化函数的系数
//		y1=a1*cos(w1*(t-x/v1)+f)+w11		y2=a2*cos(w2*(t+x/v2)+f)+w22


int main()
{
	initgraph(WIN_LENGTH, WIN_HEIGHT, 1);//初始化图形窗口


	setbkcolor(WHITE);//设置背景色为白色
	double t, x, f;//定义  t为时间变量		x为横坐标变量		f为波的初相位
	

	screen();//清屏并坐标轴初始化

	f = 0;//设置初相位为0

	for (t = 0; 1; t +=speed)//时间永远增加
	{
		screen();//清屏并坐标轴初始化
		setorigin(0, 0); //设置(0, 0)为坐标原点
		//显示控制按键
		outtextxy(200, 50, L"变频");
		outtextxy(400, 50, L"变速");
		outtextxy(600, 50, L"变幅");

		for (x = 0; x<1200 - XO; x += 0.5)//循环画点    画到1200 - XO
		{
			setorigin(XO, X_X);//设置(XO, X_X)为坐标原点
			F1.y = F1.a*cos(F1.w*(t - x / F1.v) + f) + F1.w1;//求第一个波函数的纵坐标
			putpixel(x, F1.y, GREEN);//用绿色画点

			setorigin(XO, X_X * 2);//设置(XO, X_X * 2)为坐标原点
			F2.y = F2.a*cos(F2.w*(t + x / F2.v) + f) + F2.w1;//求第二个波函数的纵坐标
			putpixel(x, F2.y, RED);//用红色画点
			setorigin(XO, X_X * 3);//设置(XO, X_X * 3)为坐标原点
			putpixel(x, F1.y + F2.y, BLUE);//用蓝色画点
		}
		
		Sleep(100);//视觉暂留时间
		MouseMessage();//鼠标消息
	}

	return 0;
}


void screen()//清屏并坐标轴初始化
{
	cleardevice();//清屏
	setcolor(BLACK);//设置线的颜色
	setorigin(XO, 0);//设置（XO，0）为坐标原点
	//画坐标轴
	line(0, X_X, WIN_LENGTH, X_X);
	line(0, X_X * 2, WIN_LENGTH, X_X * 2);
	line(0, X_X * 3, WIN_LENGTH, X_X * 3);
	line(0, 0, 0, WIN_HEIGHT);
}


void MouseMessage()
{
	int result;
	msg = GetMouseMsg();//获取鼠标消息
	switch (msg.uMsg)//鼠标消息
	{
		case WM_LBUTTONDOWN://鼠标左击
			FlushMouseMsgBuffer();// 清空鼠标消息缓冲区
			if (msg.x > 190 && msg.x < 240 && msg.y>40 && msg.y < 60)//如果鼠标点击按键所在区域
				{
				hwnd = GetHWnd();//提示窗口置前
				result = MessageBox(hwnd, L"是否变频？", L"提示", MB_ICONINFORMATION | MB_OKCANCEL);//提示窗口
				if (result == IDOK)//如果选择确定
				{
				MessageBox(hwnd, L"请在控制台输入", L"提示", MB_OK);//提示窗口
				printf("请输入频率（0.3—5）：\nv1:");//提示信息
				scanf("%lf", &F1.v);//接收频率输入
				printf("\nv2:");
				scanf("%lf", &F2.v);
				getchar();//吃掉回车
				}
				}
				else if (msg.x > 390 && msg.x < 440 && msg.y>40 && msg.y < 60)//如果鼠标点击按键所在区域
				{
					hwnd = GetHWnd();
					result = MessageBox(hwnd, L"是否变速？", L"提示", MB_ICONINFORMATION | MB_OKCANCEL);
					if (result == IDOK)
					{
						MessageBox(hwnd, L"请在控制台输入", L"提示", MB_OK);
						printf("请输入速度（1—500）:\n");
						scanf("%d", &speed);
						getchar();
					}
				}
				else if (msg.x > 590 && msg.x < 640 && msg.y>40 && msg.y < 60)
				{
					hwnd = GetHWnd();
					result = MessageBox(hwnd, L"是否变幅？", L"提示", MB_ICONINFORMATION | MB_OKCANCEL);
					if (result == IDOK)
					{
						MessageBox(hwnd, L"请在控制台输入", L"提示", MB_OK);
						printf("请输入振幅（1—50）：\na1:");
						scanf("%lf", &F1.a);
						printf("\na2:");
						scanf("%lf", &F2.a);
						printf("请输入上下浮动（0—50）：\nw1:");
						scanf("%lf", &F1.w1);
						printf("\nw2:");
						scanf("%lf", &F2.w1);
						getchar();
					}
				}
	}
}