#pragma once
void TitleRender();
bool TitleScene();
void InfoRender();

enum class MENU
{
	START, INFO, QUIT
};
MENU MenuRender();
enum class KEY
{
	UP, DOWN, SPACE, FAIL
};
KEY KeyController();
void EnterAnimation();