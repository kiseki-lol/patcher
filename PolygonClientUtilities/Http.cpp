#include "pch.h"
#include "Http.h"
#include "Util.h"

Http__httpGetPostWinInet_t Http__httpGetPostWinInet = (Http__httpGetPostWinInet_t)ADDRESS_HTTP__HTTPGETPOSTWININET;
Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
	Http _changed = *_this;

	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, _this->url.c_str(), 0);

	if (!result)
	{
		char* path;
		char* host;
		char* query;

		curl_url_get(curl, CURLUPART_PATH, &path, 0);
		curl_url_get(curl, CURLUPART_HOST, &host, 0);
		curl_url_get(curl, CURLUPART_QUERY, &query, 0);

		if (path != NULL && host != NULL && query != NULL)
		{
			std::string _path = std::string(path);
			std::string _host = std::string(host);
			std::string _query = Util::toLower(std::string(query));

			_path.erase(_path.begin());

			if (_host == "roblox.com" || _host == "www.roblox.com")
			{
				if (_path == "asset" || _path == "asset/" || _path == "asset/default.ashx")
				{
					_changed.url = "https://assetdelivery.roblox.com/v1/asset/?" + _query;
				}
			}
		}
	}

	_this = &_changed;

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

		url = *(char**)url;
	}

	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, url, 0);

	if (result != 0)
	{
		return false;
	}

	if (url == std::string("about:blank"))
	{
		return true;
	}

	char* scheme;
	char* host;

	curl_url_get(curl, CURLUPART_SCHEME, &scheme, 0);
	curl_url_get(curl, CURLUPART_HOST, &host, 0);

	if (std::find(Util::allowedSchemes.begin(), Util::allowedSchemes.end(), std::string(scheme)) != Util::allowedSchemes.end())
	{
		return std::find(Util::allowedHosts.begin(), Util::allowedHosts.end(), std::string(host)) != Util::allowedHosts.end();
	}

	if (std::find(Util::allowedEmbeddedSchemes.begin(), Util::allowedEmbeddedSchemes.end(), std::string(scheme)) != Util::allowedEmbeddedSchemes.end())
	{
		return true;
	}

	return false;
}
