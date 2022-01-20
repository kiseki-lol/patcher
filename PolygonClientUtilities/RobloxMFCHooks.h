#pragma once

#include "RobloxMFCClasses.h"

typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this);

typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const char* pszParam, BOOL bFlag, BOOL bLast);
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast);

#ifdef ARBITERBUILD
typedef void(__thiscall* StandardOut__print_t)(void* _this, int type, const std::string& message);
extern StandardOut__print_t StandardOut__print;

void __fastcall StandardOut__print_hook(void* _this, void*, int type, const std::string& message);
#endif