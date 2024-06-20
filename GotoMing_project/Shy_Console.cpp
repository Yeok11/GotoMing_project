#include <Windows.h>
#include "Shy_Console.h"

void Gotoxy(int _x, int _y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체
	COORD Cur = { _x, _y };
	// 콘솔 커서의 위치를 강제 이동시키는 함수
	SetConsoleCursorPosition(hOut, Cur);
}

void SetColor(int _textcolor, int _bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (_bgcolor << 4) | _textcolor);
}

void SetCursorVis(bool _vis, DWORD _size)
{
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.bVisible = _vis;
	curinfo.dwSize = _size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void SetScreen()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	HWND console = GetConsoleWindow();
	if (nullptr != console)
	{
		LONG style = GetWindowLong(console, GWL_STYLE);
		style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
		SetWindowLong(console, GWL_STYLE, style);
	}
}