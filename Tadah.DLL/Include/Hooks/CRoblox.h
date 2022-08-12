#pragma once

#include <curl/curl.h>

#include "Configuration.h"
#include "Helpers.h"
#include "Discord.h"

class CWorkspace;

const auto CWorkspace__ExecUrlScript = (HRESULT(__stdcall*)(CWorkspace * workspace, LPCWSTR, VARIANTARG, VARIANTARG, VARIANTARG, VARIANTARG, LPVOID))ADDRESS_CWORKSPACE__EXECURLSCRIPT;

struct CRobloxDoc
{
    void* padding1[CLASSPADDING_CROBLOXDOC__WORKSPACE];
    CWorkspace* workspace;
};

struct CApp;

const auto CApp__RobloxAuthenticate = (void* (__thiscall*)(CApp * _this, LPVOID, LPCWSTR, LPCWSTR))ADDRESS_CAPP__ROBLOXAUTHENTICATE;

struct CRobloxApp;

const auto CRobloxApp__CreateDocument = (CRobloxDoc * (__thiscall*)(CRobloxApp * _this))ADDRESS_CROBLOXAPP__CREATEDOCUMENT;

struct CCommandLineInfo
{
    void* padding1[3];
    BOOL m_bRunAutomated;
};

class CRobloxCommandLineInfo : public CCommandLineInfo {};

const auto CCommandLineInfo__ParseLast = (void(__thiscall*)(CCommandLineInfo * _this, BOOL bLast))ADDRESS_CCOMMANDLINEINFO__PARSELAST;

typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const char* pszParam, BOOL bFlag, BOOL bLast);

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this);
void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast);

extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;

extern std::wstring jobId;
extern bool hasJobId;