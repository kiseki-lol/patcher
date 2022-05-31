#pragma once

#include "Classes.h"

typedef BOOL(__thiscall* Http__trustCheck_t)(const char* url);
BOOL __fastcall Http__trustCheck_hook(const char* url);
extern Http__trustCheck_t Http__trustCheck;
