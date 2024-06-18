#pragma once
#include "Shy_Define.h"

class Pos
{
public:
	int x;
	int y;

	Pos(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

class BoardTile
{
public:
	int rank;
	Pos pos = Pos(0,0);

	BoardTile(int _rank)
	{
		rank = _rank;
	}
};

class Board 
{
public:
	int size = 0;
	vector<BoardTile> board[99];

	Board(int _size = 0);
	void SetBoard();
	void AddTileInBoard(int _pos);
	bool AllTileFilledNot();
	bool FindEmptyTile(int _pos);
	void CheckBoard();

private:
	
};