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
	int rank; //카드의 등급
	int data; //카드의 내용
	Pos pos = Pos(0,0);

	BoardTile(int _data)
	{
		data = _data;
		rank = 0;
	}
};

class Board 
{
public:
	int size = 0;
	int hSize = 0;
	int wSize = 0;
	int limitRank = 0;

	vector<BoardTile> board[99];

	Board(int _size = 0);
	void SetBoard();
	void AddTileInBoard(int _pos);
	bool AllTileFilledNot();
	bool FindEmptyTile(int _pos);
	void CheckBoard();
	void MergeTile(Pos _pos, Pos _addPos);
	bool DownTile(Pos _pos);

private:
	
};