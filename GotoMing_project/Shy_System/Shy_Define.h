#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>

#include "Shy_Skill.h"


using std::cout;
using std::cin;
using std::vector;
using std::endl;

#define GET_SINGLE(c) c::GetInstance()
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}