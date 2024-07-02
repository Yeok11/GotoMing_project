#pragma once
#include "Shy_Character.h"

class Pos
{
public:
	int x;
	int y;

	Pos() { x = 0; y = 0; }

	Pos(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

class BoardTile
{
public:
	int data; //카드의 내용
	Pos pos = Pos(0,0);
	Skill skillData;

	BoardTile(int _data)
	{
		data = _data;
	}
};

class Board 
{
public:
	int hSize = 0;
	int wSize = 0;

	vector<BoardTile> board[99];

	Board(int _size = 0);
	Board(int hSize, int _wSize);
	void SetBoard();
	void AddTileInBoard(int _pos);
	void CheckBoard(bool fall = false);
	void MergeTile(Pos _pos, Pos _addPos);
	bool DownTile(Pos _pos);

	void RemoveTile(Pos _pos)
	{
		board[_pos.x][4 - _pos.y].data = 0;
		board[_pos.x][4 - _pos.y].skillData.rank = 0;
	}

	void InputSkill(Pos _pos, Player & _player)
	{
		Skill skillData = board[_pos.x][4 - _pos.y].skillData;
		skillData.SetValue();
		_player.actionSkills.push_back(skillData);
		RemoveTile(_pos);
	}

private:
	
};