#include "pch.h"

#include "Configuration.h"
#include "Patches.h"

#ifndef SERVER
#include "Discord.h"
#endif

#ifdef SERVER
#include "Server.h"
#endif

#include "Hooks/Http.h"
#include "Hooks/Crypt.h"
#include "Hooks/CRoblox.h"

#ifdef _DEBUG
#include "Hooks/Context.h"
#endif

#ifdef SERVER
#include "Hooks/DataModel.h"
#include "Hooks/StandardOut.h"
#include "Hooks/ServerReplicator.h"
#endif

START_PATCH_LIST()

ADD_PATCH(Http__httpGetPostWinInet, Http__httpGetPostWinInet_hook)
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)

ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)

ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)

#ifdef _DEBUG
ADD_PATCH(Context__requirePermission, Context__requirePermission_hook)
#endif

#ifdef SERVER
ADD_PATCH(DataModel__getJobId, DataModel__getJobId_hook)

ADD_PATCH(StandardOut__print, StandardOut__print_hook)

ADD_PATCH(ServerReplicator__sendTop, ServerReplicator__sendTop_hook)
ADD_PATCH(ServerReplicator__processTicket, ServerReplicator__processTicket_hook)
#endif

END_PATCH_LIST()

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
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

#ifdef PLAYER
        Discord::Cleanup();
#endif

#ifdef SERVER
        if (Server::Handle)
        {
            Server::Cleanup();
        }
#endif
    }

    return TRUE;
}

#ifdef SERVER
void __declspec(dllexport) melo() {}
#endif