#include "02_HGameLogic.h"
#include "Shy_Console.h"
#include "Shy_Core.h"
#include "Shy_Define.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>


bool isInfo = false;
bool wasTabPressed = false;
bool wasInfoKeyPressed = false;

int infoCursor = 11;

void SetReset()
{
    wasInfoKeyPressed = true;
    infoCursor = 11;
}

void KeyManager(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer) 
{
    _pPlayer->playerNewPos = _pPlayer->playerPos;
    
    //플레이어 이동
    if (GET_SINGLE(GM)->gameState == GAME_STATE::MOVE && !isInfo) {

        if (GetAsyncKeyState(VK_UP) & 0x8000)
            --_pPlayer->playerNewPos.y;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            ++_pPlayer->playerNewPos.y;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
            --_pPlayer->playerNewPos.x;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
            ++_pPlayer->playerNewPos.x;
        cout << _pPlayer->playerNewPos.x << " / " << _pPlayer->playerNewPos.y;

        if (_arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] == (char)OBJ_TYPE::ROAD) {
            _pPlayer->playerPos = _pPlayer->playerNewPos;
        }
        else if (_arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] == (char)OBJ_TYPE::ENEMY) {
            //적하고 닿았을떄
            _arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] = (char)OBJ_TYPE::ROAD;
            GM::GetInstance()->ChangeGameState(GAME_STATE::BATTLE);
        }
        else if (_arrMap[_pPlayer->playerNewPos.y][_pPlayer->playerNewPos.x] == (char)OBJ_TYPE::GOAL) {
            //골에 닿았을떄
            system("cls");
            cout << "탈출에 성공하였습니다!!";
            system("pause");
            GET_SINGLE(GM)->ChangeGameState(GAME_STATE::TITLE);
        }
    }

    _pPlayer->playerNewPos.x = std::clamp(_pPlayer->playerNewPos.x, 0, MAP_WIDTH - 1);
    _pPlayer->playerNewPos.y = std::clamp(_pPlayer->playerNewPos.y, 0, MAP_HEIGHT - 1);

    if (GetAsyncKeyState(VK_TAB) & 0x8000) { // TAB 키가 눌린 상태
        if (!wasTabPressed) { // 이전 프레임에서 TAB 키가 눌리지 않았을 때만 처리
            if (!isInfo) {
                isInfo = true;
            }
            else {
                isInfo = false;
            }
            wasTabPressed = true; // TAB 키가 눌렸음을 기록
        }
    }
    else {
        wasTabPressed = false; // TAB 키가 눌리지 않았음을 기록
    }

    if (isInfo) {
        if (!wasInfoKeyPressed) {
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (infoCursor < 27) {
                    Gotoxy(Map_Emtpy + 117, infoCursor);
                    std::cout << "    ";
                    infoCursor += 8;
                }
                wasInfoKeyPressed = true;
            }
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                if (infoCursor > 11) {
                    Gotoxy(Map_Emtpy + 117, infoCursor);
                    std::cout << "    ";
                    infoCursor -= 8;
                }
                wasInfoKeyPressed = true;
            }
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                if (infoCursor == 11) {
                    //플레이어 정보코드 구현
                    GET_SINGLE(GM)->ChangeGameState(GAME_STATE::PLAYERDATA);
                }
                else if (infoCursor == 19) 
                {
                    //도움말
                    GET_SINGLE(GM)->ChangeGameState(GAME_STATE::OPTION);
                }
                else if (infoCursor == 27) {
                    system("cls");
                    //타이틀로
                    GET_SINGLE(GM)->ChangeGameState(GAME_STATE::TITLE);
                }
            }
        }
        else {
            // 키가 떼어질 때까지 대기
            if (!(GetAsyncKeyState(VK_UP) & 0x8000) && !(GetAsyncKeyState(VK_DOWN) & 0x8000) && !(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
                wasInfoKeyPressed = false;
            }
        }
    }
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

void MapLoad(PPLAYER _pPlayer)
{
    _pPlayer->playerPos.x = 2;
    _pPlayer->playerPos.y = 15;
 
    //맵불러오기밍
    int stageNumber = rand() % 8 + 1;  // Default stage number

    std::string fileName = "stage" + std::to_string(stageNumber) + ".txt";
    std::fstream readMap(fileName);
    if (readMap.is_open()) {
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            readMap.getline(GET_SINGLE(GM)->arrMap[i], MAP_WIDTH);
            if (readMap.fail())
            {
                std::cout << "파일 에러";
            }
        }
    }

    std::fstream readMapInfo("Map\\info.txt");
    if (readMapInfo.is_open()) {
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            readMapInfo.getline(GET_SINGLE(GM)->interfaceMap[i], IMAP_WIDTH);
            if (readMapInfo.fail())
            {
                std::cout << "파일 에러";
            }
        }
    }
}

bool revealed[MAP_HEIGHT][MAP_WIDTH] = { false };

void MoveRender(char _arrMap[MAP_HEIGHT][MAP_WIDTH], PPLAYER _pPlayer, int SHADOW)
{
    if (GET_SINGLE(GM)->gameState == GAME_STATE::MOVE) {
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
                else if (_arrMap[i][j] == (char)OBJ_TYPE::EMPTY) 
                {
                    std::cout << "■";
                }
                else if (_arrMap[i][j] == (char)OBJ_TYPE::EMPTY)
                {
                    std::cout << " ";
                }
                // 시야에 비춰지고 있는 부분 출력
                else if (i >= _pPlayer->playerPos.y - SHADOW && i <= _pPlayer->playerPos.y + SHADOW && 
                    j >= _pPlayer->playerPos.x - SHADOW && j <= _pPlayer->playerPos.x + SHADOW) 
                {
                    if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
                        std::cout << "  ";
                    }
                    else if (_arrMap[i][j] == (char)OBJ_TYPE::OBSTACLE) {
                        std::cout << "◆";
                    }
                    else if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMY) {
                        std::cout << "※";
                    }
                    else if (_arrMap[i][j] == (char)OBJ_TYPE::GOAL)
                    {
                        std::cout << "＠";
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
                    else if (_arrMap[i][j] == (char)OBJ_TYPE::GOAL)
                    {
                        std::cout << "＠";
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
}

void InfoRender(char _infoarrMap[MAP_HEIGHT][IMAP_WIDTH], PPLAYER _pPlayer, int SHADOW)
{
    if (GET_SINGLE(GM)->gameState == GAME_STATE::MOVE) {
        for (int i = 0; i < MAP_HEIGHT; ++i) {
            for (int j = 0; j < IMAP_WIDTH - 1; ++j) {
                if (_infoarrMap[i][j] == (char)OBJ_TYPE::EMPTY) {
                    std::cout << "  ";
                }
                else if (_infoarrMap[i][j] == (char)OBJ_TYPE::EMPTY) {
                    std::cout << "■";
                }
                else if (_infoarrMap[i][j] == (char)OBJ_TYPE::ROAD) {
                    Gotoxy(Map_Emtpy + 103 + j * 2, +5 + i);
                }
            }
            std::cout << std::endl;
            Gotoxy(Map_Emtpy + 100, 6 + i);
            std::cout << " ";
        }
        Gotoxy(Map_Emtpy + 122, 11);
        std::cout << "플레이어 정보";
        Gotoxy(Map_Emtpy + 122, 19);
        std::cout << "도움말";
        Gotoxy(Map_Emtpy + 122, 27);
        std::cout << "타이틀화면";
        Gotoxy(Map_Emtpy + 117, infoCursor);
        std::cout << ">>";
    }
}
