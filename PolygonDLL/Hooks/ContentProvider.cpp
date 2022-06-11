#include "pch.h"

#include "Util.h"
#include "Hooks/ContentProvider.h"

ContentProvider__findLocalFile_t ContentProvider__findLocalFile = (ContentProvider__findLocalFile_t)ADDRESS_CONTENTPROVIDER__FINDLOCALFILE;

int __fastcall ContentProvider__findLocalFile_hook(void* _this, void*, const std::string& url, std::string* filename)
{
	printf("url: %d\n", url.length());

	ContentProvider__findLocalFile(_this, url, filename);

	return 0;
}