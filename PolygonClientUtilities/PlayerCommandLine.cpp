#include "pch.h"
#include "PlayerCommandLine.h"
#include "Util.h"

Application__ParseArguments_t Application__ParseArguments = (Application__ParseArguments_t)ADDRESS_APPLICATION__PARSEARGUMENTS;

BOOL __fastcall Application__ParseArguments_hook(int _this, void*, int a2, const char* argv)
{
    std::map<std::string, std::string> argslist = Util::parseArgs(argv);

    if (argslist.count("-jobId"))
    {
        // now we have to exclude the -jobId arg from argv
        // i'm being really lazy here, so don't do this
        // i'm just gonna erase everything that comes after the -jobId arg
        // thats gonna cause issues if the joinscript params are after the jobId arg,
        // but really it shouldn't matter because the arbiter always starts it up in the correct order

        char* pch = (char*)strstr(argv, " -jobId");
        if (pch != NULL)
            strncpy_s(pch, strlen(pch) + 1, "", 0);
    }

    return Application__ParseArguments(_this, a2, argv);
}