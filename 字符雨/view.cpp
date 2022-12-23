#include"view.h"
#include"model.h"

void InitWind()
{
	initWindow("字符雨", 0, 0, WIN_WIDTH, WIN_HEIGHT);
	//initConsole();
	PlaySound("flower dance.wav", NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);
	srand((unsigned int)time(NULL));
	beginPaint();
	setBrushColor(RGB(0, 0, 0));
	setTextBkColor(RGB(0, 0, 0));
	setTextFont("Kristen ITC");
	setTextSize(TEXTSIZE);
	endPaint();
}

void clearWind()
{
	beginPaint();
	rectangle(0, 0, WIN_WIDTH, WIN_HEIGHT);
	endPaint();
}

void printChar()
{
	string auxiliary;
	int add;
	beginPaint();
	for (int i = 0; i < COL_NUM; i++)
	{
		add = address.at(i).at(0) - address.at(i).at(1);
		for (int l = 0; l < address.at(i).at(1); l++, add++)
		{
			if (add < 0 || add >= CharNum)
				continue;
			auxiliary = str[i].substr(add, 1);
			if (l == address.at(i).at(1) - 1)
			{
				setTextColor(RGB(255, 255, 255));
			}
			else
			{
				setTextColor(RGB(0, (l + 1) * (255 / address.at(i).at(1)), 0));
			}
			paintText(i*TEXTSIZE, add * TEXTSIZE, auxiliary.c_str());
		}
	}
	endPaint();
}

void charMove()
{
	for (int l = 0; l < COL_NUM; l++)
	{
		address.at(l).at(0)++;
	}
}
