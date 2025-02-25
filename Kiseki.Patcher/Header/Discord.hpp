#ifdef PLAYER

#pragma once

#include <thread>

#include <discord_rpc.h>
#include <discord_register.h>
#include <rapidjson/document.h>

#include "Hooks/CRoblox.hpp"

#include "Globals.hpp"

class Discord {
public:
	static void Initialize(const std::string joinScriptUrl);
	static void Cleanup();
private:
	static void Update();
};

#endif