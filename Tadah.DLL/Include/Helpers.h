#pragma once

#include "Configuration.h"

class Helpers
{
public:
    static const std::vector<BYTE> publicKey;
    static const std::vector<std::string> allowedWildcardDomains;
    static const std::vector<std::string> allowedDomains;
    static const std::vector<std::string> allowedSchemes;
    static const std::vector<std::string> allowedEmbeddedSchemes;
    static bool isASCII(const std::string& s);
    static std::string toLower(std::string s);
    static std::vector<BYTE> base64Decode(const std::string_view data);
    static std::map<std::string, std::string> parseQueryString(std::string query);
    static std::string joinQueryString(std::map<std::string, std::string> query);
    static std::string ws2s(std::wstring widestring);
    static size_t write(char* contents, size_t size, size_t memory, void* pointer);
};