#include<iostream>

#include"02_HGameLogic.h"
#include"01_HConsole.h"

int main()
{
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE);
	int i = 0;
	char arrMap[MAP_HEIGHT][MAP_WIDTH];

	PLAYER tPlayer = {};

	while (true)
	{
		Update(arrMap, &tPlayer);
		Init(arrMap);
		Gotoxy(0, 0);
		Render(arrMap, &tPlayer, SHADOW);
		FrameSync(60);
	}
}