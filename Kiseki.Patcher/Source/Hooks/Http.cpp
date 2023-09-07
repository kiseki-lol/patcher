#include "Hooks/Http.hpp"

Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

bool __fastcall Http__trustCheck_hook(const char* url)
{    
    if (strlen(url) == 7 && !Helpers::isASCII(url))
    {
        url = ((char**)url)[0];
    }

    std::string _url = std::string(url);

    if (_url == "about:blank")
    {
        return true;
    }

    for (std::string allowedEmbeddedScheme : Helpers::allowedEmbeddedSchemes)
    {
        if (_url.rfind(allowedEmbeddedScheme + ":", 0) == 0)
        {
            return true;
        }
    }

    std::pair<bool, std::map<std::string, std::string>> result = Helpers::parseURL(url);
    if (!result.first)
    {
        return false;
    }

    std::map<std::string, std::string> parsed = result.second;

    if (!parsed["scheme"].empty() && !parsed["host"].empty())
    {
        if (std::find(Helpers::allowedSchemes.begin(), Helpers::allowedSchemes.end(), std::string(parsed["scheme"])) != Helpers::allowedSchemes.end())
        {
            for (std::string wildcard : Helpers::allowedWildcardDomains)
            {
                if (parsed["host"].length() >= wildcard.length() && parsed["host"].compare(parsed["host"].length() - wildcard.length(), wildcard.length(), wildcard))
                {
                    return true;
                }
            }

            return std::find(Helpers::allowedDomains.begin(), Helpers::allowedDomains.end(), parsed["host"]) != Helpers::allowedDomains.end();
        }
    }

    return true;
}