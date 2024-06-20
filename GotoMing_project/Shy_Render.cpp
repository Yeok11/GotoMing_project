#include "Shy_Render.h"

void ChangeColorByRank(int _rank)
{
	switch (_rank)
	{
	case 1:
		SetColor((int)COLOR::BLACK, (int)COLOR::MINT);
		break;

	case 2:
		SetColor((int)COLOR::BLACK, (int)COLOR::YELLOW);
		break;

	case 3:
		SetColor((int)COLOR::BLACK, (int)COLOR::RED);
		break;

	case 4:
		SetColor((int)COLOR::BLACK, (int)COLOR::LIGHT_YELLOW);
		break;

	default:
		SetColor((int)COLOR::BLACK, (int)COLOR::GRAY);
	}
}

void TileRender(Pos _pos)
{
	int hMax = 11, wMax = 17;
	for (int h = 0; h < hMax; h++)
	{
		Gotoxy((wMax + 2) * _pos.x + 4, (hMax + 1) * _pos.y + h + 1);
		for (int w = 0; w < wMax; w++)
		{
			cout << " ";
		}
	}
}

void BoardRender(Board & _board)
{
	Gotoxy(0, 0);
	
	for (int i = _board.size - 1; i >= 0; --i)
	{
		for (int j = 0; j < _board.size; ++j)
		{
			ChangeColorByRank(_board.board[j][i].rank);
			TileRender(Pos(j, _board.size -1 - i));
			cout << _board.board[j][i].data;
		}
		cout << endl;
	}
}