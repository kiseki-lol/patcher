#include "pch.h"

#include "Server.h"

#ifdef SERVER

HANDLE Server::Handle;

std::ofstream Server::OutputLog;
std::ofstream Server::HttpLog;

std::string Server::OutputLogPath;
std::string Server::HttpLogPath;

void Server::Initialize(const std::wstring jobId)
{
	std::string _jobId = Helpers::ws2s(jobId);
    std::string signature = "Tadah.DLL v1.0.0";

#ifdef _DEBUG
    signature += " (compiled as Debug)";
#endif

    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    Server::Handle = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, Server::Handle);

    printf((signature + "\n\n").c_str());

    // Initialize file logging
    fs::create_directory(fs::path(Helpers::getModulePath()).parent_path() / "logs");

    OutputLogPath = (fs::path(Helpers::getModulePath()).parent_path() / "logs" / (_jobId + "-Output.log")).string();
    HttpLogPath = (fs::path(Helpers::getModulePath()).parent_path() / "logs" / (_jobId + "-Http.log")).string();

    OutputLog.open(OutputLogPath, std::ios::out);
    HttpLog.open(HttpLogPath, std::ios::out);

    OutputLog << signature << " - StandardOut" << std::endl << std::endl;
    HttpLog << signature << " - Http" << std::endl << std::endl;

    OutputLog.close();
    HttpLog.close();
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

void Server::Log::Http(const RequestType request, const std::string url)
{
    std::string type;
    std::string time = Helpers::getISOTimestamp();

    type = (request == RequestType::GET ? "GET" : "POST");

    HttpLog.open(HttpLogPath, std::ios::out);
    HttpLog << "[" << time << "] [" << type << "] " << "'" << url << "'" << std::endl;
    HttpLog.close();
}

void Server::Cleanup()
{
    CloseHandle(Server::Handle);
    OutputLog.close();
    HttpLog.close();
}

#endif