#pragma once
#include<Windows.h>
#include<iostream>

using std::cout;
using std::wcout;
using std::endl;

COORD GetConsoleResolution();
void LockResize();