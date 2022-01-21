#pragma once

#include "Config.h"

#include <oaidl.h>

#if defined(MFC2010) || defined(MFC2011)
class CWorkspace;

// 2010 struct definitions:
// 0x47E010: CWorkspace->DoExecScript()
// 0x47EC10: CWorkspace->ExecUrlScript()

const auto CWorkspace__ExecUrlScript = (HRESULT(__stdcall*)(CWorkspace * workspace, LPCWSTR, VARIANTARG, VARIANTARG, VARIANTARG, VARIANTARG, LPVOID))ADDRESS_CWORKSPACE__EXECURLSCRIPT;

struct CRobloxDoc
{
	void* padding1[40];
	CWorkspace* workspace;
};

struct CApp;

const auto CApp__CreateGame = (CWorkspace * (__thiscall*)(CApp * _this, LPCWSTR, LPCWSTR))ADDRESS_CAPP__CREATEGAME;
const auto CApp__RobloxAuthenticate = (void * (__thiscall*)(CApp * _this, LPCWSTR, LPCWSTR))ADDRESS_CAPP__ROBLOXAUTHENTICATE;

struct CRobloxApp;

// 2010 struct definitions:
// 0x405D20: CRobloxApp->CreateDocument()
// 0x44F6F0: CRobloxApp->ExitInstance()
// 0x452900: CRobloxApp->InitInstance()

const auto CRobloxApp__CreateDocument = (CRobloxDoc * (__thiscall*)(CRobloxApp * _this))ADDRESS_CROBLOXAPP__CREATEDOCUMENT;

struct CCommandLineInfo
{
	void* padding1[3];
	BOOL m_bRunAutomated;
};

class CRobloxCommandLineInfo : public CCommandLineInfo {};

const auto CCommandLineInfo__ParseLast = (void(__thiscall*)(CCommandLineInfo * _this, BOOL bLast))ADDRESS_CCOMMANDLINEINFO__PARSELAST;
#endif