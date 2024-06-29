#include "Shy_Define.h"
#include "Shy_BM.h"

void BM::bInit()
{
	battleBoard = Board(5, 4);
	battleBoard.SetBoard();
	enemy = Enemy(10, dWAIT);
	
	enemy.SetData();
	initTile = true;
	playerTurn = true;
}