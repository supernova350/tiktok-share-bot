#include "Requests.h"

#include "Helpers.h"
#include "Constants.h"
#include <curl/curl.h>
#include <format>
#include <string>

Requests::Requests()
{
	sent_requests = 0;
	curl_global_init(CURL_GLOBAL_ALL);
}

Requests::~Requests()
{
	curl_global_cleanup();
}

void Requests::send_share()
{
	std::string api_domain = Helpers::random_choice(Constants::API_DOMAINS);
	std::string platform = Helpers::random_choice(Constants::PLATFORMS);
	std::string device_type = Helpers::random_choice(Constants::DEVICE_TYPES);
	std::string app_name = Helpers::random_choice(Constants::APP_NAMES);
	std::string channel = Helpers::random_choice(Constants::CHANNELS);

	std::string os_version = std::to_string(Helpers::random_int(1, 12));
	std::string device_id = {};
	for (size_t i = 0; i < 19; i++)
	{
		device_id.append(std::to_string(Helpers::random_int(0, 9)));
	}

	std::string useragent = Helpers::random_choice(Constants::USERAGENTS);

	std::string url = std::format("https://{}/aweme/v1/aweme/stats/?channel={}&device_type={}&device_id={}&os_version={}&version_code=220400&app_name={}&device_platform={}&aid=1988", api_domain, channel, device_type, device_id, os_version, app_name, platform);
	std::string postfields = std::format("item_id={}&share_delta=1", "7087365331995462955");

	CURL* curl = curl_easy_init();

	if (curl) 
	{
		std::string res_str;

		curl_slist* headers = nullptr;
		curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
		curl_slist_append(headers, useragent.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_str);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);

		if (res_str.find(R"("status_code":0)") != std::string::npos)
		{
			sent_requests++;
		}
	}
}