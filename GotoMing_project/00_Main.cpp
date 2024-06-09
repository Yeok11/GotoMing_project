#include<iostream>

#include"02_HGameLogic.h"
#include"01_HConsole.h"

int main()
{
	int i = 0;
	char arrMap[MAP_HEIGHT][MAP_WIDTH];

	while (true)
	{
		Init(arrMap);
		Gotoxy(0, 0);
		Render(arrMap);
		FrameSync(60);
	}
}