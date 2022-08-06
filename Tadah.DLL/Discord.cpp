#include "pch.h"

#include "Discord.h"

#ifndef SERVER

std::string username;
int placeId;

void InitializeDiscord()
{
	// Check if Discord should be enabled by checking if the binary is the client as well as if the binary's containing folder contains a ".nodiscord" file
	std::string path = Helpers::getModulePath();

	if (fs::path(path).stem() != "TadahPlayer")
	{
		return;
	}

	if (fs::exists(fs::path(path).parent_path() / ".nodiscord"))
	{
		return;
	}

	// Get the username and placeId
	std::pair<bool, std::string> response = Helpers::httpGet(BASE_URL + std::string("/api/places/information?ticket=") + ticket);
	if (!response.first)
	{
		return;
	}

	rapidjson::Document document;
	document.Parse(response.second.c_str());

	if (document.HasParseError() || !document.HasMember("username") || !document.HasMember("placeId"))
	{
		return;
	}

	username = document["username"].GetString();
	placeId = document["placeId"].GetInt();

	UpdatePresence();

	// Run the updater
	std::thread updater(UpdatePresence);
	updater.join();
}

void UpdatePresence()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(60 * 1000));

		std::string title = "";
		int size = 0;
		int max = 0;

		// Get title, size, and max
		std::pair<bool, std::string> response = Helpers::httpGet(BASE_URL + std::string("/api/places/information?id=") + std::to_string(placeId));
		if (!response.first)
		{
			return;
		}

		rapidjson::Document document;
		document.Parse(response.second.c_str());

		if (document.HasParseError() || !document.HasMember("title") || !document.HasMember("size") || !document.HasMember("max"))
		{
			return;
		}

		title = document["title"].GetString();
		size = document["size"].GetInt();
		max = document["max"].GetInt();

		DiscordRichPresence presence;
		memset(&presence, 0, sizeof(presence));
	
		presence.largeImageText = username.c_str();
		presence.largeImageKey = "logo";
		presence.smallImageText = "2011";
		presence.smallImageKey = "2011";

		presence.details = title.c_str();
		presence.state = "In a game";
		presence.partySize = size;
		presence.partyMax = max;
	}
}

void CleanupDiscord()
{
	Discord_Shutdown();
}

#endif