/*
S�߹�Դ  G�ڹ���	����S1��S2	����S�Ⱦ�	���S1��S2����ɹ�Դ������λ��ͬ��S1��S2֮��ľ�����    d      �������ľ�����   D

ͬ����ͬƵ�ʡ��к㶨������������ɫ��Դ�����������йⲨ�ĵ���

���ϸ���������ֱ���Ƶļ��Ϊ��x=��l/d������dΪ�����������ĵļ�࣬���ǵ�ɫ�Ⲩ����������˫����������ƽ�еĿ������ľ��롣		

��ɫ����	������Χ			��ɫֵ Red	��ɫֵ Green	��ɫֵ Blue
��			770��622nm			255			0				0
���ɫ							255			0				255
��			622��597nm
��			597��577nm			255			255				0
��			577��492nm			0			255				0
������		492��455nm			0			0				255
��			455��350nm
��ɫ							0			255				255	
*/

#include<acllib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>

#define WIN_LENGTH 1400
#define WIN_HEIGHT 800

//---------------------------------------------------------------------------------------ȫ�ֱ��������붨��
typedef struct {
	int R;
	int G;
	int B;
	int A;
}rgba_def;

double pointx = 200;//�߹�Դ��������
const double pointy = WIN_HEIGHT / 2;//�����겻�ܸı�
double screen_X = WIN_LENGTH - 200;//��������
double screen_L = WIN_HEIGHT; //���߶�
double hole_wide = 6;//�׿�
double hole_X = 400;
double hole1_Y = 350, hole2_Y = WIN_HEIGHT - hole1_Y;
bool flag = 0;
double JianJu = 0;//���Ƽ��
int WaveLength = 660;//����
int i, j;
rgba_def rgba_var;
double suofangbili = 80;
const int WaveNum = 5;//����+1
int radius[WaveNum] = { 0,40,80,120,160 };//�߹�Դ��˫��֮��Բ���뾶
int radius_s_p[WaveNum] = { 0,(int)((screen_X - hole_X) / (hole_X - pointx)*40),(int)((screen_X - hole_X) / (hole_X - pointx)*80),(int)((screen_X - hole_X) / (hole_X - pointx)*120),(int)((screen_X - hole_X) / (hole_X - pointx)*160) };//˫������֮��Բ���뾶
int step = 10;//ÿ��ʱ��ι⴫���ľ���
int step_s_p = 0;

//--------------------------------------------------------------------------------------------����ԭ������
void TimerListener(int id);
void initdevice();
void MouseListener(int x, int y, int button, int event);
void KBListener(int key, int event);
void PaintTiaoWen(int red, int green, int blue);//������
rgba_def lambdaToColor(double lambda, double gamma, double intensityMax);//���㲨����Ӧ��RGB
void LightSpread();//��Ĵ���

//----------------------------------------------------------------------------------��ں���
int Setup()
{
	initConsole();
	initWindow("��ĸ���", 120, 0, WIN_LENGTH, WIN_HEIGHT);
	
	printf("��ǰ����Ϊ��%d\n", WaveLength);

	beginPaint();
	setTextSize(20);
	endPaint();

	JianJu = (screen_X - hole_X) / ((hole2_Y - 3) - (hole1_Y + 3))*WaveLength/ suofangbili;
	step_s_p = (int)((screen_X - hole_X) / (hole_X - pointx) * step);//��֤�߹�Դ��˫��֮��Ĺ��˫������֮��Ĺ��Ӧ
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

//--------------------------------------------------------------------------------------------------�Զ��庯��
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
	//x��
	line((int)hole_X, WIN_HEIGHT / 2, int(screen_X), WIN_HEIGHT / 2);

	//��
	line((int)screen_X, (int)((WIN_HEIGHT - screen_L) / 2), (int)screen_X, (int)((WIN_HEIGHT + screen_L) / 2));
	paintText((int)(screen_X - 30), 20, "��");

	//����
	line((int)hole_X, 0, (int)hole_X, (int)(hole1_Y - hole_wide / 2));
	line((int)hole_X, (int)(hole2_Y + hole_wide / 2), (int)hole_X, WIN_HEIGHT);
	line((int)hole_X, (int)(hole1_Y + hole_wide / 2), (int)hole_X, (int)(hole2_Y - hole_wide / 2));

	paintText((int)(hole_X - 30), 20, "˫");
	paintText((int)(hole_X - 30), 40, "��");


	//���Ȳ���
	//�߹�Դ
	line((int)pointx, (int)(pointy + hole_wide/2), (int)pointx, (int)pointy + 300);
	line((int)pointx, (int)(pointy - hole_wide/2), (int)pointx, (int)pointy - 300);

	paintText((int)pointx - 30, (int)pointy - 100, "��");
	paintText((int)pointx - 30, (int)pointy - 80, "��");
	paintText((int)pointx - 30, (int)pointy - 60, "Դ");


	//����ͬ�����Ĺ�Դ

	setPenColor(RGB(rgba_var.R, rgba_var.G, rgba_var.B));
	setBrushColor(RGB(rgba_var.R, rgba_var.G, rgba_var.B));
	rectangle(175, (int)(pointy - hole_wide / 2), (int)pointx+2, (int)(pointy + hole_wide / 2));

	//һЩ˵��
	setTextColor(RGB(0, 0, 255));
	paintText(20, 20, "��ǰ�߹�Դ����������̨");
	paintText(20, 50, "����+��-�ı��߹�Դ����");
	paintText(20, 700, "�����ָı�˫��λ��");
	paintText(20, 720, "Ctrl+�����ָı���λ��");
	paintText(20, 740, "���¼��ı�˫����");
	

	endPaint();
} 

void PaintTiaoWen(int red,int green,int blue)
{
	int Red, Green, Blue;

	beginPaint();

	setPenStyle(PEN_STYLE_SOLID);

	for (i = 0; i < 50; i++)
	{
		//�ݴ�
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

		step_s_p = (int)((screen_X - hole_X) / (hole_X - pointx) * step);//��֤�߹�Դ��˫��֮��Ĺ��˫������֮��Ĺ��Ӧ





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
			flag = 1;//ctrl������		����λ��
		}
		else if (event == 1)
		{
			flag = 0;//ctrl���ɿ�		������λ��
		}
	}

	if ((key == 107 || key == 187) && event == 0)
	{

		WaveLength+=10;
		printf("��ǰ����Ϊ��%d\n", WaveLength);
	}
	else if ((key == 109 || key == 189) && event == 0)
	{
		WaveLength-=10;
		printf("��ǰ����Ϊ��%d\n", WaveLength);
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


//�ҵ��ֻ� 2018 / 6 / 24 12 : 27 : 59		�W���o��	����԰��ҳ��ϵ����	���ת��ָ�� ���� �� RGB ��ɫ��


//ָ������ת����RGBA��ɫ
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

	//�ڿɼ����׵ı�Ե��ǿ�Ƚϵ͡�
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

	//1953��������NTSC����ʱ,�������ӫ����ļ����������ȹ�ʽ����
	int Y = static_cast<int>(0.212671*r + 0.715160*g + 0.072169*b);

	//٤������ gamma
	//����ǿ�� intensityMax
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
	//ÿһ��time ����һ���Ⲩ

	int index;//�Ⲩ���

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




