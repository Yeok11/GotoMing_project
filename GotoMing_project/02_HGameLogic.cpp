#include "02_HGameLogic.h"
#include<iostream>
#include<ctime>

void FrameSync(unsigned int _Framerate)
{
	clock_t oldtime, curtime;
	oldtime = clock();
	while (true)
	{
		curtime = clock();
		if (curtime - oldtime > 1000 / _Framerate)
		{
			oldtime = curtime;
			break;
		}
	}
}

void Render(int Map_Height, int Map_Width)
{
	for (int i = 0; i < Map_Height; i++) {
		for (int j = 0; j < Map_Width; j++) {
			std::cout << "бр";
		}
		std::cout << std::endl;
	}
}
