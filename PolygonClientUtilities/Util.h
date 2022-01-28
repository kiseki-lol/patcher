#pragma once

#include "pch.h"

class Util
{
public:
    static const std::vector<std::string> allowedHosts;
    static const std::vector<std::string> allowedSchemes;
    static const std::vector<std::string> allowedEmbeddedSchemes;
    static std::vector<std::string> split(std::string s, std::string delimiter);
    static std::map<std::string, std::string> parseArgs(std::string args);
    static bool isASCII(const std::string& s);
};