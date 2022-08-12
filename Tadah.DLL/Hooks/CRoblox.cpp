#include "pch.h"

#include "Hooks/CRoblox.h"

#ifdef SERVER
#include "Server.h"
#endif

bool hasAuthUrlArg = false;
bool hasAuthTicketArg = false;
bool hasJoinArg = false;
bool hasJobIdArg = false;

std::wstring authenticationUrl;
std::wstring authenticationTicket;
std::wstring joinScriptUrl;
std::wstring jobId;

CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)ADDRESS_CROBLOXAPP__INITINSTANCE;
CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
    {
        return FALSE;
    }

    CApp* app = reinterpret_cast<CApp*>(CLASSLOCATION_CAPP);

#ifndef SERVER
    if (hasAuthUrlArg && hasAuthTicketArg && !authenticationUrl.empty() && !authenticationTicket.empty())
    {
        CApp__RobloxAuthenticate(app, nullptr, authenticationUrl.c_str(), authenticationTicket.c_str());
    }
#endif

    if (hasJoinArg && !joinScriptUrl.empty())
    {
        try
        {
            CRobloxDoc* document = CRobloxApp__CreateDocument(_this);
            CWorkspace__ExecUrlScript(document->workspace, joinScriptUrl.c_str(), VARIANTARG(), VARIANTARG(), VARIANTARG(), VARIANTARG(), nullptr);
        }
        catch (std::runtime_error)
        {
            return FALSE;
        }
    }

    return TRUE;
}

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast)
{
    if (hasJoinArg && joinScriptUrl.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        joinScriptUrl.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &joinScriptUrl[0], size);

        _this->m_bRunAutomated = TRUE;

        CCommandLineInfo__ParseLast(_this, bLast);

#ifndef SERVER
        Discord::Initialize(Helpers::ws2s(joinScriptUrl));
#endif
    }

#ifndef SERVER
    if (hasAuthUrlArg && authenticationUrl.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        authenticationUrl.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &authenticationUrl[0], size);

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

    if (hasAuthTicketArg && authenticationTicket.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        authenticationTicket.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &authenticationTicket[0], size);

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

#ifdef SERVER
    if (hasJobIdArg && jobId.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        jobId.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &jobId[0], size);

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

#ifndef SERVER
    if (bFlag && _stricmp(pszParam, "a") == 0)
    {
        hasAuthUrlArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

    if (bFlag && _stricmp(pszParam, "t") == 0)
    {
        hasAuthTicketArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

    if (bFlag && _stricmp(pszParam, "j") == 0)
    {
        hasJoinArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

#ifdef SERVER
    if (bFlag && _stricmp(pszParam, "jobId") == 0)
    {
        hasJobIdArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);

        Server::Initialize(jobId);

        return;
    }
#endif

    CRobloxCommandLineInfo__ParseParam(_this, pszParam, bFlag, bLast);
}