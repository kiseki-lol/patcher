#include "pch.h"
#include "TrustCheck.h"
#include "Util.h"
#include "LUrlParser.h"

Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

BOOL __fastcall Http__trustCheck_hook(const char* url)
{
    if (strlen(url) == 7 && !Util::isASCII(url))
    {
        // so the client does this really fucking stupid thing where if it opens an ie window,
        // it passes a char**, and not a char*
        // no idea if thats a detours quirk (i doubt it) or if thats how its just actually handled
        // practically no url is ever going to be seven characters long so it doesn't really matter

        url = *(char**)url;
    }

    LUrlParser::ParseURL parsedUrl = LUrlParser::ParseURL::parseURL(url);

    if (!parsedUrl.isValid())
        return false;

    if (std::string("about:blank") == url)
        return true;

    if (std::find(Util::allowedSchemes.begin(), Util::allowedSchemes.end(), parsedUrl.scheme_) != Util::allowedSchemes.end())
        return std::find(Util::allowedHosts.begin(), Util::allowedHosts.end(), parsedUrl.host_) != Util::allowedHosts.end();

    if (std::find(Util::allowedEmbeddedSchemes.begin(), Util::allowedEmbeddedSchemes.end(), parsedUrl.scheme_) != Util::allowedEmbeddedSchemes.end())
        return true;

    return false;
}
