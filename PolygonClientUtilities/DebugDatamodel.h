#pragma once

#include "Classes.h"

typedef int (__thiscall* DataModel__createDataModel_t)(bool startHeartbeat);
int __fastcall DataModel__createDataModel_hook(int, int, int, bool startHeartbeat);
extern DataModel__createDataModel_t DataModel__createDataModel;

// Game::Game
/* typedef int(__thiscall* DataModel__createDataModel_t)(int _this);
int __fastcall DataModel__createDataModel_hook(int _this);
extern DataModel__createDataModel_t DataModel__createDataModel; */