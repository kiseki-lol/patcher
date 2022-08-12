#include "pch.h"

#include "Discord.h"

#ifdef PLAYER

bool isRunning = false;
std::string username;
int placeId;

void Discord::Initialize(const std::string joinScriptUrl)
{
	std::pair<bool, std::map<std::string, std::string>> parsed = Helpers::parseURL(joinScriptUrl);

	if (!parsed.first)
	{
		return;
	}

	if (parsed.second["query"].empty())
	{
		return;
	}

	std::map<std::string, std::string> query = Helpers::parseQueryString(parsed.second["query"]);

	if (query.find("ticket") == query.end())
	{
		return;
	}

	if (query.find("discord") == query.end())
	{
		return;
	}

	if (query["ticket"].empty())
	{
		return;
	}

	if (query["discord"] == "0")
	{
		return;
	}

	// Get the username and placeId
	std::pair<bool, std::string> response = Helpers::httpGet(BASE_URL + std::string("/api/places/information?ticket=" + query["ticket"]));
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

	Discord::Update();

	// Run the updater
	std::thread updater(Discord::Update);
	updater.join();
}

void Discord::Update()
{
	isRunning = true;

	while (isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(60 * 1000));

		std::string title = "";
		int size = 0;
		int max = 0;

		// Get title, size, and max
		std::pair<bool, std::string> response = Helpers::httpGet(BASE_URL + std::string("/api/places/information?id=" + placeId));
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

void Discord::Cleanup()
{
	isRunning = false;
	Discord_Shutdown();
}

#endif