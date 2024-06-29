#include "Shy_Render.h"
#include "SkillsList.h"
#include "Shy_Core.h"
#include <ctime>

GM* GM::instance = nullptr;

bool GM::Init()
{
	system("mode con: cols=160 lines=40");

	srand((unsigned int)time(NULL));
	SetCursorVis(false, 1);
	SetScreen();
	curPos = Pos(0, 0);
	player = Player(10, CHARACTER_STATE::WAIT);
	Skill * skill = new FireBall();
	player.SetSkill(skill);
	delete skill;
	skill = new SwordAttack();
	player.SetSkill(skill, 3);
	delete skill;
	skill = new BodyAttack();
	player.SetSkill(skill, 2);
	delete skill;
	skill = new Punch();
	player.SetSkill(skill);
	delete skill;
	skill = new Shiled();
	player.SetSkill(skill);
	delete skill;
	

	ChangeGameState(GAME_STATE::BATTLE);

	return false;
}

void GM::Run()
{
	Render(battleBoard);
	Sleep(500);
	

	while (true)
	{
		Update();
		Render(battleBoard);

		Sleep(50);
	}
}

bool GM::curPosKeySet()
{
	int key = InputKey();

	//enter
	if (key == 13)
		return true;

	//¡∂¿€≈∞
	if (key == 119)
		--curPos.y;
	if (key == 115)
		++curPos.y;
	if (key == 97)
		--curPos.x;
	if (key == 100)
		++curPos.x;

	return false;
}

void GM::Update()
{
	switch (gameState)
	{
	case GAME_STATE::TITLE:
		break;
	case GAME_STATE::BATTLE:
		ActionChange();
		break;
	case GAME_STATE::MOVE:
		break;
	case GAME_STATE::PLAYERDATA:
		break;
	case GAME_STATE::OPTION:
		break;	
	}
}

void GM::Render(Board& _gameBoard)
{
	BoardRender(_gameBoard);
	EnemyRender();
}
void GM::PlayerAction()
{
	switch (player.CheckState())
	{
	case dWAIT:
		battleBoard.CheckBoard(initTile);
		break;

	case dSELECT:
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
		system("pause");

		enemy.UseSkill(player);
		enemy.actionSkills.erase(enemy.actionSkills.begin());
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