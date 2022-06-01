#include "pch.h"
#include "TestHttpGetPost.h"
#include "Util.h"
#include "LUrlParser.h"

Http_httpGetPostWinInet_t Http_httpGetPostWinInet = (Http_httpGetPostWinInet_t)ADDRESS_HTTP_HTTPGETPOSTWININET;

void __fastcall Http_httpGetPostWinInet_hook(Http* _this, void*, bool isPost, int a3, bool compressData, LPCSTR additionalHeaders, int a6)
{
	printf("Http::httpGetPostWinInet called\n");
	// printf("Value of isPost: %d\n", isPost);
	// printf("Value of compressData: %d\n", compressData);
	// printf("Value of additionalHeaders: %s\n", additionalHeaders);
	// throw std::runtime_error("Jay coleman detected");

	/* printf("Length of url: %d\n", *(int*)((int)_this + 60));
	printf("Length of url 2: %d\n", _this->url.size());
	printf("Length of alternateUrl: %d\n", _this->alternateUrl.size());

	printf("\n");

	printf("Location of _this+20: %08X\n", (int)_this);
	printf("Location of _this->alternateUrl: %p\n", &_this->alternateUrl);

	printf("\n");

	printf("Location of _this+40: %08X\n", (int)_this + 40);
	printf("Location of _this->url: %p\n", &_this->url); */

	printf("Requested url: %s\n", _this->url.c_str());

	LUrlParser::ParseURL parsedUrl = LUrlParser::ParseURL::parseURL(_this->url);
	std::string urlPath = Util::toLower(parsedUrl.path_);
	
	if (parsedUrl.host_ == "roblox.com" || parsedUrl.host_ == "www.roblox.com")
	{
		if (urlPath == "asset" || urlPath == "asset/" || urlPath == "asset/default.ashx")
		{
			std::string assetUrl = "https://assetdelivery.roblox.com/v1/asset/?" + parsedUrl.query_;
			printf("Should swap URL with: %s\n", assetUrl.c_str());

			std::string test = assetUrl;
			_this->url = test;
		}
	}

	printf("\n");

	Http_httpGetPostWinInet(_this, isPost, a3, compressData, additionalHeaders, a6);
}