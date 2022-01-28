#include "pch.h"
#include "Config.h"
#include "Patches.h"
#include "RobloxMFCHooks.h"
#include "Logger.h" // remove when testing is done

START_PATCH_LIST()
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)
ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)
#ifdef ARBITERBUILD
ADD_PATCH(DataModel__getJobId, DataModel__getJobId_hook)
ADD_PATCH(StandardOut__print, StandardOut__print_hook)
// ADD_PATCH(Network__RakNetAddressToString, Network__RakNetAddressToString_hook)
#ifdef PLAYER2012
ADD_PATCH(Application__ParseArguments, Application__ParseArguments_hook)
#endif
#endif
#if (defined(MFC2010) || defined(MFC2011)) && (defined(PLAYERBUILD) || defined(ARBITERBUILD))
// ADD_PATCH(CApp__CreateGame, CApp__CreateGame_hook)
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
#endif
END_PATCH_LIST()

// DLLs for release will be loaded with VMProtect, so this isn't necessary
// Arbiter will still use Stud_PE for ease in swapping DLLs however
#ifdef ARBITERBUILD
void __declspec(dllexport) doNothing() {}
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        LONG error = Patches::Apply();
        if (error != NO_ERROR)
        {
#ifdef _DEBUG
            std::string message = "Patches::Apply returned " + std::to_string(error);
            MessageBoxA(nullptr, message.c_str(), nullptr, MB_ICONERROR);
#endif

            ExitProcess(EXIT_FAILURE);
        }
    }

    return TRUE;
}