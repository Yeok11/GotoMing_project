#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>

using std::cout;
using std::cin;
using std::wcout;
using std::vector;
using std::string;
using std::endl;

enum class CHARACTER_STATE
{
	WAIT,
	SELECT,
	BATTLE,
	MOVE
};


#define GET_SINGLE(c) c::GetInstance()
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define dWAIT CHARACTER_STATE::WAIT
#define dSELECT CHARACTER_STATE::SELECT
#define dBATTLE CHARACTER_STATE::BATTLE
#define dMOVE CHARACTER_STATE::MOVE
#define	Or(v, a, b) (v == a || v == b) 

