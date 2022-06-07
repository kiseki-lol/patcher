#include "pch.h"

#include "Patches.h"
#include "Util.h"
#include "Hooks/Application.h"

#if defined(ARBITERBUILD) && defined(PLAYER2012)

Application__ParseArguments_t Application__ParseArguments = (Application__ParseArguments_t)ADDRESS_APPLICATION__PARSEARGUMENTS;

BOOL __fastcall Application__ParseArguments_hook(int _this, void*, int a2, const char* argv)
{
    std::map<std::string, std::string> argslist = Util::parseArgs(argv);

    if (argslist.count("-jobId"))
    {
        /*
            Erase everything that comes after the -jobId argument.
            
            Dirty quick hack that *shouldn't* matter in production
            since the Arbiter starts up the player with arguments in
            such an order that this won't affect anything.
        */

        char* pch = (char*)strstr(argv, " -jobId");
        if (pch != NULL)
            strncpy_s(pch, strlen(pch) + 1, "", 0);
    }

    return Application__ParseArguments(_this, a2, argv);
}

#endif