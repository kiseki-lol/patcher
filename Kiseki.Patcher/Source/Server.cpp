#ifdef SERVER

#include "Server.hpp"

HANDLE Server::Handle;

std::ofstream Server::OutputLog;

std::string Server::OutputLogPath;

void Server::Initialize(const std::wstring jobId)
{
	std::string _jobId = Helpers::ws2s(jobId);
    std::string signature = "Kiseki.Patcher v1.0.0";

#ifdef _DEBUG
    signature += " (compiled as Debug)";
#endif

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    Server::Handle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, Server::Handle);

    printf((signature + "\n\n").c_str());

    // Initialize file logging
    std::filesystem::create_directory(std::filesystem::path(Helpers::getModulePath()).parent_path() / "logs");

    OutputLogPath = (std::filesystem::path(Helpers::getModulePath()).parent_path() / "logs" / (_jobId + "-Output.log")).string();

    OutputLog.open(OutputLogPath, std::ios::out);

    OutputLog << signature << " - StandardOut" << std::endl << std::endl;

    OutputLog.close();
}

void Server::Log::Output(const LogSeverity severity, const std::string message)
{
    std::string type;
    std::string time = Helpers::getISOTimestamp();

    switch (severity)
    {
    case LogSeverity::Output:
        SetConsoleTextAttribute(Server::Handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        type = "out";
        break;
    case LogSeverity::Information:
        SetConsoleTextAttribute(Server::Handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        type = "info";
        break;
    case LogSeverity::Warning:
        SetConsoleTextAttribute(Server::Handle, FOREGROUND_RED | FOREGROUND_GREEN);
        type = "warn";
        break;
    case LogSeverity::Error:
        type = "err";
        SetConsoleTextAttribute(Server::Handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    }

    printf("%s\n", message.c_str());
    SetConsoleTextAttribute(Server::Handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    OutputLog.open(OutputLogPath, std::ios::out);
    OutputLog << "[" << time << "] [" << type << "] " << message << std::endl;
    OutputLog.close();
}

void Server::Cleanup()
{
    CloseHandle(Server::Handle);
    OutputLog.close();
}

#endif