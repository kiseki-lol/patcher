#pragma once

#include "pch.h"
#include <string_view>

class Util
{
public:
#ifdef _DEBUG
    static const std::string publicKey;
#else
    static const std::vector<BYTE> publicKey;
#endif
    static const std::vector<std::string> allowedHosts;
    static const std::vector<std::string> allowedSchemes;
    static const std::vector<std::string> allowedEmbeddedSchemes;
    static std::map<std::string, std::string> parseArgs(std::string args);
    static bool isASCII(const std::string& s);
    static std::string toLower(std::string s);
    static std::vector<BYTE> base64Decode(const std::string_view data);
    static std::map<std::string, std::string> parseQueryString(std::string query);
    static std::string joinQueryString(std::map<std::string, std::string> query);
};