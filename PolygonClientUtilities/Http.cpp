#include "pch.h"
#include "Http.h"
#include "Util.h"

#define CHECK(condition, code) \
	if(!error) {               \
		if ((condition)) {     \
			error = code;      \
		}                      \
	}

Http__httpGetPostWinInet_t Http__httpGetPostWinInet = (Http__httpGetPostWinInet_t)ADDRESS_HTTP__HTTPGETPOSTWININET;
Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

size_t write(char* contents, size_t size, size_t memory, void* pointer)
{
	((std::string*)pointer)->append((char*)contents, size * memory);
	return size * memory;
}

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, _this->url.c_str(), 0);

	Http _changed = *_this;

	if (!result)
	{
		char* path;
		char* host;
		char* query;

		curl_url_get(curl, CURLUPART_PATH, &path, 0);
		curl_url_get(curl, CURLUPART_HOST, &host, 0);
		curl_url_get(curl, CURLUPART_QUERY, &query, 0);
		curl_url_cleanup(curl);

		if (path != NULL && host != NULL && query != NULL)
		{
			std::string _path = Util::toLower(std::string(path));
			std::string _host = std::string(host);
			std::string _query = std::string(query);

			if (_host == "roblox.com" || _host == "www.roblox.com")
			{
				if (_path == "/asset" || _path == "/asset/" || _path == "/asset/default.ashx")
				{
					_changed.url = "https://assetdelivery.roblox.com/v1/asset/?" + _query;
					_this = &_changed;
				}
				else if (_path == "/thumbs/asset.ashx" || _path == "/thumbs/avatar.ashx")
				{
					// https://www.roblox.com/asset/request-thumbnail-fix?assetId=1818&assetVersionId=0&width=420&height=420&imageFormat=Png&thumbnailFormatId=296&overrideModeration=false
					// https://www.roblox.com/avatar/request-thumbnail-fix?userId=86890093&width=100&height=100&imageFormat=Png&thumbnailFormatId=41&dummy=false
					// https://www.roblox.com/asset/request-thumbnail-fix for asset.ashx ; needs assetId
					// https://www.roblox.com/avatar/request-thumbnail-fix for avatar.ashx ; needs userId 

					std::string replaceWith = _path == "/thumbs/asset.ashx" ? "assetId" : "userId";
					std::string apiUrl = "https://www.roblox.com/" + std::string(_path == "/thumbs/asset.ashx" ? "asset" : "avatar") + "/request-thumbnail-fix?";

					// parse query stuff here
					std::string query = "";
					apiUrl += query;

					printf("\napiUrl: %s\n", apiUrl.c_str());

					// get the api response
					CURL* curl = curl_easy_init();
					CURLcode result;
					long response = 0;
					std::string data;

					if (!curl)
					{
						throw std::runtime_error("Failed to initialize cURL");
					}

					curl_easy_setopt(curl, CURLOPT_URL, apiUrl);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

					result = curl_easy_perform(curl);
					curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

					curl_easy_cleanup(curl);

					if (result != CURLE_OK || response != 200)
					{
						throw std::runtime_error("Unexpected error occurred when fetching Roblox API: 0x1");
					}

					rapidjson::Document document;
					document.Parse(data.c_str());

					// Ryelow should fucking kill herself
					int error = 0;

					CHECK(document.HasParseError(), 0x02);
					CHECK(!document.HasMember("d"), 0x03);
					CHECK(!document["d"].IsObject(), 0x04);
					CHECK(!document["d"].HasMember("url"), 0x04);
					CHECK(!document["d"]["url"].IsString(), 0x04);

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

	Http__httpGetPostWinInet(_this, isPost, a3, compressData, additionalHeaders, a6);
}

BOOL __fastcall Http__trustCheck_hook(const char* url)
{
	if (strlen(url) == 7 && !Util::isASCII(url))
	{
		// so the client does this really fucking stupid thing where if it opens an ie window,
		// it passes a char**, and not a char*
		// no idea if thats a detours quirk (i doubt it) or if thats how its just actually handled
		// practically no url is ever going to be seven characters long so it doesn't really matter

		url = *(char**)url; // wHOEVER DID THIS FUCKING CAST NEEDS TO GET RAPED BY 10 GORILLION GRIGRGERS
	}

	std::string _url = std::string(url);

	// checking for embedded schemes must come BEFORE checking if it's valid
	// cURL does not treat embedded resources as URLs

	if (_url == "about:blank")
	{
		return true;
	}

	for (std::string allowedEmbeddedScheme : Util::allowedEmbeddedSchemes)
	{
		if (_url.rfind(allowedEmbeddedScheme + ":", 0) == 0)
		{
			return true;
		}
	}

	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, url, 0);

	if (result != CURLE_OK)
	{
		return false;
	}

	char* scheme;
	char* host;

	curl_url_get(curl, CURLUPART_SCHEME, &scheme, 0);
	curl_url_get(curl, CURLUPART_HOST, &host, 0);
	curl_url_cleanup(curl);

	if (std::find(Util::allowedSchemes.begin(), Util::allowedSchemes.end(), std::string(scheme)) != Util::allowedSchemes.end())
	{
		return std::find(Util::allowedHosts.begin(), Util::allowedHosts.end(), std::string(host)) != Util::allowedHosts.end();
	}

	return false;
}