
#include "Configuration.hpp"
#include "Patches.hpp"

#ifdef PLAYER
#include "Discord.hpp"
#endif

#ifdef SERVER
#include "Server.hpp"
#endif

#include "Hooks/Http.hpp"
#include "Hooks/Crypt.hpp"
#include "Hooks/CRoblox.hpp"

#ifdef _DEBUG
#include "Hooks/Context.hpp"
#endif

#ifdef SERVER
#include "Hooks/DataModel.hpp"
#include "Hooks/StandardOut.hpp"
#include "Hooks/ServerReplicator.hpp"
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
void __declspec(dllexport) entrypoint() {}
#endif