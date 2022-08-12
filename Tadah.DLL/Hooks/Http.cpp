#include "pch.h"

#include "Hooks/Http.h"

#define CHECK(condition, code) \
    if(!error) {               \
        if ((condition)) {     \
            error = code;      \
        }                      \
    }

Http__httpGetPostWinInet_t Http__httpGetPostWinInet = (Http__httpGetPostWinInet_t)ADDRESS_HTTP__HTTPGETPOSTWININET;
Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
    std::pair<bool, std::map<std::string, std::string>> parsed = Helpers::parseURL(_this->url);
    Http _changed = *_this;

    if (parsed.first)
    {
        std::map<std::string, std::string> url = parsed.second;

        if (!url["path"].empty() && !url["host"].empty() && !url["query"].empty())
        {
            url["path"] = Helpers::toLower(url["path"]);

            if (url["host"] == "roblox.com" || url["host"] == "www.roblox.com")
            {
                if (url["path"] == "/asset" || url["path"] == "/asset/" || url["path"] == "/asset/default.ashx")
                {
                    _changed.url = "https://assetdelivery.roblox.com/v1/asset/?" + url["query"];
                    _this = &_changed;
                }
                else if (url["path"] == "/thumbs/asset.ashx" || url["path"] == "/thumbs/avatar.ashx")
                {
                    std::string api = "https://www.roblox.com/" + std::string(url["path"] == "/thumbs/asset.ashx" ? "asset" : "avatar") + "/request-thumbnail-fix";

                    std::map<std::string, std::string> source = Helpers::parseQueryString(url["query"]);
                    std::map<std::string, std::string> fixed = {
                        { url["path"] == "/thumbs/asset.ashx" ? "overrideModeration" : "dummy", "false" },
                        { "thumbnailFormatId", "0" }
                    };

                    for (auto& pair : source)
                    {
                        fixed[Helpers::toLower(pair.first)] = pair.second;
                    }

                    if (fixed.find("id") != fixed.end())
                    {
                        auto handler = fixed.extract("id");
                        handler.key() = url["path"] == "/thumbs/asset.ashx" ? "assetId" : "userId";
                        
                        fixed.insert(std::move(handler));
                    }

                    api += Helpers::joinQueryString(fixed);
                    
                    // Get the API response
                    std::pair<bool, std::string> response = Helpers::httpGet(api);
                    if (!response.first)
                    {
                        throw std::runtime_error("Unexpected error occurred when fetching Roblox API: 0x0");
                    }

                    std::string data = response.second;

                    rapidjson::Document document;
                    document.Parse(data.c_str());

                    int error = 0;

                    CHECK(document.HasParseError(), 0x01);
                    CHECK(!document.HasMember("d"), 0x02);
                    CHECK(!document["d"].IsObject(), 0x03);
                    CHECK(!document["d"].HasMember("url"), 0x04);
                    CHECK(!document["d"]["url"].IsString(), 0x05);

                    if (error != 0)
                    {
                        throw std::runtime_error("Unexpected error occurred when fetching Roblox API: 0x0" + std::to_string(error));
                    }

                    _changed.url = document["d"]["url"].GetString();
                    _this = &_changed;
                }
            }
        }
    }

#ifdef SERVER
    if (Server::Handle)
    {
        Server::Log::Http((RequestType)isPost, _this->url);
    }
#endif

    Http__httpGetPostWinInet(_this, isPost, a3, compressData, additionalHeaders, a6);
}

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
                if (parsed["host"].size() >= wildcard.size() && 0 == wildcard.compare(parsed["host"].size() - wildcard.size(), wildcard.size(), wildcard))
                {
                    return true;
                }
            }

            return std::find(Helpers::allowedDomains.begin(), Helpers::allowedDomains.end(), parsed["host"]) != Helpers::allowedDomains.end();
        }
    }

    return false;
}