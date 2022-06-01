#pragma once

#include "Classes.h"

typedef int (__thiscall* Game__construct_t)(Game* _this);
int __fastcall Game__construct_hook(Game* _this);
extern Game__construct_t Game__construct;