#include "pch.h"
#include "Http.h"
#include "Util.h"
#include "LUrlParser.h"

Http__httpGetPostWinInet_t Http__httpGetPostWinInet = (Http__httpGetPostWinInet_t)ADDRESS_HTTP__HTTPGETPOSTWININET;

void __fastcall Http__httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
	LUrlParser::ParseURL parsedUrl = LUrlParser::ParseURL::parseURL(_this->url);
	std::string urlPath = Util::toLower(parsedUrl.path_);
	
	Http _changed = *_this;

	if (parsedUrl.host_ == "roblox.com" || parsedUrl.host_ == "www.roblox.com")
	{
		if (urlPath == "asset" || urlPath == "asset/" || urlPath == "asset/default.ashx")
		{
			_changed.url = "https://assetdelivery.roblox.com/v1/asset/?" + parsedUrl.query_;
		}
	}

	printf("\n");

	_this = &_changed;

	Http__httpGetPostWinInet(_this, isPost, a3, compressData, additionalHeaders, a6);
}