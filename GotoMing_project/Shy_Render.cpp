#include "Shy_Render.h"

void BoardRender(Board & _board)
{
	system("cls");
	for (int i = _board.size - 1; i >= 0; --i)
	{
		for (int j = 0; j < _board.size; ++j)
		{
			cout << _board.board[j][i].rank;
		}
		cout << endl;
	}
}