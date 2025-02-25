#include "Helpers.hpp"

const std::vector<BYTE> Helpers::publicKey { PUBLIC_KEY };

const std::vector<std::string> Helpers::allowedWildcardDomains { ALLOWED_WILDCARD_DOMAINS };
const std::vector<std::string> Helpers::allowedDomains { ALLOWED_DOMAINS };
const std::vector<std::string> Helpers::allowedSchemes { ALLOWED_SCHEMES };
const std::vector<std::string> Helpers::allowedEmbeddedSchemes { ALLOWED_EMBEDDED_SCHEMES };

// https://stackoverflow.com/questions/48212992/how-to-find-out-if-there-is-any-non-ascii-character-in-a-string-with-a-file-path
bool Helpers::isASCII(const std::string& s)
{
    return !std::any_of(s.begin(), s.end(), [](char c) {
        return static_cast<unsigned char>(c) > 127;
    });
}

// https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
std::string Helpers::toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

// https://stackoverflow.com/a/44562527
std::vector<BYTE> Helpers::base64Decode(const std::string_view data)
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
std::map<std::string, std::string> Helpers::parseQueryString(const std::string query)
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

std::string Helpers::joinQueryString(const std::map<std::string, std::string> query)
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

// https://stackoverflow.com/a/12097772
std::string Helpers::ws2s(const std::wstring widestring)
{
    std::string string;
    std::transform(widestring.begin(), widestring.end(), std::back_inserter(string), [](wchar_t c) {
        return (char)c;
    });

    return string;
}

size_t Helpers::write(char* contents, size_t size, size_t memory, void* pointer)
{
    ((std::string*)pointer)->append((char*)contents, size * memory);
    return size * memory;
}

std::string Helpers::getModulePath()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    return std::string(buffer);
}

std::string Helpers::getISOTimestamp()
{
    time_t now = time(0);
    struct tm now_gmt {};

    gmtime_s(&now_gmt, &now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%FT%TZ", &now_gmt);

    return std::string(buffer);
}

std::string Helpers::getRedirectURL(const std::string url)
{
    CURL* curl = curl_easy_init();
    CURLcode result;

    if (!curl)
    {
        return url;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);

    result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        return url;
    }

    long response = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

    if (response != 301 && response != 302)
    {
        return url;
    }

    char* redirectURL;
    curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirectURL);

    std::string location = redirectURL ? std::string(redirectURL) : "";

    curl_easy_cleanup(curl);

    if (location.empty())
    {
        return url;
    }

    return location;
}

std::pair<bool, std::map<std::string, std::string>> Helpers::parseURL(const std::string url)
{
    CURLU* curl = curl_url();
    CURLUcode result = curl_url_set(curl, CURLUPART_URL, url.c_str(), 0);

    std::map<std::string, std::string> map;
    bool success = false;

    if (result == CURLE_OK)
    {
        success = true;

        char* scheme;
        char* path;
        char* host;
        char* query;

        curl_url_get(curl, CURLUPART_SCHEME, &scheme, 0);
        curl_url_get(curl, CURLUPART_PATH, &path, 0);
        curl_url_get(curl, CURLUPART_HOST, &host, 0);
        curl_url_get(curl, CURLUPART_QUERY, &query, 0);
        curl_url_cleanup(curl);

        // ugly ternaries to prevent edge-case access violations
        map["scheme"] = scheme ? std::string(scheme) : "";
        map["path"] = path ? std::string(path) : "";
        map["host"] = host ? std::string(host) : "";
        map["query"] = query ? std::string(query) : "";

        curl_free(path);
        curl_free(host);
        curl_free(query);
    }

    return std::make_pair(success, map);
}

std::pair<bool, std::string> Helpers::httpGet(const std::string url)
{
    bool success = false;
    std::string data;

    CURL* curl = curl_easy_init();
    CURLcode result;
    long response = 0;

    if (!curl)
    {
        return std::make_pair(false, "");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Helpers::write);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    result = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK || response != 200)
    {
        return std::make_pair(false, "");
    }

    return std::make_pair(true, data);
}

std::string Helpers::getBaseUrl()
{
    std::string path = Helpers::getModulePath();
    path = path.substr(0, path.find_last_of("\\/"));

    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file((path + "\\AppSettings.xml").c_str());

    if (!result)
    {
        return "";
    }

    pugi::xml_node settings = document.child("Settings");
    pugi::xml_node baseUrl = settings.child("BaseUrl");

    if (!baseUrl)
    {
        return "";
    }

    return baseUrl.child_value();
}