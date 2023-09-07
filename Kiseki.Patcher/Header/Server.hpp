#ifdef SERVER

#pragma once

#include <filesystem>
#include <fstream>

#include "Hooks/StandardOut.hpp"

#include "Globals.hpp"
#include "Helpers.hpp"

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
		static void Output(const LogSeverity severity, const std::string message);
	};
private:
	static std::string OutputLogPath;

	static std::ofstream OutputLog;
};

#endif