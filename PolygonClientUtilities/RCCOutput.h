#pragma once

#include "Classes.h"

void InitializeOutput();

typedef void(__thiscall* StandardOut__print_t)(int _this, int type, std::string* message);
void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message);
extern StandardOut__print_t StandardOut__print;