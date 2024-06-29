#pragma once
#include "Shy_Board.h"
#include "Shy_Character.h"

class BM
{
public:
	bool initTile = false;
	bool playerTurn = false;

	Board battleBoard;
	Enemy enemy;

	Board lastBoard;

	void bInit();
};