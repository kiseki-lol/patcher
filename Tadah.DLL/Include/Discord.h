#pragma once

#include <curl/curl.h>
#include <discord_rpc.h>
#include <discord_register.h>
#include <rapidjson/document.h>

#include "Configuration.h"
#include "Hooks/CRoblox.h"

#ifndef SERVER

class Discord {
public:
	static void Initialize(std::string joinScriptUrl);
	static void Cleanup();
private:
	static void Update();
};

#endif