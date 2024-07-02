#include "Shy_Define.h"
#include "Shy_BM.h"

void BM::bInit(Player & p)
{
	battleBoard = Board(5, 4);
	battleBoard.SetBoard();
	enemy = Enemy(rand() % 40 + 10, dWAIT);
	
	enemy.SetData();

	p.actionSkills = vector<Skill>();


	initTile = true;
	playerTurn = true;
}