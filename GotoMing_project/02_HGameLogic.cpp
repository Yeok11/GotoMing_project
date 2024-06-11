#include "02_HGameLogic.h"
#include "01_HConsole.h"

#include<algorithm>
#include<iostream>
#include<ctime>
#include<fstream>

void MovePlayer(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer)
{
	_pPlayer->playerNewPos = _pPlayer->playerPos;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		--_pPlayer->playerNewPos.y;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		++_pPlayer->playerNewPos.y;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		--_pPlayer->playerNewPos.x;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		++_pPlayer->playerNewPos.x;

	if (_arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] == (char)OBJ_TYPE::ROAD) {

		_pPlayer->playerPos = _pPlayer->playerNewPos;

	}

	_pPlayer->playerNewPos.x = std::clamp(_pPlayer->playerNewPos.x, 0, MAP_WIDTH - 2);
	_pPlayer->playerNewPos.y = std::clamp(_pPlayer->playerNewPos.y, 0, MAP_HEIGHT - 1);
 }

void Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer)
{
	MovePlayer(_arrMap, _pPlayer);
	Sleep(100);
}

void FrameSync(unsigned int _Framerate)
{
	clock_t oldtime, curtime;
	oldtime = clock();
	while (true)
	{
		curtime = clock();
		if (curtime - oldtime > 1000 / _Framerate)
		{
			oldtime = curtime;
			break;
		}
	}
}

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH])
{
	SetCursorVis(false, 1);

	std::fstream readMap("Map\\stage.txt");
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail())
				std::cout << "파일 에러";
		}
	}
}
bool revealed[MAP_HEIGHT][MAP_WIDTH] = { false };

void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, int SHADOW)
{
	for (int i = _pPlayer->playerPos.y - SHADOW; i <= _pPlayer->playerPos.y + SHADOW; ++i) {
		for (int j = _pPlayer->playerPos.x - SHADOW; j <= _pPlayer->playerPos.x + SHADOW; ++j) {
			if (i >= 0 && i < MAP_HEIGHT && j >= 0 && j < MAP_WIDTH) {
				revealed[i][j] = true;
			}
		}
	}
	for(int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			// 플레이어의 현재 위치 확인
			if (i == _pPlayer->playerPos.y && j == _pPlayer->playerPos.x) {
				std::cout << "＆";
			}
			// 플레이어 주위 2블록 반경에 있는지 확인
			else if (i >= _pPlayer->playerPos.y - SHADOW && i <= _pPlayer->playerPos.y + SHADOW &&
				j >= _pPlayer->playerPos.x - SHADOW && j <= _pPlayer->playerPos.x + SHADOW) {
				std::cout << "  ";
			}
			else if (revealed[i][j]) {
				std::cout << "  ";
			}
			// 맵의 다른 요소 출력
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
				std::cout << "■";
			}
			else {
				// 다른 객체에 대한 처리 추가
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}
