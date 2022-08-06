#include "pch.h"
#include "Configuration.h"
#include "Patches.h"

#ifndef ARBITER
#include "Discord.h"
#endif

#include "Hooks/Http.h"
#include "Hooks/Crypt.h"

#ifdef _DEBUG
#include "Hooks/Context.h"
#endif

#ifdef ARBITER
#include "Hooks/StandardOut.h"
#include "Hooks/ServerReplicator.h"
#endif

#include "Hooks/CRoblox.h"

START_PATCH_LIST()

ADD_PATCH(Http__httpGetPostWinInet, Http__httpGetPostWinInet_hook)
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)

ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)

#ifdef _DEBUG
ADD_PATCH(Context__requirePermission, Context__requirePermission_hook)
#endif

#ifdef ARBITER
ADD_PATCH(StandardOut__print, StandardOut__print_hook)
#endif

#if defined(ARBITER) && defined(MFC2011)
ADD_PATCH(ServerReplicator__sendTop, ServerReplicator__sendTop_hook)
ADD_PATCH(ServerReplicator__processTicket, ServerReplicator__processTicket_hook)
#endif

#if defined(ARBITER) && defined(PLAYER2012)
ADD_PATCH(Application__ParseArguments, Application__ParseArguments_hook)
#endif

#if defined(MFC2010) || defined(MFC2011)
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
#endif

END_PATCH_LIST()

void __declspec(dllexport) import() {}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
#ifdef ARBITER
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

#ifndef ARBITER
        InitializeDiscord();
#endif
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        curl_global_cleanup();

#ifndef ARBITER
        CleanupDiscord();
#endif
    }

    return TRUE;
}