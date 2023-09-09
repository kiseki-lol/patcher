#include "Hooks/Http.hpp"

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

            // TODO: This is a weird hack.
            if (url["host"] == "kiseki.lol" || url["host"] == "www.kiseki.lol" || url["host"] == "kiseki.loc" || url["host"] == "www.kiseki.loc")
            {
                if (url["path"] == "/asset" || url["path"] == "/asset/")
                {
                    std::string location = Helpers::getRedirectURL(url["scheme"] + "://" + url["host"] + "/asset?" + url["query"]);
                    _this = &_changed;
                }
            }
            else if (url["host"] == "roblox.com" || url["host"] == "www.roblox.com")
            {
                if (url["path"] == "/game/tools/insertasset.ashx")
                {
                    _changed.url = "https://sets.pizzaboxer.xyz/" + url["path"] + "?" + url["query"];
                    _this = &_changed;
                }
                else if (url["path"] == "/asset" || url["path"] == "/asset/" || url["path"] == "/asset/default.ashx")
                {
                    _changed.url = "https://assetdelivery.roblox.com/v1/asset/?" + url["query"];
                    _this = &_changed;
                }
                else if (url["path"] == "/thumbs/asset.ashx" || url["path"] == "/thumbs/avatar.ashx")
                {
                    std::string api = "https://thumbnails.roblox.com";

                    api += url["path"] == "/thumbs/asset.ashx" ? "/v1/assets" : "/v1/users/avatar";

                    std::map<std::string, std::string> source = Helpers::parseQueryString(url["query"]);
                    std::map<std::string, std::string> fixed = {};

                    for (auto& pair : source)
                    {
                        fixed[Helpers::toLower(pair.first)] = pair.second;
                    }

                    if (fixed.find("id") != fixed.end())
                    {
                        auto handler = fixed.extract("id");
                        handler.key() = url["path"] == "/thumbs/asset.ashx" ? "assetIds" : "userIds";
                        
                        fixed.insert(std::move(handler));
                    }

                    if (fixed.find("x") != fixed.end() && fixed.find("y") != fixed.end())
                    {
                        fixed["size"] = fixed["x"] + "x" + fixed["y"];

                        fixed.erase("x");
                        fixed.erase("y");
                    }

                    if (fixed.find("format") == fixed.end())
                    {
                        fixed["format"] = "Png";
                    }

                    api += Helpers::joinQueryString(fixed);
                    
                    // Get the API response
                    std::pair<bool, std::string> response = Helpers::httpGet(api);
                    if (!response.first)
                    {
                        throw std::runtime_error("Unexpected error occurred when fetching Roblox API: 0");
                    }

                    std::string data = response.second;

                    rapidjson::Document document;
                    document.Parse(data.c_str());

                    int error = 0;

                    CHECK(document.HasParseError(), 1);
                    CHECK(!document.HasMember("data"), 2);
                    CHECK(document["data"].Size() == 0, 3);
                    CHECK(!document["data"][0].HasMember("imageUrl"), 4);
                    CHECK(!document["data"][0]["imageUrl"].IsString(), 5);

                    if (error != 0)
                    {
                        throw std::runtime_error("Unexpected error occurred when fetching Roblox API: " + std::to_string(error));
                    }

                    _changed.url = document["data"][0]["imageUrl"].GetString();
                    _this = &_changed;
                }
            }
        }
    }

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