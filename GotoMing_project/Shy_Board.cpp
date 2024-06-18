#include "Shy_Board.h"

Board::Board(int _size){size = _size;}

void Board::SetBoard()
{
	//init 과정
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; ++j)
			board[i].push_back(BoardTile(0));
}

void Board::AddTileInBoard(int _pos)
{
	board[_pos][size - 1].rank = 1;
	board[_pos][size - 1].pos = Pos(_pos, size - 1);
}


void Board::CheckBoard()
{
	if (AllTileFilledNot()) //전체 검사
	{
		bool isFallingTile = false;

		//타일 검사
		for (int i = 0; i < size; i++)
		{
			for (int j = 1; j < size; j++)
			{
				//바닥으로 떨구기 (중력 구현)
				if (board[i][j - 1].rank == 0 && board[i][j].rank != 0)
				{
					isFallingTile = downTile();
				}
			}
		}

		//타일 추가
		if (!isFallingTile)
		{
			for (int i = 0; i < size; i++)
			{
				if (board[i][size - 1].rank == 0) 
				{
					AddTileInBoard(i);
				}
			}
		}
	}
	else
	{
		//타일 검사 이후 합체
		
	}
}

bool downTile()
{
	board[i][j - 1].rank = board[i][j].rank;
	board[i][j].rank = 0;

	return true;
}

bool Board::AllTileFilledNot()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if(board[i][j].rank == 0)
				return true;
		}
	}
	return false;
}

bool Board::FindEmptyTile(int _pos)
{
	for (int i = 0; i < size; i++)
	{
		if (board[_pos][i].rank == 0) return true;
	}
	return false;
}
