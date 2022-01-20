#pragma once

#include <oaidl.h>

// CWorkspace
// 2010: 0x0047EC10
// 2011: 0x0049FC90

class CWorkspace;

const auto CWorkspace__ExecUrlScript = (HRESULT(__stdcall*)(CWorkspace * workspace, LPCWSTR, VARIANTARG, VARIANTARG, VARIANTARG, VARIANTARG, LPVOID))0x0047EC10;

// CRobloxDoc

class CRobloxDoc
{
private:
	void* padding1[40];
public:
	CWorkspace* workspace;
};

// CRobloxApp
// 2010: 0x0044F6E0
// 2011: 0x0045D030

class CRobloxApp;

const auto CRobloxApp__CreateDocument = (CRobloxDoc * (__thiscall*)(CRobloxApp * _this))0x0044F6E0;
// const auto CRobloxApp__CreateGame = (CWorkspace * (__thiscall*)(CRobloxApp * _this, LPCWSTR))0x00405D20; // is CApp the same thing as CRobloxApp??

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

const auto CCommandLineInfo__ParseLast = (void(__thiscall*)(CCommandLineInfo * _this, BOOL bLast))0x007A80A0;