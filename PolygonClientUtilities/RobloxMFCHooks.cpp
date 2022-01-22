#include "pch.h"
#include "RobloxMFCHooks.h"
#include "Config.h"
#include "Util.h"
#include "Logger.h"
#include "LUrlParser.h"

static bool hasAuthUrlArg = false;
static bool hasAuthTicketArg = false;
static bool hasJoinArg = false;
static bool hasJobId = false;
static bool setJobId = false;

static std::wstring authenticationUrl;
static std::wstring authenticationTicket;
static std::wstring joinScriptUrl;
static std::string jobId;

// Functions //

Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;
Crypt__verifySignatureBase64_t Crypt__verifySignatureBase64 = (Crypt__verifySignatureBase64_t)ADDRESS_CRYPT__VERIFYSIGNATUREBASE64;
#ifdef ARBITERBUILD
DataModel__getJobId_t DataModel__getJobId = (DataModel__getJobId_t)ADDRESS_DATAMODEL__GETJOBID;
StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;
// Network__RakNetAddressToString_t Network__RakNetAddressToString = (Network__RakNetAddressToString_t)ADDRESS_NETWORK__RAKNETADDRESSTOSTRING;
#endif
#if defined(MFC2010) || defined(MFC2011)
// CApp__CreateGame_t CApp__CreateGame = (CApp__CreateGame_t)ADDRESS_CAPP__CREATEGAME;
CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)ADDRESS_CROBLOXAPP__INITINSTANCE;
CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM;
#endif

// Hook Definitions //

BOOL __fastcall Http__trustCheck_hook(const char* url)
{
    LUrlParser::ParseURL parsedUrl = LUrlParser::ParseURL::parseURL(url);

    if (!parsedUrl.isValid())
        return false;

#ifdef ARBITERBUILD
    Logger::Log(LogType::Http, url);
#endif

    if (std::string("about:blank") == url)
        return true;

    if (std::find(Util::allowedSchemes.begin(), Util::allowedSchemes.end(), parsedUrl.scheme_) != Util::allowedSchemes.end())
        return std::find(Util::allowedHosts.begin(), Util::allowedHosts.end(), parsedUrl.host_) != Util::allowedHosts.end();

    if (std::find(Util::allowedEmbeddedSchemes.begin(), Util::allowedEmbeddedSchemes.end(), parsedUrl.scheme_) != Util::allowedEmbeddedSchemes.end())
        return true;

    return false;
}

void __fastcall Crypt__verifySignatureBase64_hook(HCRYPTPROV* _this, void*, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15)
{
    // the actual function signature is (HCRYPTPROV* _this, std::string message, std::string signatureBase64)
    // but for some reason it throws a memory access violation when you pass the parameters back into the function, without even modifying them
    // each char represents the beginning of new std::string (with the int parameters, that totalls to a length of 24 bytes)
    // the signature length is stored in a14 though so we can just use that

    if (a14 > 1024)
    {
        std::ostringstream error;
        error << "Signature too large.  " << a14 << " > 1024";
        throw std::runtime_error(error.str());
    }

    Crypt__verifySignatureBase64(_this, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
}

#ifdef ARBITERBUILD
int __fastcall DataModel__getJobId_hook(DataModel* _this, void*, int a2)
{
    // this only sets the job id when game.jobId is called by lua
    // so the gameserver script must call game.jobId at the beginning for this to take effect
    // also, this only applies to the first datamodel that is created

    if (!setJobId && hasJobId && !jobId.empty())
    {
        int jobIdPtr = (int)_this + STRUCTOFFSET_DATAMODEL__JOBID;
#ifdef NDEBUG
        jobIdPtr += 4;
#endif

        ((std::string*)jobIdPtr)->assign(jobId);

        setJobId = true;
    }

    return DataModel__getJobId(_this, a2);
}

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

    if (Logger::handle)
    {
#ifdef NDEBUG
        // for some reason, the location of the message pointer is offset 4 bytes when compiled as release
        // i assume doing this is safe? most of the examples ive seen use reinterpret_cast but this seems to work fine
        int messagePtr = (int)message + 4;
        std::string* message = (std::string*)messagePtr;
#endif

        switch (type)
        {
        case 1: // RBX::MESSAGE_OUTPUT:
            Logger::Log(LogType::Output, std::string("[MESSAGE_OUTPUT]     ") + *message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case 0: // RBX::MESSAGE_INFO:
            Logger::Log(LogType::Output, std::string("[MESSAGE_INFO]       ") + *message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case 2: // RBX::MESSAGE_WARNING:
            Logger::Log(LogType::Output, std::string("[MESSAGE_WARNING]    ") + *message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case 3: // RBX::MESSAGE_ERROR:
            Logger::Log(LogType::Output, std::string("[MESSAGE_ERROR]      ") + *message);
            SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        }
        printf("%s\n", message->c_str());
        SetConsoleTextAttribute(Logger::handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

// std::string __fastcall Network__RakNetAddressToString_hook(int raknetAddress, bool writePort, char portDelineator)
// {
//    Network__RakNetAddressToString(raknetAddress, writePort, portDelineator);
//    return std::string("hi");
// }
#endif

#if defined(MFC2010) || defined(MFC2011)
/* INT __fastcall CApp__CreateGame_hook(CApp* _this, void*, int a2, LPCWSTR a3)
{
    return CApp__CreateGame(_this, a2, a3);
} */

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    CApp* app = reinterpret_cast<CApp*>(CLASSLOCATION_CAPP);

    if (hasAuthUrlArg && hasAuthTicketArg && !authenticationUrl.empty() && !authenticationTicket.empty())
    {
        CApp__RobloxAuthenticate(app, NULL, authenticationUrl.c_str(), authenticationTicket.c_str());
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
        // command line args are parsed AFTER CRobloxApp::InitInstance is run, so the logger will too be initialized after

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