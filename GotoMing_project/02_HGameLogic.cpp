#include "02_HGameLogic.h"
#include "01_HConsole.h"
#include<iostream>
#include<ctime>
#include<fstream>

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

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH])
{
	SetCursorVis(false, 1);

	std::fstream readMap("stage.txt");
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			readMap.getline(_arrMap[i], MAP_WIDTH);	
			if (readMap.fail())
				std::cout << "파일 에러";
		}
	}
}

void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH])
{
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (_arrMap[i][j] == 0) {
				std::cout << "a ";
			}
		}
	    std::cout << std::endl;
	}
}
