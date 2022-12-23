/***************************************************
�ļ����ƣ�main.cpp
�ļ����������ɵ����ߵļ����ģ��
���뻷����VS 2015
����޸ģ�
	<2018��6��1��>
***************************************************/
//-----------------------------ͷ�ļ�-------------------------
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
//#include<bios.h>
//#include<dos.h>

//-----------------------------�궨��--------------------------
#define WIN_LENGTH	1200			//���ڳ�
#define WIN_HEIGHT	700				//���ڸ�
#define PI_180		(3.1415926/180)	//��/180
#define ANGLE 2						//��ʼ�Ƕ�

//����
typedef struct
{
	double x;
	double y;
	double q;//�����
}CHARGE;



//�糡ǿ��
typedef struct
{
	double str;//�糡ǿ�ȵĴ�С
	double strx;//�糡ǿ��x�����Ĵ�С
	double stry;//�糡ǿ��y�����Ĵ�С
	double r1; //�糡����ĳ�㵽����һ�ľ���
	double r2;//�糡����ĳ�㵽���ɶ��ľ���
}STRENGTH;

//�������������
typedef struct
{
	double x;
	double y;
}ElecSpot;


//----------------------------����ԭ��-------------------------
void Init_Binary_Charge(double x1, double y1, double q1, double x2, double y2, double q2);		//��ʼ���������
ElecSpot InitPoint(double x, double y, double r, double angle);//��ʼ����ʼ��
STRENGTH Strength(double x, double y, double x1, double y1, double q1, double x2, double y2, double q2);//����������ĵ糡ǿ��
ElecSpot _origin(double x, double y, STRENGTH strength);//������һ�������
void Command(char s[]);//��ȡ�û�����
//double Q_Q(double q1, double q2);


//---------------------------ȫ�ֱ�������----------------------
double RADIUS = 5;			//�糡����ʼ�뾶
double STEP = 0.1;//����
int NUM = 22;			//����������(��ȡֵ��2��4��8��16��11��22��44��88)
char com = 0;//ָ������
CHARGE Q1 = { -200,0, -100 };//���һ
CHARGE	Q2 = { 200,  0,  100 };//��ɶ�
int Color = RGB(255, 128, 0);//�糡����ɫ
char ins[50];//�û�����洢
//double Q1_Q2;//(���ڿ������ֵ�ɵ糡�ߵ���ֹ);���ֵ������ǿΪ�㴦�й�ϵ��q1/q2=(r1/r2)^3������	֤������k*q1/(r1^2)	*	y/r1	=	k*q2/(r2^2)	*	y/r2��


//-----------------------------������--------------------------
int main()
{
	ElecSpot elec1[100], elec2[100];
	double dif_ang;
	int i = 0, j = 0;
	STRENGTH a1;
	ElecSpot bb1;
	double xx1, yy1, xx2, yy2;

	initgraph(WIN_LENGTH, WIN_HEIGHT);
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();//����
	setorigin(WIN_LENGTH / 2, WIN_HEIGHT / 2);	//������Ļ����Ϊ����ԭ��


	while (1)
	{
		Init_Binary_Charge(Q1.x, Q1.y, Q1.q, Q2.x, Q2.y, Q2.q);

		//�ڵ��Ȧ�ϳ�ʼ�����ɸ���		��2�ȵ�178��ȡ��		�ԵȲ�Ƕ�ȡ��
		dif_ang = (178 - 2) / NUM;
		for (i = 0; i < NUM; i++)
		{
			elec1[i] = InitPoint(Q1.x, Q1.y, RADIUS, (i + 1)*dif_ang);
			elec2[i] = InitPoint(Q2.x, Q2.y, RADIUS, (176 - (i + 1)*dif_ang));
			putpixel((int)elec1[i].x, (int)elec1[i].y, Color);//(int)xx,ǿ�ư�xxת��Ϊint ��
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

		InputBox(ins, 50, "������ָ�\n\t1:\t �ı�糡�����뾶\n\t2:\t�ı仭���ĵ糡������\n\t3:\t�ı����ɺ�����\n\t4:\t�ı��ҵ�ɺ�����\n\t5:\t�ı����ɵ����\n\t6:\t�ı��ҵ�ɵ����\n\t");
		Command(ins);
		cleardevice();
	}


	_getch();
	closegraph();
	return 0;
}



void Init_Binary_Charge(double x1, double y1, double q1, double x2, double y2, double q2)
{
	setcolor(BLACK);//������ɫ
	line(-WIN_LENGTH / 2, 0, WIN_LENGTH / 2, 0);//��������
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
//	printf("������ָ�\n\n");
//	printf("R:\t �ı�糡�����뾶\t\t\t     X:\t�ı�\n");
//	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	

	int com, comm;//ת���û�����
	sscanf(s, "%d", &com);// ���û�����ת��Ϊ����
	
	switch (com)
	{
	case 1:
		InputBox(ins, 50, "������糡�����뾶(���˷�Χ��1��10)��\n");
		sscanf(s, "%d", &comm);
		RADIUS = comm;
		break;
	case 2:
		InputBox(ins, 50, "������Ҫ�����ĵ糡������(��ȡֵ��4��8��16��32��22��44��88��176)��\n");
		sscanf(s, "%d", &comm);
		NUM = comm / 2;
		break;
	case 3:
		InputBox(ins, 50, "���������ɺ����꣨-400��200����\n");
		sscanf(s, "%d", &comm);
		Q1.x = comm;
		break;
	case 4:
		InputBox(ins, 50, "�������ҵ�ɺ����꣨-200��400����\n");
		sscanf(s, "%d", &comm);
		Q2.x = comm;
		break;
	case 5:
		InputBox(ins, 50, "���������ɵ������1-1000����\n");
		sscanf(s, "%d", &comm);
		Q1.q = comm;
		break;
	case 6:
		InputBox(ins, 50, "�������ҵ�ɵ������1-1000����\n");
		sscanf(s, "%d", &comm);
		Q2.q = comm;
		break;
	default:
		HWND hwnd;
		hwnd = GetHWnd();
		MessageBox(hwnd, "����������������룡", "ERROR", MB_OK);
			break;
	}
}