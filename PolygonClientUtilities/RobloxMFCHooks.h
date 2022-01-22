#pragma once

#include "RobloxMFCClasses.h"

// #include <atlstr.h>

// Type Definitions //

typedef BOOL(__thiscall* Http__trustCheck_t)(const char* url);
typedef void(__thiscall* Crypt__verifySignatureBase64_t)(HCRYPTPROV* _this, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15);
#ifdef ARBITERBUILD
typedef INT(__thiscall* DataModel__getJobId_t)(char* _this, int a2);
typedef void(__thiscall* StandardOut__print_t)(int _this, int type, std::string* message);
// typedef void(__thiscall* Network__RakNetAddressToString_t)(int raknetAddress, bool writePort, char portDelineator);
#endif
#if defined(MFC2010) || defined(MFC2011)
// typedef INT(__thiscall* CApp__CreateGame_t)(CApp* _this, int a2, LPCWSTR a3);
typedef void(__thiscall* CWorkspace__ExecUrlScript_t)(CWorkspace* workspace, LPCWSTR url, VARIANTARG arg1, VARIANTARG arg2, VARIANTARG arg3, VARIANTARG arg4, LPVOID voidptr);
typedef CRobloxDoc*(__thiscall* CRobloxApp__CreateDocument_t)(CRobloxApp* _this);
typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const char* pszParam, BOOL bFlag, BOOL bLast);
#endif

// Externals //

extern Http__trustCheck_t Http__trustCheck;
extern Crypt__verifySignatureBase64_t Crypt__verifySignatureBase64;
#ifdef ARBITERBUILD
extern DataModel__getJobId_t DataModel__getJobId;
extern StandardOut__print_t StandardOut__print;
// extern Network__RakNetAddressToString_t Network__RakNetAddressToString;
#endif
#if defined(MFC2010) || defined(MFC2011)
// extern CApp__CreateGame_t CApp__CreateGame;
extern CWorkspace__ExecUrlScript_t CWorkspace__ExecUrlScript;
extern CRobloxApp__CreateDocument_t CRobloxApp__CreateDocument;
extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;
#endif

// Hook Declarations //

BOOL __fastcall Http__trustCheck_hook(const char* url);
void __fastcall Crypt__verifySignatureBase64_hook(HCRYPTPROV* _this, void*, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15);
#ifdef ARBITERBUILD
INT  __fastcall DataModel__getJobId_hook(char* _this, void*, int a2);
void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message);
// std::string __fastcall Network__RakNetAddressToString_hook(int raknetAddress, bool writePort, char portDelineator);
#endif
#if defined(MFC2010) || defined(MFC2011)
// INT  __fastcall CApp__CreateGame_hook(CApp* _this, void*, int a2, LPCWSTR a3);
void  __fastcall CWorkspace__ExecUrlScript_hook(CWorkspace* _this, void*, LPCWSTR url, VARIANTARG arg1, VARIANTARG arg2, VARIANTARG arg3, VARIANTARG arg4, LPVOID voidptr);
CRobloxDoc* __fastcall CRobloxApp__CreateDocument_hook(CRobloxApp* _this);
BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this);
void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast);
#endif