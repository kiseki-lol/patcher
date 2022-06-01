#include "pch.h"
#include "RCCOutput.h"
#include "DebugGame.h"
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
    // i have absolutely no clue why but the location of the message pointer is offset 4 bytes when the dll compiled as release
    int messagePtr = (int)message + 4;
    message = reinterpret_cast<std::string*>(messagePtr);
#endif

    /* if (message->compare("MakeDatamodel") == 0)
    {
        printf("Attempting to create DataModel...\n");
        DataModel__createDataModel(true);
    } */

    if (message->compare("NewGame") == 0)
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
            // int datamodel = game[4];
            printf("Successfully created new Game! (%p)\n", game);
            // printf("Address of DataModel: %08X\n", game->dataModel);
            // printf("Attempting to set DataModel Job ID to 'deez nuts'...\n");
            // game->dataModel->jobId = "deez nuts";
            printf("Length of DataModel Job ID: %d\n", game->dataModel->jobId.length());

            printf("Attempting to create service provider...\n");

            void* dataModelPointer = game->dataModel.get();
            printf("Address of dataModelPointer: %p\n", dataModelPointer);

            printf("Calling ServiceProvider::create<ScriptContext>()...\n");
            void* scriptContext = ServiceProvider__createScriptContext(dataModelPointer);
            printf("Address of scriptContext: %p\n", scriptContext);

            printf("Calling ScriptContext::execute()...\n");
            // void* arg;
            // ScriptContext__execute(scriptContext, &arg, 1, "print('hi')", "hi", 0);
            ScriptContext__execute(scriptContext, 1, "print('hi')", "hi");

            // printf("Calling ScriptContext::setTimeout()...\n");
            // ScriptContext__setTimeout(scriptContext, 5);

            printf("\n");
        }
    }

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