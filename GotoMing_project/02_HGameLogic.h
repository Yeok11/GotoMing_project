#pragma once

const int MAP_WIDTH = 75;
const int MAP_HEIGHT = 35;

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
	ROAD = '0', OBSTACLE, ENEMY,
};

//메서드 선언
void MovePlayer(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer);
void Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer);
void FrameSync(unsigned int _Framerate);
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, int SHADOW);