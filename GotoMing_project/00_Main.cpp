#include<iostream>

#include"02_HGameLogic.h"
#include"01_HConsole.h"

int main()
{
	int i = 0;
	char arrMap[MAP_HEIGHT][MAP_WIDTH];
	PLAYER tPlayer = {};

	Init(arrMap, &tPlayer);

	while (true)
	{
		Update(arrMap, &tPlayer);
		Gotoxy(Map_Emtpy, 5);
		Render(arrMap, &tPlayer, SHADOW);
		FrameSync(60);
		//d
	}
}