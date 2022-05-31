#pragma once

#include "Classes.h"

typedef void(__thiscall* Crypt__verifySignatureBase64_t)(HCRYPTPROV* _this, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15);
void __fastcall Crypt__verifySignatureBase64_hook(HCRYPTPROV* _this, void*, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15);
extern Crypt__verifySignatureBase64_t Crypt__verifySignatureBase64;