#include "Shy_Render.h"
#include "Shy_Define.h"
#include "shy_Console.h"


void ChangeColorByRank(int _rank)
{
	switch (_rank)
	{
	case 0:
		SetColor((int)COLOR::BLACK, (int)COLOR::GRAY);
		break;

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
		SetColor((int)COLOR::BLACK, (int)COLOR::LIGHT_RED);
	}
}

void TileRender(Pos _pos, bool detailControl = false, string _dataName = "", int _dataRank = 0)
{
	int hMax = 11, wMax = 17;
	int dataPosX, dataPosY;

	for (int h = 0; h < hMax; h++)
	{
		if (detailControl)
		{
			dataPosX = (wMax + 3) * _pos.x + 4;
			dataPosY = hMax * _pos.y + h;
		}
		else
		{
			dataPosX = (wMax + 2) * _pos.x + 4;
			dataPosY = (hMax + 1) * _pos.y + h + 1;
		}

		Gotoxy(dataPosX, dataPosY);

		for (int w = 0; w < wMax; w++)
		{
			cout << " ";
		}
	}

	Gotoxy(dataPosX + wMax / 2 - _dataName.size() / 2, dataPosY - hMax / 2);
	cout << _dataName;
}

void TileSelectRender(Pos pos, bool _delete)
{
	for (int h = 0; h < 13; h++)
	{
		Gotoxy(19 * pos.x + 3, 12 * pos.y + h);
		for (int i = 0; i < (Or(h,0,12) ? 18 : 1); i++)
		{
			SetColor((int)COLOR::BLACK, _delete ? (int)COLOR::BLACK : (int)COLOR::LIGHT_VIOLET);
			cout << " ";
		}
		Gotoxy(19 * pos.x + 21,
			12 * pos.y + h);
		cout << " ";
	}
}

void BoardRender(Board & _board)
{
	Gotoxy(0, 0);
	
	for (int i = _board.hSize - 1; i >= 0; --i)
	{
		for (int j = 0; j < _board.wSize; ++j)
		{
			if (_board.board[j][i].data == 0)
			{
				ChangeColorByRank(0);
				TileRender(Pos(j, _board.hSize - 1 - i));
				
			}
			else
			{
				ChangeColorByRank(_board.board[j][i].skillData.rank);
				TileRender(Pos(j, _board.hSize - 1 - i), false, _board.board[j][i].skillData.name, _board.board[j][i].skillData.rank);
				cout << _board.board[j][i].data;
			}
		}
		cout << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		bool isReal = GET_SINGLE(GM)->player.actionSkills.size() > i;
		Skill _dataSkill;
		if (isReal)
		{
			_dataSkill = GET_SINGLE(GM)->player.actionSkills[i];
			ChangeColorByRank(_dataSkill.rank);
		}
		else
			ChangeColorByRank(0);

		TileRender({6 + i, 4}, true, isReal ? _dataSkill.name : "", isReal ? _dataSkill.rank : 0);
	}


	if (GET_SINGLE(GM)->player.CheckState() == CHARACTER_STATE::SELECT)
	{
		TileSelectRender(GET_SINGLE(GM)->lastCurPos, true);
		TileSelectRender(GET_SINGLE(GM)->curPos);
		GET_SINGLE(GM)->initTile = false;
	}
}

void BatRender()
{
	Enemy enemy = GET_SINGLE(GM)->enemy;

	Gotoxy(120, 10);
	cout << "     ,*-~'`^'* u_                               _u *'^`'~- *,		" << endl;
	Gotoxy(120, 11); 
	cout << "  p!^       /   jPw                           w9j \\         ^!p	" << endl;
	Gotoxy(120, 12); 
	cout << "w^.._      /      '\\_                      _/'     \\      _.^w	" << endl;
	Gotoxy(120, 13); 
	cout << "     *_   /          \\_      _    _      _/         \\    _* 	" << endl;
	Gotoxy(120, 14); 
	cout << "       q /           / \\q   ( `--` )   p/ \\          \\  p		" << endl;
	Gotoxy(120, 15); 
	cout << "       jj5****._    /    ^\\_) o  o (_/^    \\   _.****6jj		" << endl;
	Gotoxy(120, 16); 
	cout << "                *_ /      '==) ;; (=='       \\ _*				" << endl;
	Gotoxy(120, 17); 
	cout << "                 `/.w***,   /(    )\\   ,***w\\\"				" << endl;
	Gotoxy(120, 18); 
	cout << "                 ^ ilmk ^c / )    ( \\c^      					" << endl;
	Gotoxy(120, 19); 
	cout << "                          'V')_)(_('V'							" << endl;
	Gotoxy(120, 20); 
	cout << "                              `` ``								" << endl;

	Gotoxy(145, 22);
	cout << "체력 : " + enemy.ShowHp();
	Gotoxy(145, 23);
	cout << "다음 행동 : 공격";
}

void EnemyRender()
{
	SetColor((int)COLOR::WHITE);
	BatRender();
}
