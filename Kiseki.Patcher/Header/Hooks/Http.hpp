#pragma once

#include <string>

#include <curl/curl.h>

#include "Globals.hpp"
#include "Helpers.hpp"

typedef bool(__thiscall* Http__trustCheck_t)(const char* url);

bool __fastcall Http__trustCheck_hook(const char* url);

extern Http__trustCheck_t Http__trustCheck;