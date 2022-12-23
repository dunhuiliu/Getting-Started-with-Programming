#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>

//----------------------------�궨��------------------------------
#define WIN_LENGTH 1200//���ڳ�
#define WIN_HEIGHT 800//���ڸ�
#define PI_180 (3.1415926/180)	//��/180
#define hc 1.24					//��ϳ���hc=1.24nm*keV			��=hc/E=1.24/E nm*keV
#define R1 0.053				//��̬����뾶(��λ��nm)
#define E1 -13.6				//��̬��������λ��ev��
#define NUM 7					//�ܼ���
#define ENLARGE 150				//��ͼ�뾶�Ŵ�ϵ��
#define CHAR_TIME 200			//�ַ�����ʱ��
#define CHAR_X -150				//�ַ�������
#define CHAR_Y -50				//�ַ�������

//--------------------------�Զ����������--------------------------
typedef struct    //��������
{
	double r;//���Ӱ뾶
	double e;//��������
}ELEC;

typedef struct		//����λ��
{
	double x;//���Ӻ�����
	double y;//����������
}COORDINATE;

//-----------------------------����ԭ��----------------------------
void InitBkimg();//��ʼ�����
double radius(int n);//�������뾶
double Energy(int n);//�����������
COORDINATE Coor(int x, double R);//�������λ��



void Xi_Name_Print(int xi);//����ϵ����ʾ
void Put_Photon(int x, int y);//�ͷŹ���
void Demo_Line(double x1, double y1, double x2, double y2);//����ʾ�ߣ���ͷ��
void attribute(double e1, double e2, int xii, int kk);//ԾǨ������ʾ

//----------------------------ȫ�ֱ�������-------------------------
ELEC elec;//��������
COORDINATE pos;//����λ��

//-------------------------------������-----------------------------
int main()
{
	int i, j,k,xi,o=0, count = 1,cnt;//������������
	int PX, PY;//�����ƶ�����
	initgraph(WIN_LENGTH, WIN_HEIGHT);//��ʼ������

	setbkcolor(WHITE);//���ñ���ɫ
	cleardevice();//����
	Sleep(500);//��ʼ��ͣ0.5����ʾЧ������

	setorigin(WIN_LENGTH / 2, WIN_HEIGHT / 2);//��������ԭ��

	setlinecolor(BLACK);//���û�����ɫ
	//����ͼ�����ɫ
	setfillcolor(RGB(255, 128, 0));		//�ٻ�
//	setfillcolor(RGB(0, 255, 255));			//��

	for (xi = 1; xi < NUM-1; xi++)//����ϵ
	{
		Xi_Name_Print(xi);//��ӡϵ��
		for (k = xi+1; k <= NUM; k++)//ÿ��ϵ�ı���
		{
			
			for (j = k, elec.e = Energy(j), elec.r = radius(j), cnt = 2; cnt; j = xi,elec.r = radius(j))//ÿһ������
			{
				if (cnt == 2)
				{
					Demo_Line(-radius(j), 0, -radius(xi), 0);//����ʾ��
					//printf("e1=%lf\te2=%lf", elec.e, Energy(xi));
					attribute(elec.e, Energy(xi), xi, k);//��ӡ������������������ɫ��Ϣ
				}
				cnt--;//��������
				for (i = 180, o = 0; i != 177 && i != 178 && i != 176; i += 8, o += 1)//�ԵȽǶ���ͼ��ÿһ֡
				{
					if (i >= 360)
					{
						i=0;
					}

				pos = Coor(i, elec.r);//�����������


				if (i == int(elec.r) || i == -int(elec.r))
				{
					count++;
				}
			
				setlinestyle(PS_SOLID, 1);	//���û�����ʽΪֱ��
				setlinecolor(BLACK);
				fillcircle(pos.x, pos.y, 5);//h�����ӡ��������������Բ

				if (cnt == 0 && PX - 5 * o>-WIN_LENGTH / 2)//����ԾǨ�ܼ���ͬ����ͬ��ɫ�ķ������
				{
					if (xi == 1)
					{
						setlinecolor(RGB(172, 0, 172));
					}
					else if (xi == 2)
					{
						if (k == 3)    //�ɼ�������
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
					Put_Photon(PX - 5 * o, PY);//������
				}

				Sleep(100);


				InitBkimg();//��ʼ�������ܼ�Բ
				}

				if (cnt == 1)//�����ƶ���������
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

//-----------------------------�Զ��庯��------------------------------
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
	settextstyle(15, 15, L"����");
	settextcolor(BLUE);
	outtextxy(radius(1) + 1, 0, 'K');
	outtextxy(radius(2) + 5, 0, 'L');
	outtextxy(radius(3) + 5, 0, 'M');
	outtextxy(radius(4) + 5, 0, 'N');
	outtextxy(radius(5) + 5, 0, 'O');
	outtextxy(radius(6) + 5, 0, 'P');
	outtextxy(radius(7) + 5, 0, 'Q');
}

double radius(int n)//�����뾶
{
	return R1*n*n*ENLARGE;
}

double Energy(int n)//���ܼ�����
{
	return E1 / (n*n);
}

COORDINATE Coor(int x, double R)//�������λ��
{
	COORDINATE E;
	E.x = R*cos(x*PI_180);
	E.y = R*sin(x*PI_180);
	return E;
}


void Xi_Name_Print(int xi)//��ӡϵ��
{
	float count;
	cleardevice();
	settextstyle(50, 50, L"����");//�����ֵĴ�С����ʽ
	switch (xi)
	{
	case 1:
		for (count=0;count<=10;count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));//��ɫ���䡪��������ǳ
			outtextxy(CHAR_X, CHAR_Y, L"����ϵ");
			Sleep(CHAR_TIME);//ͣ��ʱ��
			cleardevice();
		}
		break; 
	case 2:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"�Ͷ�ĩϵ");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break;
	case 3:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"����ϵ");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break; 
	case 4:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"������ϵ");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break; 
	case 5:
		for (count = 0; count <= 10; count++)
		{
			settextcolor(RGB(255, count*25.5, count * 25.5));
			outtextxy(CHAR_X, CHAR_Y, L"�շ��ϵ");
			Sleep(CHAR_TIME);
			cleardevice();
		}
		break;
	}
}

void Put_Photon(int x,int y)//(x,y)Ϊ����β�����꣬���ݲ��������ӣ�ʹ�����ƶ�
{
	int length = 5;
	setlinestyle(PS_SOLID, 3);//���û�����ʽ
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

void Demo_Line(double x1, double y1, double x2, double y2)//����ʾ��
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

	settextstyle(50, 50, L"����");
	settextcolor(RED);
	outtextxy(500, -350, L"��");
	outtextxy(500, -250, L"��");
	outtextxy(500, -150, L"��");
	outtextxy(500, -50, L"��");
	outtextxy(500, 50, L"��");
	outtextxy(500, 150, L"��");
}

void attribute(double e1, double e2, int xii, int kk)//��ӡ���������������������ɫ����Ϣ
{
	TCHAR s[50], d[50];
	settextstyle(15, 15, L"����");
	settextcolor(BLACK);
	outtextxy(-580, -380, L"�ܼ��ܲ�:      eV");
	outtextxy(-580, -300, L"���Ӳ���:      nm");
	_stprintf_s(s, _T("%.2f"), e1 - e2);
	_stprintf_s(d, _T("%.2f"), 1000 * hc / (e1 - e2));
	settextcolor(RGB(255, 128, 0));
	//printf("\n%lf\t%lf\n", e1 - e2, 1000 * hc / (e1 - e2));
	outtextxy(-450, -380, s);
	outtextxy(-450, -300, d);
	if (xii == 1 || (xii == 2 && kk > 6))
	{
		settextcolor(RGB(172, 0, 172));
		outtextxy(-560, -220, L"�����");
	}
	else if (xii == 2 && kk == 3)
	{
		settextcolor(RED);
		outtextxy(-560, -220, L"�ɼ��⣨��ɫ��");
	}
	else if (xii == 2 && kk == 4)
	{
		settextcolor(GREEN);
		outtextxy(-560, -220, L"�ɼ��⣨��ɫ��");
	}
	else if (xii == 2 && kk == 5)
	{
		settextcolor(BLUE);
		outtextxy(-560, -220, L"�ɼ��⣨��ɫ��");
	}
	else if (xii == 2 && kk == 6)
	{
		settextcolor(RGB(172, 0, 172));
		outtextxy(-560, -220, L"�ɼ��⣨��ɫ��");
	}
	else {
		settextcolor(RED);
		outtextxy(-560, -220, L"�����");
	}

	_getch();
}