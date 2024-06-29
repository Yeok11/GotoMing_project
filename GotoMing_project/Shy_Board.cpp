#include "Shy_Core.h"
#include "Shy_Board.h"

Board::Board(int _size) { hSize = _size; wSize = _size; }


Board::Board(int _hSize, int _wSize)
{
	hSize = _hSize;
	wSize = _wSize;
}

#pragma region 보드 세팅

//기본 세팅
void Board::SetBoard()
{
	//init 과정
	for (int i = 0; i < wSize; i++)
		for (int j = 0; j < hSize; ++j)
			if (board[i].size() != hSize) {
				board[i].push_back(BoardTile(0));
			}
}

//타일 추가
void Board::AddTileInBoard(int _pos)
{
	//너가 가지고 있는 카드의 수
	int num = 5;
	int _data = rand() % GET_SINGLE(GM)->player.skills.size() + 1;

	board[_pos][hSize - 1].data = _data;
	board[_pos][hSize - 1].skillData = GET_SINGLE(GM)->player.skills[_data - 1];
	board[_pos][hSize - 1].skillData.rank = 1;
	board[_pos][hSize - 1].pos = Pos(_pos, hSize - 1);
}
#pragma endregion

//타일 확인
void Board::CheckBoard(bool fall)
{
	bool isFallingTile = false;

	//타일 검사
	for (int i = 0; i < wSize; i++)
	{
		for (int j = 1; j < hSize; j++)
		{
			//바닥으로 떨구기 (중력 구현)
			if (board[i][j - 1].data == 0 && board[i][j].data != 0)
				isFallingTile = DownTile(Pos(i, j));
		}
	}

	if (isFallingTile) return;

	//타일 추가
	if (!isFallingTile && fall)
	{
		for (int i = 0; i < wSize; i++)
		{
			if (board[i][hSize - 1].data == 0)
			{
				isFallingTile = true;
				AddTileInBoard(i);
			}
		}
	}

	if (isFallingTile) return;

	bool isMergeTile = false;

	//타일 검사 이후 합체
	for (int i = 0; i < wSize; i++)
	{
		for (int j = 0; j < hSize; j++)
		{
			BoardTile target = board[i][j];

			if (j + 1 != hSize && target.skillData.name == board[i][j + 1].skillData.name
				&& target.skillData.rank == board[i][j + 1].skillData.rank)
			{
				MergeTile(Pos(i, j), Pos(0, 1));
				isMergeTile = true;
			}
			else if (i + 1 != wSize && target.skillData.name == board[i + 1][j].skillData.name
				&& target.skillData.rank == board[i + 1][j].skillData.rank)
			{
				MergeTile(Pos(i, j), Pos(1, 0));
				isMergeTile = true;
			}
		}
	}

	if (!isMergeTile)
	{
		if (GET_SINGLE(GM)->player.actionSkills.size() == GET_SINGLE(GM)->player.skillLimit)
		{
			GET_SINGLE(GM)->player.ChangeState(dBATTLE);
			GET_SINGLE(GM)->lastBoard = NULL;
			return;
		}

		GET_SINGLE(GM)->lastBoard = GET_SINGLE(GM)->battleBoard;
		GET_SINGLE(GM)->player.ChangeState(dSELECT);
	}

}

//타일 합치기
void Board::MergeTile(Pos _pos, Pos _addPos)
{
	board[_pos.x][_pos.y].skillData.rank += 1; //여기 더한 값을 넣준다.

	//타일 제거
	board[_pos.x + _addPos.x][_pos.y + _addPos.y].skillData.rank = 0;
	board[_pos.x + _addPos.x][_pos.y + _addPos.y].skillData.name = "";
	board[_pos.x + _addPos.x][_pos.y + _addPos.y].data = 0;
}

//타일 떨구기
bool Board::DownTile(Pos _pos)
{
	board[_pos.x][_pos.y - 1] = board[_pos.x][_pos.y];
	board[_pos.x][_pos.y].data = 0;
	board[_pos.x][_pos.y].skillData.rank = 0;
	board[_pos.x][_pos.y].skillData.name = "";

	return true;
}


