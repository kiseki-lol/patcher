#pragma once

#include "RobloxMFCClasses.h"

#if defined(MFC2010) || defined(MFC2011)
typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this);

typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const char* pszParam, BOOL bFlag, BOOL bLast);
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast);
#endif

typedef void(__thiscall* Http__trustCheck_t)(const char* url);
extern Http__trustCheck_t Http__trustCheck;

BOOL __fastcall Http__trustCheck_hook(const char* url);

#ifdef ARBITERBUILD
typedef void(__thiscall* StandardOut__print_t)(void* _this, int type, const std::string& message);
extern StandardOut__print_t StandardOut__print;

void __fastcall StandardOut__print_hook(void* _this, void*, int type, const std::string& message);

// typedef void(__thiscall* Network__RakNetAddressToString_t)(int raknetAddress, bool writePort, char portDelineator);
// extern Network__RakNetAddressToString_t Network__RakNetAddressToString;

// std::string __fastcall Network__RakNetAddressToString_hook(int raknetAddress, bool writePort, char portDelineator);
#endif