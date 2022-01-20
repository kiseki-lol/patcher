#pragma once

#include "Config.h"
#include <oaidl.h>

// CWorkspace
// 2010: 0x0047EC10
// 2011: 0x0049FC90

class CWorkspace;

const auto CWorkspace__ExecUrlScript = (HRESULT(__stdcall*)(CWorkspace * workspace, LPCWSTR, VARIANTARG, VARIANTARG, VARIANTARG, VARIANTARG, LPVOID))ADDRESS_CWORKSPACE__EXECURLSCRIPT;

// CRobloxDoc

class CRobloxDoc
{
private:
	void* padding1[40];
public:
	CWorkspace* workspace;
};

// CApp

class CApp;

const auto CApp__CreateGame = (CWorkspace * (__thiscall*)(CApp * _this, LPCWSTR, LPCWSTR))ADDRESS_CAPP__CREATEGAME;
const auto CApp__RobloxAuthenticate = (void * (__thiscall*)(CApp * _this, LPCWSTR, LPCWSTR))ADDRESS_CAPP__ROBLOXAUTHENTICATE;

// CRobloxApp
// 2010: 0x0044F6E0
// 2011: 0x0045D030

class CRobloxApp
{
private:
	void* padding1[124];
public:
	CApp* app;
};

const auto CRobloxApp__CreateDocument = (CRobloxDoc * (__thiscall*)(CRobloxApp * _this))ADDRESS_CROBLOXAPP__CREATEDOCUMENT;

// CRobloxCommandLineInfo
// 2010: 0x007A80A0
// 2011: 0x0081354A

class CCommandLineInfo
{
private:
	void* padding1[3];
public:
	BOOL m_bRunAutomated;
};

class CRobloxCommandLineInfo : public CCommandLineInfo {};

const auto CCommandLineInfo__ParseLast = (void(__thiscall*)(CCommandLineInfo * _this, BOOL bLast))ADDRESS_CCOMMANDLINEINFO__PARSELAST;