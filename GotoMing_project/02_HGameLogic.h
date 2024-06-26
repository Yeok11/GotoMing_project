#pragma once

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 30;
//인터페이스아님 ㅋ
const int IMAP_WIDTH = 25;

const int Map_Emtpy = 5;
const int SHADOW = 3;

//구조체
typedef struct _tagpos
{
	int x;
	int y;

	bool operator ==(const _tagpos& _other) const
	{
		if (x == _other.x && y == _other.y)
			return true;
		else
			return false;
	}

}POS, * PPOS;

typedef struct _targetplayer {

	POS playerPos;
	POS playerNewPos;

}PLAYER, *PPLAYER;

enum class OBJ_TYPE {
	ROAD = '0', OBSTACLE, ENEMY, EMPTY
};

enum class GAMESTATE {
	PLAY = '0', INFO,
};

class SetGameState
{
public:
	GAMESTATE State;
	SetGameState() : State(GAMESTATE::PLAY){}
	void setState(GAMESTATE newState) {
		State = newState;
	}

};

//메서드 선언
void KeyManager(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, SetGameState& stateManager);
void Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, SetGameState& stateManager);
void FrameSync(unsigned int _Framerate);
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], char _infoarrMap[MAP_HEIGHT][IMAP_WIDTH], PPLAYER _pPlayer);
void GameRender(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, int SHADOW, SetGameState& stateManager);
void InfoRender(char _infoarrmap[MAP_HEIGHT][IMAP_WIDTH], PPLAYER _pPlayer, int SHADOW, SetGameState& stateManager);