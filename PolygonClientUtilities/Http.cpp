#include "pch.h"
#include "Http.h"
#include "Util.h"

Http__httpGetPostWinInet_t Http__httpGetPostWinInet = (Http__httpGetPostWinInet_t)ADDRESS_HTTP__HTTPGETPOSTWININET;
Http__trustCheck_t Http__trustCheck = (Http__trustCheck_t)ADDRESS_HTTP__TRUSTCHECK;

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, _this->url.c_str(), CURLU_NON_SUPPORT_SCHEME);

	Http _changed = *_this;

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
				else if (_path == "/thumbs/asset.ashx")
				{
					// hmmm
					// https://www.roblox.com/asset/request-thumbnail-fix?assetId=1818&assetVersionId=0&width=420&height=420&imageFormat=Png&thumbnailFormatId=296&overrideModeration=false
					// instead of proxying requests through the webserver, can we fetch this response in the client and parse the json?
					// we can do the same thing for /avatar/request/thumbnail-fix (https://www.roblox.com/avatar/request-thumbnail-fix?userId=86890093&width=100&height=100&imageFormat=Png&thumbnailFormatId=41&dummy=false)

					_changed.url = "http://polygon.pizzaboxer.xyz/Thumbs/Asset.ashx?" + _query + "&roblox=true";
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

		url = *(char**)url;
	}

	printf("Http::trustCheck() %s\n", url);

	CURLU* curl = curl_url();
	CURLUcode result = curl_url_set(curl, CURLUPART_URL, url, 0);

	std::string _url = std::string(url);

	// checking for embedded schemes must come BEFORE checking if it's valid
	// cURL does not treat embedded resources as URLs

	if (_url == "about:blank")
	{
		return true;
	}

	for (std::string allowedEmbeddedScheme : Util::allowedEmbeddedSchemes)
	{
		if (_url.find(allowedEmbeddedScheme + ":") == 0)
		{
			return true;
		}
	}

	if (result != 0)
	{
		return false;
	}

	char* scheme;
	char* host;

	curl_url_get(curl, CURLUPART_SCHEME, &scheme, 0);
	curl_url_get(curl, CURLUPART_HOST, &host, 0);

	if (std::find(Util::allowedSchemes.begin(), Util::allowedSchemes.end(), std::string(scheme)) != Util::allowedSchemes.end())
	{
		return std::find(Util::allowedHosts.begin(), Util::allowedHosts.end(), std::string(host)) != Util::allowedHosts.end();
	}

	return false;
}
