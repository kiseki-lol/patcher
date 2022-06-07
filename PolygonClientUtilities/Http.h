#pragma once

#include "Classes.h"
#include <curl/curl.h>
#include <rapidjson/document.h>

typedef void (__thiscall* Http__httpGetPostWinInet_t)(Http* _this, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6);
typedef bool(__thiscall* Http__trustCheck_t)(const char* url);

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6);
bool __fastcall Http__trustCheck_hook(const char* url);

extern Http__httpGetPostWinInet_t Http__httpGetPostWinInet;
extern Http__trustCheck_t Http__trustCheck;