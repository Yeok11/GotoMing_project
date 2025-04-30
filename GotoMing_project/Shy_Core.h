#pragma once
#include "Shy_Define.h"
#include "Shy_BM.h"
#include "02_HGameLogic.h"


enum class GAME_STATE
{
	TITLE,
	BATTLE,
	MOVE,
	PLAYERDATA,
	OPTION,
};


class GM : public BM
{
private:
	GM() = default;
	static GM* instance;

	void ShyUpdate();
	void Render(Board& _gameBoard);
	void playerInit();
	void ShowHelp();
	void ShowData();
	

public:
	GAME_STATE gameState;
	Player player;
	Pos curPos;
	Pos lastCurPos;

	char arrMap[MAP_HEIGHT][MAP_WIDTH] = {};
	char interfaceMap[MAP_HEIGHT][IMAP_WIDTH] = {};

	bool nextStage = true;
	bool nowAnimation = false;

	bool shyInit();
	void Run();
	bool curPosKeySet();
	void ActionChange();
	void EnemyAction();
	
	void PlayerAction();

	void InitMap();

	inline int InputKey()
	{
		int keyValue = 0;
		if (!nowAnimation)
			keyValue = _getch();

		return keyValue;
	}

	void ChangeGameState(GAME_STATE _gameState)
	{
		gameState = _gameState;

		switch (_gameState)
		{
		case GAME_STATE::TITLE:
			nextStage = true;
			return;
		case GAME_STATE::BATTLE:
			system("pause");
			system("cls");
			bInit(player);
			return;
		case GAME_STATE::MOVE:
			if (nextStage)
			{
				nextStage = false;
				MapLoad(&player.pos);
			}
			return;
		}
	}
	
public:
	static GM* GetInstance()
	{
		if (instance == nullptr)
			instance = new GM;

		return instance;
	}

	static void DestroyInst()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

private:
	
};

