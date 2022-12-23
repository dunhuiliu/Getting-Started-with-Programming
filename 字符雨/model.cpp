#include"model.h"

vector<string> str;
vector<vector<int>> address(COL_NUM);

string createString()
{
	char a;
	string s;
	for (int i = 0; i < CharNum; i++)
	{
		do
		{
			a = rand() % 91;			//Z
		} while (a < 64);			//A
		s += a;
	}
	return s;
}

void CreatePicture()
{
	for (int j = 0; j < COL_NUM; j++)
	{
		str.push_back(createString());
	}
}

vector<int> Create_One_SlidingWindow()
{
	vector<int> v(2);			//v0存储字符头，v1可显示字符长度

	v.at(0) = rand() % CharNum - CharNum;

	do
	{
		v.at(1) = rand() % MaxCharNum + 1;
	} while (v.at(1) < MinCharNum);

	return  v;
}

void Create_All_SlidingWindow()
{
	for (int k = 0; k < COL_NUM; k++)
	{
		address[k] = Create_One_SlidingWindow();
		address[k][0] += CharNum;
	}
}

void InitModel()
{
	CreatePicture();
	Create_All_SlidingWindow();
}

void pulsRain()
{
	for (int a = 0; a < COL_NUM; a++)
	{
		int s = (address.at(a).at(0) - address.at(a).at(1)) *TEXTSIZE;
		//https://www.cnblogs.com/james6176/p/4283494.html
		if (s >= WIN_HEIGHT)
		{
			str.at(a) = createString();
			address.at(a) = Create_One_SlidingWindow();
		}
	}
}
