#include "pch.h"
#include "Config.h"
#include "RobloxMFCHooks.h"

static HANDLE handle;
static std::ofstream jobLog;

static bool hasAuthUrlArg = false;
static bool hasAuthTicketArg = false;
static bool hasJoinArg = false;
static bool hasJobId = false;

static std::wstring authenticationUrl;
static std::wstring authenticationTicket;
static std::wstring joinScriptUrl;
static std::string jobId;

CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)ADDRESS_CROBLOXAPP__INITINSTANCE;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    if (hasAuthUrlArg && hasAuthTicketArg && !authenticationUrl.empty() && !authenticationTicket.empty())
    {
        // TODO: implement this
    }

    if (hasJoinArg && !joinScriptUrl.empty())
    {
        try
        {
            // TODO: use CApp__CreateGame instead
            CRobloxDoc* document = CRobloxApp__CreateDocument(_this);
            // CWorkspace__ExecUrlScript(document->workspace, joinScriptUrl.c_str(), VARIANTARG(), VARIANTARG(), VARIANTARG(), VARIANTARG(), nullptr);
            
            // CApp__CreateGame(NULL, L"", L"44340105256");
            // CApp__RobloxAuthenticate(_this->app, L"http://polygondev.pizzaboxer.xyz/", L"test");
            // CRobloxApp__CreateDocument(_this);
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
        jobLog = std::ofstream(jobId + std::string(".txt"));

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        handle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        SetStdHandle(STD_OUTPUT_HANDLE, handle);

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

#ifdef ARBITERBUILD
StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(void* _this, void*, int type, const std::string& message)
{
    switch (type)
    {
        case 1: // RBX::MESSAGE_OUTPUT:
            jobLog << "[RBX::MESSAGE_OUTPUT]     " << message.c_str() << std::endl;
            SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 0: // RBX::MESSAGE_INFO:
            jobLog << "[RBX::MESSAGE_INFO]       " << message.c_str() << std::endl;
            SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case 2: // RBX::MESSAGE_WARNING:
            jobLog << "[RBX::MESSAGE_WARNING]    " << message.c_str() << std::endl;
            SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case 3: // RBX::MESSAGE_ERROR:
            jobLog << "[RBX::MESSAGE_ERROR]      " << message.c_str() << std::endl;
            SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
    }
    printf("%s\n", message.c_str());
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    StandardOut__print(_this, type, message);
}
#endif