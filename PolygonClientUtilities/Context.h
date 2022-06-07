#pragma once

#include "Classes.h"

typedef void (__thiscall* Context__requirePermission_t)(void* _this, int permission, const char* operation);
void __fastcall Context__requirePermission_hook(void* _this, void*, int permission, const char* operation);
extern Context__requirePermission_t Context__requirePermission;