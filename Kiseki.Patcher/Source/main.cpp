#include <windows.h>

#include "Globals.hpp"
#include "Patcher.hpp"

#ifdef SERVER
#include "Server.hpp"
#endif

#ifdef PLAYER
#include "Discord.hpp"
#endif

#include "Hooks/Http.hpp"
#include "Hooks/Crypt.hpp"
#include "Hooks/CRoblox.hpp"

#ifdef SERVER
#include "Hooks/DataModel.hpp"
#include "Hooks/ServerReplicator.hpp"
#endif

START_PATCH_LIST()

ADD_PATCH(Http__httpGetPostWinInet, Http__httpGetPostWinInet_hook)
ADD_PATCH(Http__trustCheck, Http__trustCheck_hook)

ADD_PATCH(Crypt__verifySignatureBase64, Crypt__verifySignatureBase64_hook)

#if defined(PLAYER) || defined(SERVER)
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
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
        LONG patchesError = Patcher::Apply();
        if (patchesError != NO_ERROR)
        {
#ifdef _DEBUG
            std::string message = "Patches::Apply returned " + std::to_string(patchesError);
            MessageBoxW(nullptr, std::wstring(message.begin(), message.end()).c_str(), nullptr, MB_ICONERROR);
#endif

            ExitProcess(EXIT_FAILURE);
        }

        CURLcode curlError = curl_global_init(CURL_GLOBAL_DEFAULT);
        if (curlError != CURLE_OK)
        {
#ifdef _DEBUG
            std::string message = "curl_global_init returned " + std::to_string(curlError);
            MessageBoxW(nullptr, std::wstring(message.begin(), message.end()).c_str(), nullptr, MB_ICONERROR);
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
    }

    return TRUE;
}

void __declspec(dllexport) entrypoint() {}