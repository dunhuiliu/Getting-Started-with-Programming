#include"Model.h"
#include"Ctrl.h"

#include"acllib.h"
#include"View.h"

#include<stdio.h>

int start=0;//��Ϸ��ʼ��־
int GunAngle = 90;//��Ͳ�Ƕ�
int shellflag=0;//�����ڵ��ı�־
void kBoardListener(int key, int event)
{
	if (event == 0)
	{
		start = 1;
		switch (key)
		{
		case 37:
			if (GunAngle > 0)
				GunAngle -= 15;
			break;
		case 39:
			if (GunAngle < 180)
				GunAngle += 15;
			break;
		case 32:
		shellflag=1;//�����ڵ��ı�־
		printf("%d\n", key);
			break;
		default:
			break;
		}

	}
}