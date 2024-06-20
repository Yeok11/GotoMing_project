#include "Shy_Define.h"
#include "Shy_Core.h"
#include "Shy_Render.h"
#include <ctime>

GM* GM::instance = nullptr;

bool GM::Init()
{
	srand((unsigned int)time(NULL));
	SetCursorVis(false, 1);
	SetScreen();
	return false;
}

void GM::Run()
{
	battleBoard.SetBoard();

	Render(battleBoard);

	Sleep(500);
	//battleBoard.AddTileInBoard(3);

	while (true)
	{
		Update();
		Render(battleBoard);

		Sleep(100);
	}
}

void GM::Update()
{
	battleBoard.CheckBoard();
	
}

void GM::Render(Board& _gameBoard)
{
	BoardRender(_gameBoard);
}
