#pragma once

#include "Classes.h"

typedef BOOL(__thiscall* Application__ParseArguments_t)(int _this, int a2, const char* argv);
BOOL __fastcall Application__ParseArguments_hook(int _this, void*, int a2, const char* argv);
extern Application__ParseArguments_t Application__ParseArguments;