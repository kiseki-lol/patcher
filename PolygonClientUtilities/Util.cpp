#include "pch.h"
#include "Util.h"

// this is ifdef guarded so that the public key cannot easily be replaced
// the std::vector variant is the base64 blob decoded into its byte form (https://cryptii.com/pipes/base64-to-hex)
// for ease of development, the string is retained to easily swap keys
// currently the key is the Project Polygon key

#ifdef _DEBUG

const std::string Util::publicKey =
    "BgIAAACkAABSU0ExAAQAAAEAAQABmKy9m0NxBRoXTuQPZU8BeM"
    "fwBisHcYBy93KSlQB3emeiW/pEMj9YWn2k7JkHiqcjuH+XE5PW"
    "K+q9s8oLQsnXTdTYa2l+1BhypP5jefgq0ZHITTIMBfE7rTI39p"
    "pzs0ayXKINQMIsBzXaJm25v5gP+vlz4cupJPq+jy9De+kcyw==";

#else

const std::vector<BYTE> Util::publicKey = {
    0x06, 0x02, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x52, 0x53, 0x41, 0x31, 0x00, 0x04, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x98, 0xac, 0xbd, 0x9b, 0x43, 0x71, 0x05, 0x1a, 0x17,
    0x4e, 0xe4, 0x0f, 0x65, 0x4f, 0x01, 0x78, 0xc7, 0xf0, 0x06, 0x2b, 0x07, 0x71, 0x80, 0x72,
    0xf7, 0x72, 0x92, 0x95, 0x00, 0x77, 0x7a, 0x67, 0xa2, 0x5b, 0xfa, 0x44, 0x32, 0x3f, 0x58,
    0x5a, 0x7d, 0xa4, 0xec, 0x99, 0x07, 0x8a, 0xa7, 0x23, 0xb8, 0x7f, 0x97, 0x13, 0x93, 0xd6,
    0x2b, 0xea, 0xbd, 0xb3, 0xca, 0x0b, 0x42, 0xc9, 0xd7, 0x4d, 0xd4, 0xd8, 0x6b, 0x69, 0x7e,
    0xd4, 0x18, 0x72, 0xa4, 0xfe, 0x63, 0x79, 0xf8, 0x2a, 0xd1, 0x91, 0xc8, 0x4d, 0x32, 0x0c,
    0x05, 0xf1, 0x3b, 0xad, 0x32, 0x37, 0xf6, 0x9a, 0x73, 0xb3, 0x46, 0xb2, 0x5c, 0xa2, 0x0d, 
    0x40, 0xc2, 0x2c, 0x07, 0x35, 0xda, 0x26, 0x6d, 0xb9, 0xbf, 0x98, 0x0f, 0xfa, 0xf9, 0x73,
    0xe1, 0xcb, 0xa9, 0x24, 0xfa, 0xbe, 0x8f, 0x2f, 0x43, 0x7b, 0xe9, 0x1c, 0xcb
};

#endif

const std::vector<std::string> Util::allowedHosts
{
    "polygon.pizzaboxer.xyz",
    "polygondev.pizzaboxer.xyz",
    "polygonapi.pizzaboxer.xyz",
    "clientsettingsapi.pizzaboxer.xyz",

    "roblox.com",
    "www.roblox.com",
    "api.roblox.com",
    "assetdelivery.roblox.com",
    "assetgame.roblox.com",

    "rbxcdn.com",
    "www.rbxcdn.com",

    "tr.rbxcdn.com",
    "t0.rbxcdn.com",
    "t1.rbxcdn.com",
    "t2.rbxcdn.com",
    "t3.rbxcdn.com",
    "t4.rbxcdn.com",
    "t5.rbxcdn.com",
    "t6.rbxcdn.com",
    "t7.rbxcdn.com",
    "t8.rbxcdn.com",
    "t9.rbxcdn.com",

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

// https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
std::string Util::toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

// https://stackoverflow.com/a/44562527
std::vector<BYTE> Util::base64Decode(const std::string_view data)
{
    // table from '+' to 'z'
    const uint8_t lookup[] = {
        62,  255, 62,  255, 63,  52,  53, 54, 55, 56, 57, 58, 59, 60, 61, 255,
        255, 0,   255, 255, 255, 255, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
        10,  11,  12,  13,  14,  15,  16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
        255, 255, 255, 255, 63,  255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
        36,  37,  38,  39,  40,  41,  42, 43, 44, 45, 46, 47, 48, 49, 50, 51
    };

    static_assert(sizeof(lookup) == 'z' - '+' + 1);

    std::vector<unsigned char> out;
    int val = 0, valb = -8;
    for (uint8_t c : data)
    {
        if (c < '+' || c > 'z')
        {
            break;
        }

        c -= '+';
        if (lookup[c] >= 64)
        {
            break;
        }

        val = (val << 6) + lookup[c];
        valb += 6;

        if (valb >= 0)
        {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    return out;
}

// https://stackoverflow.com/a/28269049
std::map<std::string, std::string> Util::parseQueryString(std::string query)
{
    std::istringstream stream(query);
    std::map<std::string, std::string> parsed;
    std::string pair, key, value;

    while (std::getline(stream, pair, '&')) // split each term
    {
        std::istringstream term(pair);

        if (std::getline(std::getline(term, key, '='), value))
        {
            parsed[key] = value;
        }
    }
    
    return parsed;
}

std::string Util::joinQueryString(std::map<std::string, std::string> query)
{
    std::stringstream stream;
    stream << "?";

    for (auto const& pair : query)
    {
        stream << pair.first << "=" << pair.second << "&";
    }

    std::string result = stream.str();
    result.pop_back(); // remove ending ampersand

    return result;
}