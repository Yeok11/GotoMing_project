#pragma once

const int MAP_WIDTH = 21;
const int MAP_HEIGHT = 20;

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
	ROAD = '0',
};

//메서드 선언
void FrameSync(unsigned int _Framerate);
void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);
void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH]);