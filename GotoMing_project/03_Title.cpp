#include<iostream>
#include<fcntl.h>
#include<io.h>
#include "HTitle.h"
#include "01_Hconsole.h"
void TitleRender()
{
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"██████╗  ██████╗ ███╗   ███╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗" << endl;
	wcout << L"██╔══██╗██╔═══██╗████╗ ████║██╔══██╗████╗ ████║██╔══██╗████╗  ██║" << endl;
	wcout << L"██████╔╝██║   ██║██╔████╔██║██████╔╝██╔████╔██║███████║██╔██╗ ██║" << endl;
	wcout << L"██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║" << endl;
	wcout << L"██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝██║ ╚═╝ ██║██║  ██║██║ ╚████║" << endl;
	wcout << L"╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝" << endl;
	int curmode = _setmode(_fileno(stdout), prevmode);
}

bool TitleScene()
{
	while (true)
	{
		system("cls");
		TitleRender();
		MENU eMenu = MenuRender();
		switch (eMenu)
		{
		case MENU::START:
			EnterAnimation();
			// Intro 애니메이션.
			return true;
		case MENU::INFO:
			InfoRender();
			break;
		case MENU::QUIT:
			return false;
		}
	}
}

void InfoRender()
{
	system("cls");
	cout << "[조작법 ]" << endl;
	Sleep(100);
	// 만약, 그 전까지는 얘가 계속 출력
	// 되어 있는 상태여야하는데, 
	// 스페이스바가 눌렸으면. 나가져야돼.
	while (true)
	{
		if (KeyController() == KEY::SPACE)
			break;
	}
}

MENU MenuRender()
{
	COORD Resolution = GetConsoleResolution();
	int x = Resolution.X / 3;  // 2.5
	int y = Resolution.Y / 2.5;// 3
	int originy = y;
	Gotoxy(x, y);
	cout << "게임 시작";
	Gotoxy(x, y + 1);
	cout << "게임 정보";
	Gotoxy(x, y + 2);
	cout << "게임 종료";
	while (true)
	{
		KEY eKey = KeyController();
		switch (eKey)
		{
		case KEY::UP:
			if (originy < y)
			{
				Gotoxy(x - 2, y);
				cout << " ";
				Gotoxy(x - 2, --y);
				cout << ">";
				Sleep(100);
			}
			break;
		case KEY::DOWN:
			if (originy + 2 > y)
			{
				Gotoxy(x - 2, y);
				cout << " ";
				Gotoxy(x - 2, ++y);
				cout << ">";
				Sleep(100);
			}
			break;
		case KEY::SPACE:
		{
			if (y == originy)
				return MENU::START;
			else if (y == originy + 1)
				return MENU::INFO;
			else if (y == originy + 1)
				return MENU::QUIT;
		}
		break;
		}
	}
}

KEY KeyController()
{
	// 입력처리?
	//if(getch()) // 1
	if (GetAsyncKeyState(VK_UP) & 0x8000) // 2
	{
		return KEY::UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 2
	{
		return KEY::DOWN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) // 2
	{
		Sleep(50);
		return KEY::SPACE;
	}
	return KEY::FAIL;
}

void EnterAnimation()
{
	COORD Resolution = GetConsoleResolution();
	int width = Resolution.X;
	int height = Resolution.Y;
	int anitime = 20;
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
}
