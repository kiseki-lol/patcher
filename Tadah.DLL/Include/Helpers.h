#pragma once

#include <curl/curl.h>

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
    static std::map<std::string, std::string> parseQueryString(const std::string query);
    static std::string joinQueryString(const std::map<std::string, std::string> query);
    static std::string ws2s(const std::wstring widestring);
    static size_t write(char* contents, size_t size, size_t memory, void* pointer);
    static std::string getModulePath();
    static std::string getISOTimestamp();
    static std::pair<bool, std::map<std::string, std::string>> parseURL(const std::string url);
    static std::pair<bool, std::string> httpGet(const std::string url);
};