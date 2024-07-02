#pragma once
#include <Windows.h>
void Gotoxy(int _x, int _y);
void SetColor(int _textcolor, int _bgcolor = 0);
void SetScreen();
void SetCursorVis(bool _vis, DWORD _size);


enum class COLOR
{
    BLACK, BLUE, GREEN, SKYBLUE, RED,
    VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
    LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
    LIGHT_YELLOW, WHITE, END
};