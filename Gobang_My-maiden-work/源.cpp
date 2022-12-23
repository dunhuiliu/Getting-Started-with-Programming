/******************************************
文件名称：main.cpp
文件描述：实现图形界面五子棋游戏
编译环境：VS2008-VS2017     VC6.0
最后修改：
<2018年1月13日>  <创建工程>  
******************************************/

#include"gomoku.h"
#include<stdio.h>
//========================主函数===========================
int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	PlaySound(L"res/flower dance.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC| SND_NODEFAULT);
	Initbefore();
	do {
		cnt = 0;
		chongwan = 0;
		flag = 0;
		GameInit();
		while (flag == 0)
		{
			MouseClick();
			Judge();
			if (chongwan == 1)
				break;
		}
		for (i = 0; i < Num + 1; i++) {
			for (j = 0; j < Num + 1; j++)
			{
				Map[i][j] = 0;
			}
		}
		if (flag)
		{
			settextcolor(hong);
			LOGFONT q;
			gettextstyle(&q);						 // 获取当前字体设置
			q.lfHeight = 64;						 // 设置字体高度为 24
			_tcscpy_s(q.lfFaceName, _T("黑体"));	// 设置字体为“草书”(高版本 VC 推荐使用 _tcscpy_s 函数)
			q.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
			settextstyle(&q);						// 设置字体样式
			setbkmode(0);
			TCHAR baoliu[] = _T("请按任意键继续...");
			outtextxy(170, 400, baoliu);
			getchar();
			FlushMouseMsgBuffer();//清空鼠标消息缓冲区
		}
		cleardevice();
	} while (1);
	return 0;
}

VOID Initbefore()
{
	srand((unsigned int)time(NULL));
	//loadimage(NULL, _T("IMAGE"), _T("bkimage.ico"));
	loadimage(&Background1, TEXT("res/Background1.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background2, TEXT("res/Background2.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background3, TEXT("res/Background3.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background4, TEXT("res/Background4.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background5, TEXT("res/Background5.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background6, TEXT("res/Background6.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background7, TEXT("res/Background7.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background8, TEXT("res/Background8.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background9, TEXT("res/Background9.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
	loadimage(&Background10, TEXT("res/Backgroun10.jpg"), WINDOW_WIDTH, WINDOW_HEIGHT);
}
//游戏初始化函数
VOID GameInit()
{
	putimage(0, 0, &Background6);
	BeginBatchDraw();
	for (i = 0; i < 19; i++)
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
		if (i < 7)
			j = i + 1;
		else if (i >= 7 && i<14)
			j = i - 6;
		else j = i - 13;
		switch (j)
		{
		case 1:
			setlinecolor(hong);
			break;
		case 2:
			setlinecolor(cheng);
			break;
		case 3:
			setlinecolor(huang);
			break;
		case 4:
			setlinecolor(lv);
			break;
		case 5:
			setlinecolor(lan);
			break;
		case 6:
			setlinecolor(dian);
			break;
		case 7:
			setlinecolor(zi);
			break;
		}
		line(Leftjie + GeLength*i, UpDownjie, Leftjie + GeLength*i, WINDOW_HEIGHT - UpDownjie);
		line(Leftjie, UpDownjie + GeLength*i, WINDOW_WIDTH - Rightjie, UpDownjie + GeLength*i);
	}
	EndBatchDraw();

	//输出右侧说明文字
	settextcolor(dian);
	LOGFONT f;
	gettextstyle(&f);						 // 获取当前字体设置
	f.lfHeight = 24;						 // 设置字体高度为 24
	_tcscpy_s(f.lfFaceName, _T("草书"));	// 设置字体为“草书”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(0);

	outtextxy(850, 60, hei);
	outtextxy(850, 90, bai);
	settextcolor(hong);
	outtextxy(850, 150, luozi);
	outtextxy(850,630, qiege);
	outtextxy(850, 670, qiebkp);

	//重玩游戏
	settextcolor(hong);
	outtextxy(850, 390, again);

	//悔棋
	outtextxy(850, 470, huiqi);

	//搞笑
	outtextxy(850, 550, gaoxiao);

	//步数显示
	settextcolor(lv);
	outtextxy(850, 210, heibu);
	outtextxy(850, 240, baibu);
}

VOID MouseClick()
{
	msg = GetMouseMsg();
	switch (msg.uMsg)
	{
	case WM_LBUTTONUP:
		if (msg.x > 70 && msg.x < 810 && msg.y > 30 && msg.y < 770)
		{
			if (msg.x>100 && msg.y>60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 0)
				{
					X = (msg.x - Leftjie - GeLength / 2) / GeLength + 1;
					Y = (msg.y - UpDownjie - GeLength / 2) / GeLength + 1;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = ((msg.x - Leftjie - GeLength / 2) / GeLength + 1)*GeLength + Leftjie;
					drawY = ((msg.y - UpDownjie - GeLength / 2) / GeLength + 1)*GeLength + UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"这里有棋子哦,请选择别处", L"Are you逗比？", MB_OK);
				}
			}
			else if (msg.x<100 && msg.y > 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 0)
				{
					X = 0;
					Y = (msg.y - UpDownjie - GeLength / 2) / GeLength + 1;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = Leftjie;
					drawY = ((msg.y - UpDownjie - GeLength / 2) / GeLength + 1)*GeLength + UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength + 1] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"这里有棋子哦,请选择别处", L"Are you逗比？", MB_OK);
				}
			}
			else if (msg.x>100 && msg.y < 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 0)
				{
					X = (msg.x - Leftjie - GeLength / 2) / GeLength + 1;
					Y = 0;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = ((msg.x - Leftjie - GeLength / 2) / GeLength + 1)*GeLength + Leftjie;
					drawY = UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength + 1][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"这里有棋子哦,请选择别处", L"Are you逗比？", MB_OK);
				}
			}
			else if (msg.x<100 && msg.y < 60)
			{
				if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 0)
				{
					X = 0;
					Y = 0;
					Record.rx[cnt] = X;
					Record.ry[cnt] = Y;
					cnt++;
					drawX = Leftjie;
					drawY = UpDownjie;
					if (cnt % 2) {
						Map[X][Y] = 1;
					}
					else Map[X][Y] = 2;
					if (cnt > 0)
					PlayGame();
				}
				else if (Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 1 || Map[(msg.x - Leftjie - GeLength / 2) / GeLength][(msg.y - UpDownjie - GeLength / 2) / GeLength] == 2)
				{
					hWnd = GetHWnd();
					MessageBox(hWnd, L"这里有棋子哦，请选择别处", L"Are you逗比？", MB_OK);
				}
			}
		}
		else if (msg.x >= 845 && msg.y >= 370 && msg.y <= 410)
			chongwan = 1;
		else if (msg.x >= 845 && msg.y >= 450 && msg.y <= 490)
		{
			if (cnt>0)
			{
				Back();
			}
		else {
				hWnd = GetHWnd();
				MessageBox(hWnd, L"啊？什么？你已经悔到头了呢！", L"你是猴子吗？", MB_OK);
			}
		}
		else if (msg.x >= 845 && msg.y >= 530 && msg.y <= 570)
		{
			hWnd = GetHWnd();
			MessageBox(hWnd, L"奴婢紧张制作中，请陛下耐心等待！", L"其实我不会写这个......", MB_OK);
		}
		else if (msg.x >= 845 && msg.y >= 610 && msg.y <= 650)
		{
			NO_Songs=rand()%SUM_Songs+1;
			ChangeSong();
		}
		else if (msg.x >= 845 && msg.y >= 650 && msg.y <= 690)
		{
			ChangePictures();
		}
		break;
	}
}

VOID PlayGame()
{
	BeginBatchDraw();
	if (cnt % 2)
		setfillcolor(heise);
	else setfillcolor(baise);
	//if (Map[X][Y] == 0)
	solidcircle(drawX, drawY, 19);

	//计步
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//轮到玩家显示
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);
	EndBatchDraw();
}

VOID Judge()
{
	//黑棋赢
	if (
		(Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1 && Map[X + 3][Y] == 1 && Map[X + 4][Y] == 1) ||
		(Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1 && Map[X + 3][Y] == 1) ||
		(Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1 && Map[X + 2][Y] == 1) ||
		(Map[X - 3][Y] == 1 && Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1 && Map[X + 1][Y] == 1) ||
		(Map[X - 4][Y] == 1 && Map[X - 3][Y] == 1 && Map[X - 2][Y] == 1 && Map[X - 1][Y] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1 && Map[X][Y + 3] == 1 && Map[X][Y + 4] == 1) ||
		(Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1 && Map[X][Y + 3] == 1) ||
		(Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1 && Map[X][Y + 2] == 1) ||
		(Map[X][Y - 3] == 1 && Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1 && Map[X][Y + 1] == 1) ||
		(Map[X][Y - 4] == 1 && Map[X][Y - 3] == 1 && Map[X][Y - 2] == 1 && Map[X][Y - 1] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1 && Map[X + 3][Y - 3] == 1 && Map[X + 4][Y - 4] == 1) ||
		(Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1 && Map[X + 3][Y - 3] == 1) ||
		(Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1 && Map[X + 2][Y - 2] == 1) ||
		(Map[X - 3][Y + 3] == 1 && Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y - 1] == 1) ||
		(Map[X - 4][Y + 4] == 1 && Map[X - 3][Y + 3] == 1 && Map[X - 2][Y + 2] == 1 && Map[X - 1][Y + 1] == 1 && Map[X][Y] == 1) ||
		(Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1 && Map[X + 3][Y + 3] == 1 && Map[X + 4][Y + 4] == 1) ||
		(Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1 && Map[X + 3][Y + 3] == 1) ||
		(Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1 && Map[X + 2][Y + 2] == 1) ||
		(Map[X - 3][Y - 3] == 1 && Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1 && Map[X + 1][Y + 1] == 1) ||
		(Map[X - 4][Y - 4] == 1 && Map[X - 3][Y - 3] == 1 && Map[X - 2][Y - 2] == 1 && Map[X - 1][Y - 1] == 1 && Map[X][Y] == 1)
		)
		flag = 1;

	//白棋赢
	if (
		(Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2 && Map[X + 3][Y] == 2 && Map[X + 4][Y] == 2) ||
		(Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2 && Map[X + 3][Y] == 2) ||
		(Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2 && Map[X + 2][Y] == 2) ||
		(Map[X - 3][Y] == 2 && Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2 && Map[X + 1][Y] == 2) ||
		(Map[X - 4][Y] == 2 && Map[X - 3][Y] == 2 && Map[X - 2][Y] == 2 && Map[X - 1][Y] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2 && Map[X][Y + 3] == 2 && Map[X][Y + 4] == 2) ||
		(Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2 && Map[X][Y + 3] == 2) ||
		(Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2 && Map[X][Y + 2] == 2) ||
		(Map[X][Y - 3] == 2 && Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2 && Map[X][Y + 1] == 2) ||
		(Map[X][Y - 4] == 2 && Map[X][Y - 3] == 2 && Map[X][Y - 2] == 2 && Map[X][Y - 1] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2 && Map[X + 3][Y - 3] == 2 && Map[X + 4][Y - 4] == 2) ||
		(Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2 && Map[X + 3][Y - 3] == 2) ||
		(Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2 && Map[X + 2][Y - 2] == 2) ||
		(Map[X - 3][Y + 3] == 2 && Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y - 1] == 2) ||
		(Map[X - 4][Y + 4] == 2 && Map[X - 3][Y + 3] == 2 && Map[X - 2][Y + 2] == 2 && Map[X - 1][Y + 1] == 2 && Map[X][Y] == 2) ||
		(Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2 && Map[X + 3][Y + 3] == 2 && Map[X + 4][Y + 4] == 2) ||
		(Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2 && Map[X + 3][Y + 3] == 2) ||
		(Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2 && Map[X + 2][Y + 2] == 2) ||
		(Map[X - 3][Y - 3] == 2 && Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2 && Map[X + 1][Y + 1] == 2) ||
		(Map[X - 4][Y - 4] == 2 && Map[X - 3][Y - 3] == 2 && Map[X - 2][Y - 2] == 2 && Map[X - 1][Y - 1] == 2 && Map[X][Y] == 2)
		)
		flag = 2;
	if (flag == 1) {
		hWnd = GetHWnd();
		MessageBox(hWnd, L"黑棋胜", L"恭喜！", MB_OK);
	}
	else if (flag == 2)
	{
		hWnd = GetHWnd();
		MessageBox(hWnd, L"粉棋胜", L"恭喜！", MB_OK);
	}
}

//悔棋
VOID Back()
{
	//cleardevice();
	GameInit();
	if(cnt>0)
	cnt--;
	X=Record.rx[cnt];
	Y=Record.ry[cnt];
	Map[X][Y] = 0;

	for (i = 0; i < Num + 1; i++)
	{
		for (j = 0; j < Num + 1; j++)
		{
			if (Map[i][j]==1)
				setfillcolor(heise);
			else if(Map[i][j]==2)
				setfillcolor(baise);
			else continue;
			drawX = Leftjie + i*GeLength;
			drawY = UpDownjie + j*GeLength;
			solidcircle(drawX, drawY, 19);
		}
	}
	//计步
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	if (cnt == 0)
	{
		heibuS[1] = 0;
	}else 
	heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//轮到玩家显示
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);
}

VOID ChangeSong()
{
	PlaySound(NULL, NULL, SND_FILENAME);
	switch (NO_Songs)
	{
	case 1:
		PlaySound(L"res/han.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 2:
		PlaySound(L"res/flower dance.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 3:
		PlaySound(L"res/纯音乐 - 一首好听的古筝曲.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 4:
		PlaySound(L"res/乐正绫  洛天依 - 扫雷2.0.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	case 5:
		PlaySound(L"res/凉凉.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
		break;
	}
}

VOID ChangePictures()
{
	NO_Pictures = rand() % SUM_Pictures + 1;
	switch (NO_Pictures)
	{
	case 1:
		putimage(0, 0, &Background1);
		break;
	case 2:
		putimage(0, 0, &Background2);
		break;
	case 3:
		putimage(0, 0, &Background3);
		break;
	case 4:
		putimage(0, 0, &Background4);
		break;
	case 5:
		putimage(0, 0, &Background5);
		break;
	case 6:
		putimage(0, 0, &Background6);
		break;
	case 7:
		putimage(0, 0, &Background7);
		break;
	case 8:
		putimage(0, 0, &Background8);
		break;
	case 9:
		putimage(0, 0, &Background9);
		break;
	case 10:
		putimage(0, 0, &Background10);
		break;
	}

	BeginBatchDraw();
	for (i = 0; i < 19; i++)
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
		if (i < 7)
			j = i + 1;
		else if (i >= 7 && i<14)
			j = i - 6;
		else j = i - 13;
		switch (j)
		{
		case 1:
			setlinecolor(hong);
			break;
		case 2:
			setlinecolor(cheng);
			break;
		case 3:
			setlinecolor(huang);
			break;
		case 4:
			setlinecolor(lv);
			break;
		case 5:
			setlinecolor(lan);
			break;
		case 6:
			setlinecolor(dian);
			break;
		case 7:
			setlinecolor(zi);
			break;
		}
		line(Leftjie + GeLength*i, UpDownjie, Leftjie + GeLength*i, WINDOW_HEIGHT - UpDownjie);
		line(Leftjie, UpDownjie + GeLength*i, WINDOW_WIDTH - Rightjie, UpDownjie + GeLength*i);

	}
	EndBatchDraw();

	//输出右侧说明文字
	settextcolor(dian);
	LOGFONT f;
	gettextstyle(&f);						 // 获取当前字体设置
	f.lfHeight = 24;						 // 设置字体高度为 24
	_tcscpy_s(f.lfFaceName, _T("草书"));	// 设置字体为“草书”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	setbkmode(0);

	outtextxy(850, 60, hei);
	outtextxy(850, 90, bai);
	settextcolor(hong);
	outtextxy(850, 150, luozi);
	outtextxy(850, 630, qiege);
	outtextxy(850, 670, qiebkp);

	//重玩游戏
	settextcolor(hong);
	outtextxy(850, 390, again);

	//悔棋
	outtextxy(850, 470, huiqi);

	//搞笑
	outtextxy(850, 550, gaoxiao);

	//步数显示
	settextcolor(lv);
	outtextxy(850, 210, heibu);
	outtextxy(850, 240, baibu);
	//计步
	setcolor(RGB(255, 255, 255));
	setbkmode(OPAQUE);
	if (cnt == 0)
	{
		heibuS[1] = 0;
	}
	else
		heibuS[1] = (int)(cnt - 0.001) / 2 + 1;
	_stprintf_s(heibuS, _T("%d"), heibuS[1]);
	outtextxy(948, 210, heibuS);

	baibuS[1] = cnt / 2;
	_stprintf_s(baibuS, _T("%d"), baibuS[1]);
	outtextxy(948, 240, baibuS);

	//轮到玩家显示
	if (cnt % 2) {
		wanjia[1] = 2;
	}
	else wanjia[1] = 1;
	_stprintf_s(wanjia, _T("%d"), wanjia[1]);
	outtextxy(905, 150, wanjia);


	for (i = 0; i < Num + 1; i++)
	{
		for (j = 0; j < Num + 1; j++)
		{
			if (Map[i][j] == 1)
				setfillcolor(heise);
			else if (Map[i][j] == 2)
				setfillcolor(baise);
			else continue;
			drawX = Leftjie + i*GeLength;
			drawY = UpDownjie + j*GeLength;
			solidcircle(drawX, drawY, 19);
		}
	}
}
