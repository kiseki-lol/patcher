#include "pch.h"
#include "Logger.h"

#pragma warning(disable : 4996)

HANDLE Logger::handle;
std::ofstream Logger::outputLog;
std::ofstream Logger::httpLog;

void Logger::Initialize(const std::string jobId)
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    Logger::handle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, Logger::handle);

    // lol
    printf("Access key read: \n");
    printf("Current Access key: \n");
    printf("Service starting...\n");
    printf("Intializing Roblox Web Service\n");
    printf("Service Started on port 64989\n");

    Logger::outputLog = std::ofstream(jobId + std::string("-Output.txt"));
    Logger::httpLog = std::ofstream(jobId + std::string("-Http.txt"));
}

void Logger::Log(LogType type, const std::string message)
{
    if (!handle) return;

    switch (type)
    {
    case LogType::Output:
        outputLog << "[" << Logger::UtcTime() << "] " << message.c_str() << std::endl;
        break;
    case LogType::Http:
        httpLog << "[" << Logger::UtcTime() << "] " << message.c_str() << std::endl;
        break;
    }    
}

std::string Logger::UtcTime()
{
    std::stringstream time;
    std::time_t now = std::time(NULL);
    time << std::put_time(std::localtime(&now), "%F %T");
    return time.str();
}