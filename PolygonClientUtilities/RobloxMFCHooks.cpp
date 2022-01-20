#include "pch.h"
#include "RobloxMFCHooks.h"

static HANDLE handle;
static std::ofstream jobLog;

static bool hasJoinArg = false;
static bool hasJobId = false;

static std::wstring joinScriptUrl;
static std::string jobId;

// 2010: 0x00452900;
// 2011: 0x004613C0;

CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)0x00452900;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    if (hasJoinArg && !joinScriptUrl.empty())
    {
        try
        {
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

// 2010: 0x00450AC0;
// 2011: 0x0045EE50;

CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)0x00450AC0;

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

    if (bFlag && _stricmp(pszParam, "j") == 0)
    {
        hasJoinArg = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

    if (bFlag && _stricmp(pszParam, "jobId") == 0)
    {
        hasJobId = true;
        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

    CRobloxCommandLineInfo__ParseParam(_this, pszParam, bFlag, bLast);
}

// 2010: 0x0059F340;
// 2011: 0x005B25E0;

StandardOut__print_t StandardOut__print = (StandardOut__print_t)0x0059F340;

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