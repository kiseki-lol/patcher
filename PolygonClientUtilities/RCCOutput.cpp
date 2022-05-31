#include "pch.h"
#include "RCCOutput.h"

HANDLE outputHandle;

void InitializeOutput()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    outputHandle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, outputHandle);

#ifndef NDEBUG
    printf("[[[ DLL COMPILED AS DEBUG ]]]\n");
#endif

    // lol
    // printf("Access key read: \n");
    // printf("Current Access key: \n");
    // printf("Service starting...\n");
    // printf("Intializing Roblox Web Service\n");
    // printf("Service Started on port 64989\n");
}

StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

#ifdef NDEBUG
    // i have absolutely no clue why but the location of the message pointer is offset 4 bytes when the dll compiled as release
    int messagePtr = (int)message + 4;
    message = reinterpret_cast<std::string*>(messagePtr);
#endif

    switch (type)
    {
    case 1: // RBX::MESSAGE_OUTPUT:
        SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 0: // RBX::MESSAGE_INFO:
        SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case 2: // RBX::MESSAGE_WARNING:
        SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case 3: // RBX::MESSAGE_ERROR:
        SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    }
    printf("%s\n", message->c_str());
    SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}