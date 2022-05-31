#include "pch.h"
#include "RCCOutput.h"
#include "Logger.h"

StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

    if (Logger::handle)
    {
#ifdef NDEBUG
        // i have absolutely no clue why but the location of the message pointer is offset 4 bytes when the dll compiled as release
        int messagePtr = (int)message + 4;
        std::string* message = reinterpret_cast<std::string*>(messagePtr);
#endif

        Logger::Print(type, *message);
    }
}