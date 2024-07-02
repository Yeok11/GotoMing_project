#include<fcntl.h>
#include<io.h>
#include "Shy_Console.h"
#include "Shy_Core.h"
#include"02_HGameLogic.h"
#include "HTitle.h"

int y = 22;
bool isStart = false;
bool aa = false;

void TitleRender()
{
	Gotoxy(0, 0);
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << endl;
	wcout << endl;
	wcout << endl;
	wcout << L"                                          ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄      ▄██████▄     ▄████████  ▄██████▄  ███▄▄▄▄  " << endl;
	wcout << L"                                        ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄   ███    ███   ███    ███ ███    ███ ███▀▀▀██▄" << endl;
	wcout << L"                                        ███   ███   ███ ███▌ ███   ███   ███    █▀    ███    █▀  ███    ███ ███   ███" << endl;
	wcout << L"                                        ███   ███   ███ ███▌ ███   ███  ▄███         ▄███▄▄▄     ███    ███ ███   ███" << endl;
	wcout << L"                                        ███   ███   ███ ███▌ ███   ███ ▀▀███ ████▄  ▀▀███▀▀▀     ███    ███ ███   ███" << endl;
	wcout << L"                                        ███   ███   ███ ███  ███   ███   ███    ███   ███    █▄  ███    ███ ███   ███" << endl;
	wcout << L"                                        ███   ███   ███ ███  ███   ███   ███    ███   ███    ███ ███    ███ ███   ███" << endl;
	wcout << L"                                         ▀█   ███   █▀  █▀    ▀█   █▀    ████████▀    ██████████  ▀██████▀   ▀█   █▀ " << endl;
	int curmode = _setmode(_fileno(stdout), prevmode);
}

void TitleScene()
{
	Chosse();
}

void Chosse()
{
	Gotoxy(62 + 10, 20);
	std::cout << "게임시작";
	Gotoxy(62 + 10, 22);
	std::cout << "종료";

	if (!aa && GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_DOWN)) {
		aa = true;
	}
	if (aa) {
		if (GetAsyncKeyState(VK_UP) && y == 22) {
			Gotoxy(62 + 4, 20);
			std::cout << ">>";
			Gotoxy(62 + 4, 22);
			std::cout << "    ";
			y = 20;
		}

		if (GetAsyncKeyState(VK_DOWN) && y == 20) {
			Gotoxy(62 + 4, 22);
			std::cout << ">>";
			Gotoxy(62 + 4, 20);
			std::cout << "    ";
			y = 22;
		}

		if (GetAsyncKeyState(VK_SPACE) && y == 20) {
			SetReset();
			system("cls");
			EnterAnimation();
		}

		if (GetAsyncKeyState(VK_SPACE) && y == 22) {
			exit(0);
		}
	}
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


void EnterAnimation()
{
	COORD Resolution = GetConsoleResolution();
	int width = Resolution.X;
	int height = Resolution.Y;
	int anitime = 7;
	system("cls");

	for (int i = 0; i < 5; ++i)
	{
		Gotoxy(0, 0);
		SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
		system("cls");
		Sleep(anitime);
		SetColor((int)COLOR::WHITE);
		system("cls");
		Sleep(anitime);
	}

	// 크로스 되는 애니메이션을 추가
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	for (int i = 0; i < width / 2; ++i)
	{
		for (int j = 0; j < height; j += 2)
		{
			Gotoxy(i * 2, j);
			cout << "  ";
		}
		for (int j = 1; j < height; j += 2)
		{
			Gotoxy(width - 2 - i * 2, j);
			cout << "  ";
		}
		Sleep(anitime);
	}
	SetColor((int)COLOR::WHITE);
	system("cls");

	GET_SINGLE(GM)->ChangeGameState(GAME_STATE::MOVE);
}
