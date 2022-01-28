#include "pch.h"
#include "Util.h"

const std::vector<std::string> Util::allowedHosts
{
    "polygon.pizzaboxer.xyz",
    "polygondev.pizzaboxer.xyz",
    "polygonapi.pizzaboxer.xyz",
    "clientsettingsapi.pizzaboxer.xyz",

    "roblox.com",
    "www.roblox.com",
    "assetdelivery.roblox.com",

    "tadah.rocks",
    "www.tadah.rocks"
};

const std::vector<std::string> Util::allowedSchemes
{
    "http",
    "https",
    "ftp"
};

const std::vector<std::string> Util::allowedEmbeddedSchemes
{
    "javascript",
    "jscript",
    "res"
};

std::map<std::string, std::string> Util::parseArgs(std::string args)
{
    std::map<std::string, std::string> map;

    std::string::size_type key_pos = 0;
    std::string::size_type key_end;
    std::string::size_type val_pos;
    std::string::size_type val_end;

    while ((key_end = args.find(' ', key_pos)) != std::string::npos)
    {
        if ((val_pos = args.find_first_not_of(" -", key_end)) == std::string::npos)
            break;

        val_end = args.find(" -", val_pos);
        map.emplace(args.substr(key_pos, key_end - key_pos), args.substr(val_pos, val_end - val_pos));

        key_pos = val_end;
        if (key_pos != std::string::npos)
            ++key_pos;
    }

    return map;
}

// https://stackoverflow.com/questions/48212992/how-to-find-out-if-there-is-any-non-ascii-character-in-a-string-with-a-file-path
bool Util::isASCII(const std::string& s)
{
    return !std::any_of(s.begin(), s.end(), [](char c) {
        return static_cast<unsigned char>(c) > 127;
    });
}