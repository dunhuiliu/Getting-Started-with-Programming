#pragma once

#define SHELLS 5555//����ڵ�����1
#define NUM_PLANE 10//���ɻ���
#define MIN_PLANE 3//���ٷɻ���

extern int NowShells;//��ǰ�ڵ�����
extern int GunAngle;//�ڵĽǶ�
extern int q1, w1, e1, r1;//���ڵ���1������
extern int q2, w2, e2, r2;//���ڵ���2������
extern int q3, w3, e3, r3;//���ڵ���3������
extern int q4, w4, e4, r4;//���ڵ���4������

extern int _X_;//�ɻ�ƫ����
extern int nPlane;//�ɻ�����
extern int x[], y[];
extern int x[], y[];

extern struct shells {
	int x1;
	int y1;
	int x2;
	int y2;
}Shell[];//ÿһ���ڵ�����

int GunCoord();//�����ڵ�����
int Angle();//�Ƕȼ���
int FairShell();//�ڵ��ķ����ʼ��
int ShellProc(int i);//�ڵ��������
int AirFly(int x, int y);//�ɻ����й���
int PlaneLocation(int i);//�ɻ������¼����ʼ��