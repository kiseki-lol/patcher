#pragma once

#include "Classes.h"

typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const char* pszParam, BOOL bFlag, BOOL bLast);

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this);
void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast);

extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;