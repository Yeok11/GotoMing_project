#pragma once

class Board 
{
public:
	int size;
	int board[][];

	Board(int _size);

private:
	
};

class BoardTile 
{
public:
	int rank;
};


void SetBoard(Board& _board);