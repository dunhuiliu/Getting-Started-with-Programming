#include"controller.h"

int Setup()
{
	InitWind();
	clearWind();
	InitModel();
	registerTimerEvent(TimerListener);
	startTimer(0, 200);

	return 0;
}

void TimerListener(int id)
{
	if (id == 0)
	{
		clearWind();
		charMove();
		printChar();
		pulsRain();
	}
}
