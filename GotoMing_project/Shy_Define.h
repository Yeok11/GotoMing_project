#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::endl;

#include "Shy_Skill.h"
#include "Shy_Board.h"



#define GET_SINGLE(c) c::GetInstance()
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}