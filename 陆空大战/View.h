#pragma once
#define BATTERY_HEIGHT 40//��̨�߶�
#define BATTERY_WIDTH 100//��̨���
#define GunLength 80//�ڵĳ���
#define GunWidth 30//�ڵĿ��


int GameInit();
int PaintBattery();
int PaintGun();
int PaintShells(int XONE, int YONE, int XTWO, int YTWO);
int AirPlane(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5);
