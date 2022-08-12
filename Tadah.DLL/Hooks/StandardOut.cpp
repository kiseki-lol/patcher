#include "pch.h"

#include "Hooks/StandardOut.h"

#ifdef SERVER

StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

#ifdef SERVER
    if (Server::Handle)
    {
#ifndef _DEBUG
        // Message pointer is offset 4 bytes when the DLL is compiled as release
        message = reinterpret_cast<std::string*>((int)message + 4);
#endif

        Server::Log::Output((LogSeverity)type, message->c_str());
    }
#endif
}

#endif