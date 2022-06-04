#pragma once

#include "Classes.h"

typedef void (__thiscall* Http__httpGetPostWinInet_t)(Http* _this, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6);
void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6);
extern Http__httpGetPostWinInet_t Http__httpGetPostWinInet;