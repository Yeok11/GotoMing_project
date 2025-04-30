#include "Shy_Render.h"
#include "SkillsList.h" 
#include "Shy_Console.h"
#include "Shy_Core.h"
#include "HTitle.h"

GM* GM::instance = nullptr;

bool GM::shyInit()
{
	system("mode con: cols=160 lines=40");
	playerInit();
	srand((unsigned int)time(NULL));
	SetCursorVis(false, 1);
	SetScreen();
	curPos = Pos(0, 0);
	
	ChangeGameState(GAME_STATE::BATTLE);

	return false;
}

void GM::playerInit()
{
	player = Player(25, CHARACTER_STATE::WAIT);

	//기본 스킬
	Skill* skill = new FireBall();
	player.SetSkill(skill);
	delete skill;
	skill = new SwordAttack();
	player.SetSkill(skill);
	delete skill;
	skill = new BodyAttack();
	player.SetSkill(skill);
	delete skill;
	skill = new Punch();
	player.SetSkill(skill);
	delete skill;
	skill = new ThrowSand();
	player.SetSkill(skill);
	delete skill;
	skill = new Head();
	player.SetSkill(skill);
	delete skill;
}

void GM::Run()
{
	while (true)
	{
		ShyUpdate();
		Render(battleBoard);

		Sleep(70);
	}
}

bool GM::curPosKeySet()
{
	int key = InputKey();

	//enter
	if ((key == 13 || key == 32) && battleBoard.board[curPos.x][battleBoard.hSize - 1 - curPos.y].data != 0)
		return true;

	if (key == 224)
		key = _getch();

	//조작키
	if ((key == 119 || key == 72) && curPos.y > 0)
		--curPos.y;
	if ((key == 115 || key == 80) && curPos.y < battleBoard.hSize - 1)
		++curPos.y;
	if ((key == 97 || key == 75) && curPos.x > 0)
		--curPos.x;
	if ((key == 100 || key == 77) && curPos.x < battleBoard.wSize - 1)
		++curPos.x;

	return false;
}

void GM::ShowHelp() 
{
	#pragma region 설명충

	system("cls");
	cout << "상화좌우 키로 조작이 가능하며 선택은 Spacebar로 진행합니다." << endl;
	cout << "＠에 도달하면 클리어할 수 있습니다." << endl << endl;

	cout << "전투에서 타일은 자신의 차례가 시작될때만 떨어지며 합성과 중력은 항상 작용합니다." << endl;
	cout << "카드는 세 개까지 선택이 가능하며 카드의 등급은 7성까지 색이 변홥니다." << endl;
	cout << "색의 순서는 민트 -> 노랑 -> 빨강 -> 연한 노랑 -> 녹색 -> 하늘 -> 연한 빨강입니다." << endl << endl;
	cout << endl << "*아직 미숙한 것들이 많습니다." << endl;
	#pragma endregion


	system("pause");
	system("cls");
	GET_SINGLE(GM)->ChangeGameState(GAME_STATE::MOVE);
	SetReset();
}

void GM::ShowData()
{
	system("cls");
	cout << "체력 : " << player.ShowHp() << endl;

	system("pause");
	system("cls");
	GET_SINGLE(GM)->ChangeGameState(GAME_STATE::MOVE);
	SetReset();
}

void GM::ShyUpdate()
{
	switch (gameState)
	{
	case GAME_STATE::TITLE:
		TitleScene();
		break;
	case GAME_STATE::BATTLE:
		ActionChange();
		break;
	case GAME_STATE::MOVE:
		KeyManager(arrMap, &player.pos);
		break;
	case GAME_STATE::PLAYERDATA:
		ShowData();
		break;
	case GAME_STATE::OPTION: //도움말
		ShowHelp();
		break;
	}
}

void GM::Render(Board& _gameBoard)
{
	if (gameState == GAME_STATE::BATTLE)
	{
		nowAnimation = true;
		BoardRender(_gameBoard);
		EnemyRender();
		PlayerHpRender(player);

		if (enemy.hp <= 0)
		{
			system("cls");
			cout << "적을 처치했습니다." << endl << endl;
			system("pause");
			system("cls");
			ChangeGameState(GAME_STATE::TITLE);
		}
		else if (player.hp <= 0)
		{
			system("cls");
			cout << "고것도 못게쥬~! ㅋ" << endl << endl;
			system("pause");
			ChangeGameState(GAME_STATE::TITLE);
		}
			
	}
	else if (gameState == GAME_STATE::TITLE)
	{
		TitleRender();
	}
	else if (gameState == GAME_STATE::MOVE)
	{
		Gotoxy(5, 5);
		MoveRender(arrMap, &player.pos, SHADOW);
		InfoRender(interfaceMap, &player.pos, SHADOW);
	}
}
void GM::PlayerAction()
{
	switch (player.CheckState())
	{
	case dWAIT:
		battleBoard.CheckBoard(initTile);
		break;

	case dSELECT:
		if (nowAnimation) return;
		
		Sleep(50);
		lastCurPos = curPos;

		if (curPosKeySet())
		{
			battleBoard.InputSkill(curPos, player);

			player.ChangeState(dWAIT);
		}
		break;

	case dBATTLE:
		if (player.actionSkills.size() != 0)
		{
			player.UseSkill(enemy);
			player.actionSkills.erase(player.actionSkills.begin());
		}
		else
		{
			//enemy action
			playerTurn = false;
			player.ChangeState(dWAIT);
			enemy.ChangeState(dBATTLE);
		}
		break;
	}
}

void GM::EnemyAction()
{
	switch (enemy.CheckState())
	{
	case dBATTLE:
		enemy.UseSkill(player);
		enemy.actionSkills.erase(enemy.actionSkills.begin());
		Gotoxy(145, 30);
		cout << "적의 공격!";

		Sleep(1500);

		Gotoxy(145, 30);
		cout << "            ";

		enemy.SetNextAction();
		enemy.ChangeState(dWAIT);
		initTile = true;
		playerTurn = true;
		return;
	}
}


void GM::ActionChange()
{
	if (playerTurn)
	{
		PlayerAction();
	}
	else
	{
		EnemyAction();
	}
}