#include "pch.h"
#include "Config.h"
#include "Patches.h"
#include "RobloxMFCHooks.h"

START_PATCH_LIST()
#ifdef ADDRESS_CROBLOXAPP__INITINSTANCE
ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
#endif
#ifdef ADDRESS_CROBLOXCOMMANDLINEINFO__PARSEPARAM
ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)
#endif
#ifdef ARBITERBUILD
ADD_PATCH(StandardOut__print, StandardOut__print_hook)
#endif
END_PATCH_LIST()

// To be added to game imports
void __declspec(dllexport) doNothing() {}

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