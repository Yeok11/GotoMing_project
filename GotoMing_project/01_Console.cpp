#include<Windows.h>

#include"01_HConsole.h"

void LockResize()
{
	HWND console = GetConsoleWindow();
	if (nullptr != console)
	{
		LONG style = GetWindowLong(console, GWL_STYLE);
		style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;// &~WS_CAPTION;
		SetWindowLong(console, GWL_STYLE, style);
	}
}

void SetColor(int _textcolor, int _bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)
		, (_bgcolor << 4) | _textcolor);
}

COORD GetConsoleResolution()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &info);
	short width = info.srWindow.Right - info.srWindow.Left + 1;
	short height = info.srWindow.Bottom - info.srWindow.Top + 1;
	return COORD{ width, height };
}

void Gotoxy(int _x, int _y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체.
	COORD Cur = { _x, _y }; // *2가 자연스러울수도있음.
	// 콘솔 커서의 위치를 강제 이동시키는 함수.
	SetConsoleCursorPosition(hOut, Cur);
}

void SetCursorVis(bool _vis, DWORD _size)
{
	CONSOLE_CURSOR_INFO curinfo;
	curinfo.bVisible = _vis; // on, off
	curinfo.dwSize = _size; // 1~100
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE)
		, &curinfo);
}
