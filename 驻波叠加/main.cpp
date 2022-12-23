#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include <windows.h>

#define WIN_LENGTH 1200//���ڳ�
#define WIN_HEIGHT 800//���ڸ�
#define PI 3.14159//��
#define XO	50//���������꿪ʼ
#define X_X (WIN_HEIGHT/4)//����x����


void screen();//�������������ʼ��
void MouseMessage();//�����Ϣ


MOUSEMSG msg = { 0 };//�����Ϣ
HWND hwnd;//���ھ��

int speed = 10;//ʱ������

typedef struct//��������ϵ���ṹ��
{
	double y;
	double a;
	double w;
	double v;
	double w1;
}COEF;

COEF F1 = { 0, 100, 6 * PI / 1000 ,1,0 }, F2 = { 0,100,6 * PI / 1000,1,0 };//��ʼ��������ϵ��
//		y1=a1*cos(w1*(t-x/v1)+f)+w11		y2=a2*cos(w2*(t+x/v2)+f)+w22


int main()
{
	initgraph(WIN_LENGTH, WIN_HEIGHT, 1);//��ʼ��ͼ�δ���


	setbkcolor(WHITE);//���ñ���ɫΪ��ɫ
	double t, x, f;//����  tΪʱ�����		xΪ���������		fΪ���ĳ���λ
	

	screen();//�������������ʼ��

	f = 0;//���ó���λΪ0

	for (t = 0; 1; t +=speed)//ʱ����Զ����
	{
		screen();//�������������ʼ��
		setorigin(0, 0); //����(0, 0)Ϊ����ԭ��
		//��ʾ���ư���
		outtextxy(200, 50, L"��Ƶ");
		outtextxy(400, 50, L"����");
		outtextxy(600, 50, L"���");

		for (x = 0; x<1200 - XO; x += 0.5)//ѭ������    ����1200 - XO
		{
			setorigin(XO, X_X);//����(XO, X_X)Ϊ����ԭ��
			F1.y = F1.a*cos(F1.w*(t - x / F1.v) + f) + F1.w1;//���һ����������������
			putpixel(x, F1.y, GREEN);//����ɫ����

			setorigin(XO, X_X * 2);//����(XO, X_X * 2)Ϊ����ԭ��
			F2.y = F2.a*cos(F2.w*(t + x / F2.v) + f) + F2.w1;//��ڶ�����������������
			putpixel(x, F2.y, RED);//�ú�ɫ����
			setorigin(XO, X_X * 3);//����(XO, X_X * 3)Ϊ����ԭ��
			putpixel(x, F1.y + F2.y, BLUE);//����ɫ����
		}
		
		Sleep(100);//�Ӿ�����ʱ��
		MouseMessage();//�����Ϣ
	}

	return 0;
}


void screen()//�������������ʼ��
{
	cleardevice();//����
	setcolor(BLACK);//�����ߵ���ɫ
	setorigin(XO, 0);//���ã�XO��0��Ϊ����ԭ��
	//��������
	line(0, X_X, WIN_LENGTH, X_X);
	line(0, X_X * 2, WIN_LENGTH, X_X * 2);
	line(0, X_X * 3, WIN_LENGTH, X_X * 3);
	line(0, 0, 0, WIN_HEIGHT);
}


void MouseMessage()
{
	int result;
	msg = GetMouseMsg();//��ȡ�����Ϣ
	switch (msg.uMsg)//�����Ϣ
	{
		case WM_LBUTTONDOWN://������
			FlushMouseMsgBuffer();// ��������Ϣ������
			if (msg.x > 190 && msg.x < 240 && msg.y>40 && msg.y < 60)//��������������������
				{
				hwnd = GetHWnd();//��ʾ������ǰ
				result = MessageBox(hwnd, L"�Ƿ��Ƶ��", L"��ʾ", MB_ICONINFORMATION | MB_OKCANCEL);//��ʾ����
				if (result == IDOK)//���ѡ��ȷ��
				{
				MessageBox(hwnd, L"���ڿ���̨����", L"��ʾ", MB_OK);//��ʾ����
				printf("������Ƶ�ʣ�0.3��5����\nv1:");//��ʾ��Ϣ
				scanf("%lf", &F1.v);//����Ƶ������
				printf("\nv2:");
				scanf("%lf", &F2.v);
				getchar();//�Ե��س�
				}
				}
				else if (msg.x > 390 && msg.x < 440 && msg.y>40 && msg.y < 60)//��������������������
				{
					hwnd = GetHWnd();
					result = MessageBox(hwnd, L"�Ƿ���٣�", L"��ʾ", MB_ICONINFORMATION | MB_OKCANCEL);
					if (result == IDOK)
					{
						MessageBox(hwnd, L"���ڿ���̨����", L"��ʾ", MB_OK);
						printf("�������ٶȣ�1��500��:\n");
						scanf("%d", &speed);
						getchar();
					}
				}
				else if (msg.x > 590 && msg.x < 640 && msg.y>40 && msg.y < 60)
				{
					hwnd = GetHWnd();
					result = MessageBox(hwnd, L"�Ƿ�����", L"��ʾ", MB_ICONINFORMATION | MB_OKCANCEL);
					if (result == IDOK)
					{
						MessageBox(hwnd, L"���ڿ���̨����", L"��ʾ", MB_OK);
						printf("�����������1��50����\na1:");
						scanf("%lf", &F1.a);
						printf("\na2:");
						scanf("%lf", &F2.a);
						printf("���������¸�����0��50����\nw1:");
						scanf("%lf", &F1.w1);
						printf("\nw2:");
						scanf("%lf", &F2.w1);
						getchar();
					}
				}
	}
}