#include<iostream>

#include"02_HGameLogic.h"
#include"01_HConsole.h"

int main()
{
	int i = 0;
	char arrMap[MAP_HEIGHT][MAP_WIDTH];
	char InfoarrMap[MAP_HEIGHT][IMAP_WIDTH];
	PLAYER tPlayer = {};
	SetGameState stateManager = {};
	SetINFOState stateInfoManager = {};

	Init(arrMap, InfoarrMap, &tPlayer);

	while (true)
	{
		Update(arrMap, &tPlayer, stateManager, stateInfoManager);
		Gotoxy(Map_Emtpy, 5);
		GameRender(arrMap, &tPlayer, SHADOW, stateManager);
		Gotoxy(Map_Emtpy + 101, 5);
		InfoRender(InfoarrMap, &tPlayer, SHADOW, stateManager);
		FrameSync(60);
		//d
	}
}