#pragma once

#include "Classes.h"

// const auto ContentProvider__findLocalFile = (bool(__cdecl*)(const char* url))ADDRESS_CONTENTPROVIDER__ISURL;

typedef bool(__thiscall* ContentProvider__findLocalFile_t)(void* _this, const std::string& url, std::string* filename);
int __fastcall ContentProvider__findLocalFile_hook(void* _this, void*, const std::string& url, std::string* filename);

extern ContentProvider__findLocalFile_t ContentProvider__findLocalFile;