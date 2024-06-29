#pragma once
#include "Shy_Define.h"
#include "Shy_BM.h"


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

	void Update();
	void Render(Board& _gameBoard);
	

public:
	GAME_STATE gameState;
	Player player;
	Pos curPos;
	Pos lastCurPos;
	
	bool Init();
	void Run();
	bool curPosKeySet();

	void ActionChange();
	void EnemyAction();
	void PlayerAction();

	inline int InputKey()
	{
		int keyValue = _getch();

		return keyValue;
	}

	void ChangeGameState(GAME_STATE _gameState)
	{
		gameState = _gameState;

		switch (_gameState)
		{
		case GAME_STATE::TITLE:
			return;
		case GAME_STATE::BATTLE:
			bInit();
			return;
		case GAME_STATE::MOVE:
			return;
		case GAME_STATE::PLAYERDATA:
			return;
		case GAME_STATE::OPTION:
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

