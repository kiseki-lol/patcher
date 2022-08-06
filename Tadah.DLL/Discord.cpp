#include "pch.h"

#include "Discord.h"

#ifndef ARBITERBUILD

std::string username;
int placeId;

void InitializeDiscord()
{
	// Check if Discord should be enabled by checking if the binary is the client as well as if the binary's containing folder contains a ".nodiscord" file
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	std::string path = std::string(buffer);

	if (fs::path(path).stem() != "TadahPlayer")
	{
		return;
	}

	if (fs::exists(fs::path(path).parent_path() / ".nodiscord"))
	{
		return;
	}

	// Get the username and placeId
	CURL* curl = curl_easy_init();
	CURLcode result;
	long response = 0;
	std::string data;

	if (!curl)
	{
		return;
	}

	curl_easy_setopt(curl, CURLOPT_URL, std::string(BASE_URL + std::string("/api/places/information?ticket=") + ticket));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Helpers::write);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

	result = curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

	curl_easy_cleanup(curl);

	if (result != CURLE_OK || response != 200)
	{
		return;
	}

	rapidjson::Document document;
	document.Parse(data.c_str());

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
		CURL* curl = curl_easy_init();
		CURLcode result;
		long response = 0;
		std::string data;

		if (!curl)
		{
			return;
		}

		curl_easy_setopt(curl, CURLOPT_URL, std::string(BASE_URL + std::string("/api/places/information?id=") + std::to_string(placeId)));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Helpers::write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

		result = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

		curl_easy_cleanup(curl);

		if (result != CURLE_OK || response != 200)
		{
			return;
		}

		rapidjson::Document document;
		document.Parse(data.c_str());

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