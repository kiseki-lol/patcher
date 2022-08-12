#pragma once

#include <discord_rpc.h>
#include <discord_register.h>
#include <rapidjson/document.h>

#include "Configuration.h"
#include "Hooks/CRoblox.h"

#ifdef PLAYER

class Discord {
public:
	static void Initialize(const std::string joinScriptUrl);
	static void Cleanup();
private:
	static void Update();
};

#endif