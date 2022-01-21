#pragma once

#include "pch.h"

enum class LogType { Output, Http };

class Logger
{
private:
	static std::ofstream outputLog;
	static std::ofstream httpLog;
public:
	static HANDLE handle;
	static void Initialize(const std::string jobId);
	static void Log(LogType type, const std::string message);
	static std::string UtcTime();
};