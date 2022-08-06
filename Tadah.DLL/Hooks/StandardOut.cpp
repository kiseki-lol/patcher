#include "pch.h"

#include "Hooks/StandardOut.h"

#ifdef SERVER

HANDLE outputHandle;

std::string httpLogPath;
std::string stdoutLogPath;

std::ofstream httpLog;
std::ofstream stdoutLog;

void InitializeOutput()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    outputHandle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, outputHandle);

    printf("Tadah.DLL v1.0.0\n");

#ifdef _DEBUG
    SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("Compiled as Debug\n\n");
#endif

    // Initialize file logging
    fs::create_directory(fs::path(Helpers::getModulePath()).parent_path() / "logs");

    std::string time = Helpers::getISOTimestamp();

    stdoutLogPath = (fs::path(Helpers::getModulePath()).parent_path() / "logs" / (time + "-StandardOut.log")).string();
    httpLogPath = (fs::path(Helpers::getModulePath()).parent_path() / "logs" / (time + "-Http.log")).string();

    stdoutLog.open(stdoutLogPath, std::ios::out);
    httpLog.open(stdoutLogPath, std::ios::out);

    stdoutLog << "Tadah.DLL v1.0.0 - StandardOut" << std::endl << std::endl;
    httpLog << "Tadah.DLL v1.0.0 - Http" << std::endl << std::endl;

    stdoutLog.close();
    httpLog.close();
}

StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

#ifndef _DEBUG
    // Message pointer is offset 4 bytes when the DLL is compiled as release
    message = reinterpret_cast<std::string*>((int)message + 4);
#endif

    std::string stringifiedType;
    std::string time = Helpers::getISOTimestamp();

    switch (type)
    {
        case RBX__MESSAGE_OUTPUT:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            stringifiedType = "out";
            break;
        case RBX__MESSAGE_INFO:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            stringifiedType = "info";
            break;
        case RBX__MESSAGE_WARNING:
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN);
            stringifiedType = "warn";
            break;
        case RBX__MESSAGE_ERROR:
            stringifiedType = "err";
            SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
    }
    
    printf("%s\n", message->c_str());
    SetConsoleTextAttribute(outputHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    stdoutLog.open(stdoutLogPath, std::ios::out);
    stdoutLog << "[" << time << "] [" << stringifiedType << "] " << message << std::endl;
    stdoutLog.close();
}

#endif