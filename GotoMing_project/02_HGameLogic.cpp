#include "02_HGameLogic.h"
#include "01_HConsole.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <fstream>

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
    else if (_arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] == (char)OBJ_TYPE::ENEMY) {
        
        //뒤지는 시스템 구현하세요 ㅇㅇ
        system("curl parrot.live");

    }
    _pPlayer->playerNewPos.x = std::clamp(_pPlayer->playerNewPos.x, 0, MAP_WIDTH - 2);
    _pPlayer->playerNewPos.y = std::clamp(_pPlayer->playerNewPos.y, 0, MAP_HEIGHT - 1);
}

void Update(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer)
{
    MovePlayer(_arrMap, _pPlayer);
    Sleep(10);
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

void Init(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer)
{
    _pPlayer->playerPos.x = 1;
    _pPlayer->playerPos.y = 1;
    system("title 21Bombman | mode con cols=160 lines=40");
    SetCursorVis(false, 1);

    std::fstream readMap("Map\\stage.txt");
    if (readMap.is_open()) {
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            readMap.getline(_arrMap[i], MAP_WIDTH);
            if (readMap.fail())
            {
                std::cout << "파일 에러";
            }
        }
    }
}

bool revealed[MAP_HEIGHT][MAP_WIDTH] = { false };

void Render(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, int SHADOW)
{
    // 불값으로 2차원 배열을 받아와 true인 경우에만 밝힐 수 있도록 사전작업
    for (int i = _pPlayer->playerPos.y - SHADOW; i <= _pPlayer->playerPos.y + SHADOW; ++i) {
        for (int j = _pPlayer->playerPos.x - SHADOW; j <= _pPlayer->playerPos.x + SHADOW; ++j) {
            if (i >= 0 && i < MAP_HEIGHT && j >= 0 && j < MAP_WIDTH) {
                revealed[i][j] = true;
            }
        }
    }

    // 맵을 출력합니다.
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH - 1; ++j) {

            // 플레이어 위치
            if (i == _pPlayer->playerPos.y && j == _pPlayer->playerPos.x) {
                std::cout << "＆";
            }
            // 빈 공간은 시야와 상관없이 항상 출력
            else if (_arrMap[i][j] == (char)OBJ_TYPE::EMPTY) {
                std::cout << "■";
            }
            // 시야에 비춰지고 있는 부분 출력
            else if (i >= _pPlayer->playerPos.y - SHADOW && i <= _pPlayer->playerPos.y + SHADOW &&
                j >= _pPlayer->playerPos.x - SHADOW && j <= _pPlayer->playerPos.x + SHADOW) {
                if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
                    std::cout << "  ";
                }
                else if (_arrMap[i][j] == (char)OBJ_TYPE::OBSTACLE) {
                    std::cout << "◆";
                }
                else if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMY) {
                    std::cout << "※";
                }
            }
            // 시야에 비춰진 영역 출력
            else if (revealed[i][j]) {
                if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
                    std::cout << "  ";
                }
                else if (_arrMap[i][j] == (char)OBJ_TYPE::OBSTACLE) {
                    std::cout << "◆";
                }
                else if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMY) {
                    std::cout << "※";
                }
            }
            // 맵의 다른 요소 출력 (아직 밝혀지지 않은 영역)
            else {
                std::cout << "▒ ";
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < Map_Emtpy; ++i) {
            std::cout << " ";
        }
    }
}
