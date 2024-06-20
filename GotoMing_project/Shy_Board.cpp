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
	//너가 가지고 있는 카드의 수
	int num = 5;

	board[_pos][size - 1].data = rand() % num + 1;
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
				if (board[i][j - 1].data == 0 && board[i][j].data != 0)
				{
					isFallingTile = DownTile(Pos(i, j));
				}
			}
		}

		//타일 추가
		if (!isFallingTile)
		{
			for (int i = 0; i < size; i++)
			{
				if (board[i][size - 1].data == 0) 
					AddTileInBoard(i);
			}
		}
	}
	else
	{
		//타일 검사 이후 합체
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				BoardTile target = board[i][j];

				if (j + 1 != size
					&& target.data == board[i][j + 1].data
					&& target.rank == board[i][j + 1].rank)
				{
					MergeTile(Pos(i, j), Pos(0, 1));
				}
				else if (i + 1 != size 
					&& target.data == board[i + 1][j].data 
					&& target.rank == board[i + 1][j].rank)
				{
					MergeTile(Pos(i, j), Pos(1, 0));
				}
			}
		}
	}
}

void Board::MergeTile(Pos _pos, Pos _addPos)
{
	//타일 제거
	board[_pos.x + _addPos.x][_pos.y + _addPos.y].rank = 0;
	board[_pos.x + _addPos.x][_pos.y + _addPos.y].data = 0;

	board[_pos.x][_pos.y].rank += 1; //여기 더한 값을 넣준다.
}


bool Board::DownTile(Pos _pos)
{
	board[_pos.x][_pos.y - 1] = board[_pos.x][_pos.y];
	board[_pos.x][_pos.y].data = 0;
	board[_pos.x][_pos.y].rank = 0;

	return true;
}

bool Board::AllTileFilledNot()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if(board[i][j].data == 0)
				return true;
		}
	}
	return false;
}

bool Board::FindEmptyTile(int _pos)
{
	for (int i = 0; i < size; i++)
	{
		if (board[_pos][i].data == 0) return true;
	}
	return false;
}
