#include "pch.h"
#include "RobloxMFCHooks.h"
#include "Logger.h"
#include "Config.h"
#include "LUrlParser.h"

static bool hasAuthUrlArg = false;
static bool hasAuthTicketArg = false;
static bool hasJoinArg = false;
static bool hasJobId = false;

static std::wstring authenticationUrl;
static std::wstring authenticationTicket;
static std::wstring joinScriptUrl;
static std::string jobId;

#if defined(MFC2010) || defined(MFC2011)
CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)ADDRESS_CROBLOXAPP__INITINSTANCE;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    if (hasAuthUrlArg && hasAuthTicketArg && !authenticationUrl.empty() && !authenticationTicket.empty())
    {
        // TODO: implement this using CApp__RobloxAuthenticate
    }

    if (hasJoinArg && !joinScriptUrl.empty())
    {
        try
        {
            // TODO: use CApp__CreateGame instead
            CRobloxDoc* document = CRobloxApp__CreateDocument(_this);
            CWorkspace__ExecUrlScript(document->workspace, joinScriptUrl.c_str(), VARIANTARG(), VARIANTARG(), VARIANTARG(), VARIANTARG(), nullptr);
        }
        catch (std::runtime_error& exception)
        {
            MessageBoxA(nullptr, exception.what(), nullptr, MB_ICONERROR);
            return FALSE;
        }
    }

    return TRUE;
}

CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM;

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const char* pszParam, BOOL bFlag, BOOL bLast)
{
    if (hasJoinArg && joinScriptUrl.empty())
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        joinScriptUrl.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &joinScriptUrl[0], size);

        _this->m_bRunAutomated = TRUE;

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

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

#ifdef ARBITERBUILD
    if (hasJobId && jobId.empty())
    {
        jobId = std::string(pszParam);
        Logger::Initialize(jobId);

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

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

    if (bFlag && _stricmp(pszParam, "j") == 0)
    {
        hasJoinArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

#ifdef ARBITERBUILD
    if (bFlag && _stricmp(pszParam, "jobId") == 0)
    {
        hasJobId = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
#endif

    CRobloxCommandLineInfo__ParseParam(_this, pszParam, bFlag, bLast);
}
#endif

Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

BOOL __fastcall Http__trustCheck_hook(const char* url)
{
    const std::vector<std::string> allowedHosts
    {
        "polygon.pizzaboxer.xyz",
        "polygondev.pizzaboxer.xyz",
        "polygonapi.pizzaboxer.xyz",

        "roblox.com",
        "www.roblox.com",
        "assetdelivery.roblox.com",

        "tadah.rocks",
        "www.tadah.rocks"
    };

    const std::vector<std::string> allowedSchemes
    {
        "http",
        "https",
        "ftp",
    };

    const std::vector<std::string> allowedEmbeddedSchemes
    {
        "javascript",
        "jscript",
        "res",
    };

    LUrlParser::ParseURL parsedUrl = LUrlParser::ParseURL::parseURL(url);

    if (!parsedUrl.isValid()) 
        return false;

#ifdef ARBITERBUILD
    Logger::Log(LogType::Http, url);
#endif

    if (std::string("about:blank") == url) 
        return true;

    if (std::find(allowedSchemes.begin(), allowedSchemes.end(), parsedUrl.scheme_) != allowedSchemes.end())
        return std::find(allowedHosts.begin(), allowedHosts.end(), parsedUrl.host_) != allowedHosts.end();

    if (std::find(allowedEmbeddedSchemes.begin(), allowedEmbeddedSchemes.end(), parsedUrl.scheme_) != allowedEmbeddedSchemes.end())
        return true;

    return false;
}

#ifdef ARBITERBUILD
StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string& message)
{
    StandardOut__print(_this, type, message);

    // so there's a slight issue here
    // when the dll is compiled as release, the message's location is sometimes offset by 8 bytes
    // 
    // here's when it works properly:
    // https://media.discordapp.net/attachments/377894067712950275/934077740192235520/x32dbg_U1Y4T8xnev.png
    // the message pointer location of [EBP+0xC] (0x0019F8DC) and value (0x0019F8E0) have a valid string as seen on the stack
    //
    // and here's when it doesn't work properly:
    // https://cdn.discordapp.com/attachments/377894067712950275/934080068110655568/unknown.png
    // the pointer location of [EBP+0xC] (0x0019FD2C) just points to nothing (0x04A88C70)
    // however the pointer location with an actual valid string is just 8 bytes ahead (0x0019FD34)
    // wtf??

#ifndef NDEBUG
    if (Logger::handle)
    {
        switch (type)
        {
        case 1: // RBX::MESSAGE_OUTPUT:
            // Logger::Log(LogType::Output, std::string("[MESSAGE_OUTPUT]     ") + message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 0: // RBX::MESSAGE_INFO:
            // Logger::Log(LogType::Output, std::string("[MESSAGE_INFO]       ") + message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case 2: // RBX::MESSAGE_WARNING:
            // Logger::Log(LogType::Output, std::string("[MESSAGE_WARNING]    ") + message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case 3: // RBX::MESSAGE_ERROR:
            // Logger::Log(LogType::Output, std::string("[MESSAGE_ERROR]      ") + message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        }
        printf("%s\n", message.c_str());
        SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
#endif
}

// Network__RakNetAddressToString_t Network__RakNetAddressToString = (Network__RakNetAddressToString_t)ADDRESS_NETWORK__RAKNETADDRESSTOSTRING;

// std::string __fastcall Network__RakNetAddressToString_hook(int raknetAddress, bool writePort, char portDelineator)
// {
//    Network__RakNetAddressToString(raknetAddress, writePort, portDelineator);
//    return std::string("hi");
// }
#endif