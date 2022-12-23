/*
S线光源  G遮光屏	狭缝S1、S2	且与S等距	因此S1、S2是相干光源，且相位相同；S1、S2之间的距离是    d      ，到屏的距离是   D

同方向、同频率、有恒定初相差的两个单色光源所发出的两列光波的叠加

杨氏干涉两相邻直条纹的间距为△x=λl/d，其中d为两个狭缝中心的间距，λ是单色光波波长，ι是双缝屏到和它平行的考察屏的距离。		

颜色名称	波长范围			红色值 Red	绿色值 Green	蓝色值 Blue
红			770～622nm			255			0				0
洋红色							255			0				255
橙			622～597nm
黄			597～577nm			255			255				0
绿			577～492nm			0			255				0
蓝、靛		492～455nm			0			0				255
紫			455～350nm
青色							0			255				255	
*/

#include<acllib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>

#define WIN_LENGTH 1400
#define WIN_HEIGHT 800

//---------------------------------------------------------------------------------------全局变量声明与定义
typedef struct {
	int R;
	int G;
	int B;
	int A;
}rgba_def;

double pointx = 200;//线光源横纵坐标
const double pointy = WIN_HEIGHT / 2;//纵坐标不能改变
double screen_X = WIN_LENGTH - 200;//屏横坐标
double screen_L = WIN_HEIGHT; //屏高度
double hole_wide = 6;//孔宽
double hole_X = 400;
double hole1_Y = 350, hole2_Y = WIN_HEIGHT - hole1_Y;
bool flag = 0;
double JianJu = 0;//条纹间距
int WaveLength = 660;//波长
int i, j;
rgba_def rgba_var;
double suofangbili = 80;
const int WaveNum = 5;//波数+1
int radius[WaveNum] = { 0,40,80,120,160 };//线光源与双缝之间圆弧半径
int radius_s_p[WaveNum] = { 0,(int)((screen_X - hole_X) / (hole_X - pointx)*40),(int)((screen_X - hole_X) / (hole_X - pointx)*80),(int)((screen_X - hole_X) / (hole_X - pointx)*120),(int)((screen_X - hole_X) / (hole_X - pointx)*160) };//双缝与屏之间圆弧半径
int step = 10;//每个时间段光传播的距离
int step_s_p = 0;

//--------------------------------------------------------------------------------------------函数原型声明
void TimerListener(int id);
void initdevice();
void MouseListener(int x, int y, int button, int event);
void KBListener(int key, int event);
void PaintTiaoWen(int red, int green, int blue);//画条纹
rgba_def lambdaToColor(double lambda, double gamma, double intensityMax);//计算波长对应的RGB
void LightSpread();//光的传播

//----------------------------------------------------------------------------------入口函数
int Setup()
{
	initConsole();
	initWindow("光的干涉", 120, 0, WIN_LENGTH, WIN_HEIGHT);
	
	printf("当前波长为：%d\n", WaveLength);

	beginPaint();
	setTextSize(20);
	endPaint();

	JianJu = (screen_X - hole_X) / ((hole2_Y - 3) - (hole1_Y + 3))*WaveLength/ suofangbili;
	step_s_p = (int)((screen_X - hole_X) / (hole_X - pointx) * step);//保证线光源与双缝之间的光和双缝与屏之间的光对应
	rgba_var = lambdaToColor(WaveLength, 0.8, 255.0);

	initdevice();
	LightSpread();
	PaintTiaoWen(rgba_var.R, rgba_var.G, rgba_var.B);
	
	registerMouseEvent(MouseListener);
	registerKeyboardEvent(KBListener);
	registerTimerEvent(TimerListener);
	startTimer(0, 100);

	return 0;
}

//--------------------------------------------------------------------------------------------------自定义函数
void TimerListener(int id)
{
	initdevice();

	LightSpread();

	PaintTiaoWen(rgba_var.R, rgba_var.G, rgba_var.B);
}

void initdevice()
{
	beginPaint();
	clearDevice();
	setTextColor(RGB(0, 255, 0));
	setPenColor(BLACK);
	setPenStyle(PEN_STYLE_SOLID);
	//x轴
	line((int)hole_X, WIN_HEIGHT / 2, int(screen_X), WIN_HEIGHT / 2);

	//屏
	line((int)screen_X, (int)((WIN_HEIGHT - screen_L) / 2), (int)screen_X, (int)((WIN_HEIGHT + screen_L) / 2));
	paintText((int)(screen_X - 30), 20, "屏");

	//狭缝
	line((int)hole_X, 0, (int)hole_X, (int)(hole1_Y - hole_wide / 2));
	line((int)hole_X, (int)(hole2_Y + hole_wide / 2), (int)hole_X, WIN_HEIGHT);
	line((int)hole_X, (int)(hole1_Y + hole_wide / 2), (int)hole_X, (int)(hole2_Y - hole_wide / 2));

	paintText((int)(hole_X - 30), 20, "双");
	paintText((int)(hole_X - 30), 40, "缝");


	//暂先不动
	//线光源
	line((int)pointx, (int)(pointy + hole_wide/2), (int)pointx, (int)pointy + 300);
	line((int)pointx, (int)(pointy - hole_wide/2), (int)pointx, (int)pointy - 300);

	paintText((int)pointx - 30, (int)pointy - 100, "线");
	paintText((int)pointx - 30, (int)pointy - 80, "光");
	paintText((int)pointx - 30, (int)pointy - 60, "源");


	//换不同波长的光源

	setPenColor(RGB(rgba_var.R, rgba_var.G, rgba_var.B));
	setBrushColor(RGB(rgba_var.R, rgba_var.G, rgba_var.B));
	rectangle(175, (int)(pointy - hole_wide / 2), (int)pointx+2, (int)(pointy + hole_wide / 2));

	//一些说明
	setTextColor(RGB(0, 0, 255));
	paintText(20, 20, "当前线光源波长见控制台");
	paintText(20, 50, "键盘+、-改变线光源波长");
	paintText(20, 700, "鼠标滚轮改变双缝位置");
	paintText(20, 720, "Ctrl+鼠标滚轮改变屏位置");
	paintText(20, 740, "上下键改变双缝间距");
	

	endPaint();
} 

void PaintTiaoWen(int red,int green,int blue)
{
	int Red, Green, Blue;

	beginPaint();

	setPenStyle(PEN_STYLE_SOLID);

	for (i = 0; i < 50; i++)
	{
		//暂存
		Red = red;
		Green = green;
		Blue = blue;

		for (j = 0; j <= JianJu / 2; j += 1)
		{
			Red = (int)(red - (red / JianJu) * 2 * j);
			Green = (int)(green - (green / JianJu) * 2 * j);
			Blue = (int)(blue - (blue / JianJu) * 2 * j);
			

			setPenColor(RGB(Red, Green, Blue));

			line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 + i*JianJu + j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 + i*JianJu + j));
			line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 + (i + 1)*JianJu - j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 + (i + 1)*JianJu - j));

			line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 - i*JianJu - j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 - i*JianJu - j));
			line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 - (i + 1)*JianJu + j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 - (i + 1)*JianJu + j));

		}

		setPenColor(BLACK);
		line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 + i*JianJu + j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 + i*JianJu + j));
		line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 + (i + 1)*JianJu - j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 + (i + 1)*JianJu - j));

		line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 - i*JianJu - j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 - i*JianJu - j));
		line((int)screen_X + 10, (int)(WIN_HEIGHT / 2 - (i + 1)*JianJu + j), WIN_LENGTH, (int)(WIN_HEIGHT / 2 - (i + 1)*JianJu + j));

	}


	endPaint();
}

void MouseListener(int x, int y, int button, int event)
{
	//printf("button=%d\tevent=%d\n", button, event);

	if (event == 3 || event == 4)
	{
		if (button == 2)
		{
			if (event == 3)
			{
				if (flag == 0)
				{
					hole_X+=2;
				}
				else if (flag == 1)
				{
					screen_X+=2;
				}

			}
			else if (event == 4)
			{

				if (flag == 0)
				{
					hole_X-=2;
				}
				else if (flag == 1)
				{
					screen_X-=2;
				}
			}
		}

		JianJu = (screen_X - hole_X) / ((hole2_Y - 3) - (hole1_Y + 3))*WaveLength / suofangbili;

		step_s_p = (int)((screen_X - hole_X) / (hole_X - pointx) * step);//保证线光源与双缝之间的光和双缝与屏之间的光对应





//		for (int q = 0; q < WaveNum; q++)
//		{
//			radius[q] = q * 40;
//			radius_s_p[q] = (screen_X - hole_X) / (hole_X - pointx)*radius[q];
	//	}

		

	}
}

void KBListener(int key, int event)
{
	//printf("key=%d\tevent=%d\n", key, event);

	if (key == 17)
	{
		if (event == 0)
		{
			flag = 1;//ctrl键按下		变屏位置
		}
		else if (event == 1)
		{
			flag = 0;//ctrl键松开		变狭缝位置
		}
	}

	if ((key == 107 || key == 187) && event == 0)
	{

		WaveLength+=10;
		printf("当前波长为：%d\n", WaveLength);
	}
	else if ((key == 109 || key == 189) && event == 0)
	{
		WaveLength-=10;
		printf("当前波长为：%d\n", WaveLength);
	}

	if (hole1_Y < (WIN_HEIGHT - hole_wide) / 2-2)
	{
		if (key == 38 && event == 0)
		{
			hole1_Y--;
			hole2_Y = WIN_HEIGHT - hole1_Y;
		}
		else if (key == 40 && event == 0)
		{
			hole1_Y++;
			hole2_Y = WIN_HEIGHT - hole1_Y;
		}
	}
	else
	{
		hole1_Y-=1;
	}
	
	rgba_var = lambdaToColor(WaveLength, 0.8, 255.0);
	JianJu = (screen_X - hole_X) / ((hole2_Y - 3) - (hole1_Y + 3))*WaveLength / suofangbili;


}


//我的手机 2018 / 6 / 24 12 : 27 : 59		學海無涯	博客园首页联系管理	如何转换指定 波长 到 RGB 颜色？


//指定波长转换成RGBA颜色
rgba_def lambdaToColor(double lambda, double gamma, double intensityMax)
{
	double r, g, b, alpha;
	if (lambda >= 380.0 && lambda < 440.0) {
		r = -1.0 * (lambda - 440.0) / (440.0 - 380.0);
		g = 0.0;
		b = 1.0;
	}
	else if (lambda >= 440.0 && lambda < 490.0) {
		r = 0.0;
		g = (lambda - 440.0) / (490.0 - 440.0);
		b = 1.0;
	}
	else if (lambda >= 490.0 && lambda < 510.0) {
		r = 0.0;
		g = 1.0;
		b = -1.0 * (lambda - 510.0) / (510.0 - 490.0);
	}
	else if (lambda >= 510.0 && lambda < 580.0) {
		r = (lambda - 510.0) / (580.0 - 510.0);
		g = 1.0;
		b = 0.0;
	}
	else if (lambda >= 580.0 && lambda < 645.0) {
		r = 1.0;
		g = -1.0 * (lambda - 645.0) / (645.0 - 580.0);
		b = 0.0;
	}
	else if (lambda >= 645.0 && lambda <= 780.0) {
		r = 1.0;
		g = 0.0;
		b = 0.0;
	}
	else {
		r = 0.0;
		g = 0.0;
		b = 0.0;
	}

	//在可见光谱的边缘处强度较低。
	if (lambda >= 380.0 && lambda < 420.0) {
		alpha = 0.30 + 0.70 * (lambda - 380.0) / (420.0 - 380.0);
	}
	else if (lambda >= 420.0 && lambda < 701.0) {
		alpha = 1.0;
	}
	else if (lambda >= 701.0 && lambda < 780.0) {
		alpha = 0.30 + 0.70 * (780.0 - lambda) / (780.0 - 700.0);
	}
	else {
		alpha = 0.0;
	}

	//1953年在引入NTSC电视时,计算具有荧光体的监视器的亮度公式如下
	int Y = static_cast<int>(0.212671*r + 0.715160*g + 0.072169*b);

	//伽马射线 gamma
	//照明强度 intensityMax
	int R = r == 0.0 ? 0 : static_cast<int>(round(intensityMax * pow(r * alpha, gamma)));
	int G = g == 0.0 ? 0 : static_cast<int>(round(intensityMax * pow(g * alpha, gamma)));
	int B = b == 0.0 ? 0 : static_cast<int>(round(intensityMax * pow(b * alpha, gamma)));
	int A = static_cast<int>(alpha);

	rgba_def rgba_v;
	rgba_v.R = R;
	rgba_v.G = G;
	rgba_v.B = B;
	rgba_v.A = A;

	return rgba_v;
}

void LightSpread()
{
	int k;

	beginPaint();

	for (k = 0; k < WaveNum; k++)
	{
		if (k % 2 == 0)
		{
			setPenStyle(PEN_STYLE_SOLID);
		}
		else if (k % 2 == 1)
		{
			setPenStyle(PEN_STYLE_DASH);
		}

		radius[k] = radius[k] + step;

		if (radius[k] > hole_X - pointx)
		{
			radius[k] = step;
		}

		arc((int)(pointx - radius[k]), (int)(WIN_HEIGHT / 2 - radius[k]), (int)(pointx + radius[k]), (int)(WIN_HEIGHT / 2 + radius[k]), (int)pointx, (int)(WIN_HEIGHT / 2 + radius[k]), (int)pointx, (int)(WIN_HEIGHT / 2 - radius[k]));
	}


	for (k = 0; k < WaveNum; k++)
	{
		if (k % 2 == 0)
		{
			setPenStyle(PEN_STYLE_SOLID);
		}
		else if (k % 2 == 1)
		{
			setPenStyle(PEN_STYLE_DASH);
		}

		radius_s_p[k] = radius_s_p[k] + step_s_p;

		if (radius_s_p[k] > screen_X - hole_X)
		{
			radius_s_p[k] = step_s_p;
		}

		arc((int)(hole_X - radius_s_p[k]), (int)(hole1_Y - radius_s_p[k]), (int)(hole_X + radius_s_p[k]), (int)(hole1_Y + radius_s_p[k]), (int)hole_X, (int)(hole1_Y + radius_s_p[k]), (int)hole_X, (int)(hole1_Y - radius_s_p[k]));
		arc((int)(hole_X - radius_s_p[k]), (int)(hole2_Y - radius_s_p[k]), (int)(hole_X + radius_s_p[k]), (int)(hole2_Y + radius_s_p[k]), (int)hole_X, (int)(hole2_Y + radius_s_p[k]), (int)hole_X, (int)(hole2_Y - radius_s_p[k]));
	}
	endPaint();
}











/*
typedef struct BODONG {
	int radius;
	BODONG* next;
}BO;

void LightSpread()
{
	//每一个time 产生一个光波

	int index;//光波间隔

	static int boshu;

	BO* head;



	beginPaint();
	arc((int)(pointx - radius[0]), (int)(WIN_HEIGHT / 2 - radius[0]), (int)(pointx + radius[0]), (int)(WIN_HEIGHT / 2 + radius[0]), (int)pointx, (int)(WIN_HEIGHT / 2 + radius[0]), (int)pointx, (int)(WIN_HEIGHT / 2 - radius[0]));
	arc((int)(pointx - radius[1]), (int)(WIN_HEIGHT / 2 - radius[1]), (int)(pointx + radius[1]), (int)(WIN_HEIGHT / 2 + radius[1]), (int)pointx, (int)(WIN_HEIGHT / 2 + radius[1]), (int)pointx, (int)(WIN_HEIGHT / 2 - radius[1]));


	endPaint();
	radius[0]++;

	radius[1]++;



}
*/




