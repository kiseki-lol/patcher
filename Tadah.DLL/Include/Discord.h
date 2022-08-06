#pragma once

#include <curl/curl.h>
#include <discord_rpc.h>
#include <discord_register.h>
#include <rapidjson/document.h>

#include "Configuration.h"
#include "Hooks/CRoblox.h"

#ifndef ARBITERBUILD

std::thread updater;

void InitializeDiscord();
void UpdatePresence();
void CleanupDiscord();

#endif