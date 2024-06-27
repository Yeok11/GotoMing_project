#pragma once
#include<Windows.h>
#include<iostream>
using std::cout;
using std::wcout;
using std::endl;

COORD GetConsoleResolution();
void LockResize();
void Gotoxy(int _x, int _y);
void SetCursorVis(bool _vis, DWORD _size);
void SetColor(int _textcolor = 15, int _bgcolor = 0);

enum class COLOR
{
	BLACK, BLUE, GREEN, SKYBLUE, RED,
	VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
	LIGHT_YELLOW, WHITE, END
};