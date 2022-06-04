#include "pch.h"
#include "RCCOutput.h"
#include "Patches.h"

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
    // Message pointer is offset 4 bytes when the DLL is compiled as release
    message = reinterpret_cast<std::string*>((int)message + 4);
#endif

    if (message->compare("NewGame") == 0 || message->compare("NewGame2") == 0)
    {
        printf("\n");
        printf("Attempting to create new Game...\n");

        Game* game = new Game();
        int result = Game__construct(Game__initializeClass(game, 0));

        if (result)
        {
            printf("Failed to create new Game! (returned %d)\n", result);
        }
        else
        {
            printf("Successfully created new Game! (%p)\n", game);

            game->dataModel->jobId = "deez nuts";
            auto scriptContext = ServiceProvider__createScriptContext(game->dataModel.get());

            ScriptContext__execute(scriptContext, 5, "print(\"hi this should be inside the dll's created datamodel i think\")", "hi");
            ScriptContext__execute(scriptContext, 5, "print(\"job id: \" .. game.jobId)", "hi");
            ScriptContext__execute(scriptContext, 5, "printidentity()", "hi");

            printf("\n");
        }
    }

    switch (type)
    {
        case RBX__MESSAGE_OUTPUT:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            break;
        case RBX__MESSAGE_INFO:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            break;
        case RBX__MESSAGE_WARNING:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
            break;
        case RBX__MESSAGE_ERROR:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
    }

    printf("%s\n", message->c_str());
    SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}