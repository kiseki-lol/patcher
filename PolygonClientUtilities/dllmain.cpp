#include "pch.h"
#include "Config.h"
#include "Patches.h"

#include "Http.h"
#include "Crypt.h"

#ifdef _DEBUG
#include "Context.h"
#endif

#if defined(ARBITERBUILD)
#include "StandardOut.h"
#endif

#if defined(ARBITERBUILD) && defined(MFC2011)
#include "ReplicatorSecurity.h"
#endif

#if defined(ARBITERBUILD) && defined(PLAYER2012)
#include "Application.h"
#endif

#if defined(MFC2010) || defined(MFC2011)
#include "CRoblox.h"
#endif

START_PATCH_LIST()

ADD_PATCH(Http__httpGetPostWinInet, Http__httpGetPostWinInet_hook)
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)

ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)

#ifdef _DEBUG
ADD_PATCH(Context__requirePermission, Context__requirePermission_hook)
#endif

#ifdef ARBITERBUILD
ADD_PATCH(StandardOut__print, StandardOut__print_hook)
#endif

#if defined(ARBITERBUILD) && defined(MFC2011)
ADD_PATCH(ServerReplicator__sendTop, ServerReplicator__sendTop_hook)
ADD_PATCH(ServerReplicator__processTicket, ServerReplicator__processTicket_hook)
#endif

#if defined(ARBITERBUILD) && defined(PLAYER2012)
ADD_PATCH(Application__ParseArguments, Application__ParseArguments_hook)
#endif

#if defined(MFC2010) || defined(MFC2011)
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
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

        LONG patchesError = Patches::Apply();
        if (patchesError != NO_ERROR)
        {
#ifdef _DEBUG
            std::string message = "Patches::Apply returned " + std::to_string(patchesError);
            MessageBoxA(nullptr, message.c_str(), nullptr, MB_ICONERROR);
#endif

            ExitProcess(EXIT_FAILURE);
        }

        CURLcode curlError = curl_global_init(CURL_GLOBAL_DEFAULT);
        if (curlError != CURLE_OK)
        {
#ifdef _DEBUG
            std::string message = "curl_global_init returned " + std::to_string(curlError);
            MessageBoxA(nullptr, message.c_str(), nullptr, MB_ICONERROR);
#endif

            ExitProcess(EXIT_FAILURE);
        }
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        curl_global_cleanup();
    }

    return TRUE;
}