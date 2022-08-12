#pragma once

#include "Configuration.h"
#include "Helpers.h"

#include "Hooks/StandardOut.h"

#ifdef SERVER

enum class RequestType {
	POST,
	GET
};

enum class LogSeverity {
	Information = RBX__MESSAGE_INFO,
	Output = RBX__MESSAGE_OUTPUT,
	Warning = RBX__MESSAGE_WARNING,
	Error = RBX__MESSAGE_ERROR
};

class Server {
public:
	static HANDLE Handle;

	static void Initialize(const std::wstring jobId);
	static void Cleanup();

	struct Log
	{
		static void Http(const RequestType type, const std::string message);
		static void Output(const LogSeverity severity, const std::string message);
	};
private:
	static std::string HttpLogPath;
	static std::string OutputLogPath;

	static std::ofstream HttpLog;
	static std::ofstream OutputLog;
};

#endif