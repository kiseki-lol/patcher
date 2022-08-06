#include "pch.h"

#include "Hooks/CRoblox.h"

std::string ticket = "";

static bool hasAuthUrlArg = false;
static bool hasAuthTicketArg = false;
static bool hasJoinArg = false;

static std::wstring authenticationUrl;
static std::wstring authenticationTicket;
static std::wstring joinScriptUrl;

CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)ADDRESS_CROBLOXAPP__INITINSTANCE;
CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    CApp* app = reinterpret_cast<CApp*>(CLASSLOCATION_CAPP);

    if (hasAuthUrlArg && hasAuthTicketArg && !authenticationUrl.empty() && !authenticationTicket.empty())
    {
        CApp__RobloxAuthenticate(app, nullptr, authenticationUrl.c_str(), authenticationTicket.c_str());
    }

#ifndef SERVER
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
#endif

    return TRUE;
}

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast)
{
#ifndef SERVER
    if (hasJoinArg && joinScriptUrl.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        joinScriptUrl.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &joinScriptUrl[0], size);

        _this->m_bRunAutomated = TRUE;

        CCommandLineInfo__ParseLast(_this, bLast);
        
        // Parse the joinScriptUrl for it's placeId here
        try
        {
            CURLU* curl = curl_url();
            CURLUcode result = curl_url_set(curl, CURLUPART_URL, Helpers::ws2s(joinScriptUrl).c_str(), 0);

            if (result == CURLE_OK)
            {
                char* query;
                curl_url_get(curl, CURLUPART_QUERY, &query, 0);
                curl_url_cleanup(curl);

                std::map<std::string, std::string> parameters = Helpers::parseQueryString(std::string(query));
                if (parameters.find("ticket") != parameters.end())
                {
                    ticket = parameters["ticket"];
                }
            }
        }
        catch (...)
        {
            //
        }

        if (ticket.empty())
        {
            ExitProcess(EXIT_FAILURE);
        }

        return;
    }
#endif

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

#ifndef SERVER
    if (bFlag && _stricmp(pszParam, "j") == 0)
    {
        hasJoinArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

    CRobloxCommandLineInfo__ParseParam(_this, pszParam, bFlag, bLast);
}