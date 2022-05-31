#include "pch.h"
#include "Config.h"
#include "Patches.h"
// #include "RobloxMFCHooks.h"

#include "TrustCheck.h"
#include "VerifySignatureBase64.h"

#ifdef ARBITERBUILD
#include "RCCOutput.h"

#ifdef MFC2011
#include "ReplicatorSecurity.h"
#endif

#ifdef PLAYER2012
#include "PlayerCommandLine.h"
#endif
#endif

#if defined(MFC2010) || defined(MFC2011)
#include "MFCCommandLine.h"
#endif

START_PATCH_LIST()
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)
ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)

#ifdef ARBITERBUILD
// ADD_PATCH(DataModel__getJobId, DataModel__getJobId_hook)
ADD_PATCH(StandardOut__print, StandardOut__print_hook)
// ADD_PATCH(Network__RakNetAddressToString, Network__RakNetAddressToString_hook)

#ifdef MFC2011
ADD_PATCH(ServerReplicator__sendTop, ServerReplicator__sendTop_hook)
ADD_PATCH(ServerReplicator__processTicket, ServerReplicator__processTicket_hook)
#endif

#ifdef PLAYER2012
ADD_PATCH(Application__ParseArguments, Application__ParseArguments_hook)
#endif
#endif

#if defined(MFC2010) || defined(MFC2011)
// ADD_PATCH(CApp__CreateGame, CApp__CreateGame_hook)
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
#endif

#ifdef DEBUG_SERVERREPLICATOR__PROCESSPACKET
// ADD_PATCH(ServerReplicator__processPacket, ServerReplicator__processPacket_hook)
#endif
END_PATCH_LIST()

// DLLs for release will be loaded with VMProtect, so this isn't necessary
// Arbiter will still use Stud_PE for ease in swapping DLLs however
// #ifdef ARBITERBUILD
void __declspec(dllexport) import() {}
// #endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
#ifdef ARBITERBUILD
        InitializeOutput();
#endif

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