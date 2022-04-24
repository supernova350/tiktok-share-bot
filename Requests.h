#pragma once

#include <iostream>

struct GetRequest
{

};

struct PostRequest
{

};

class Requests
{
private:
	int sent_requests;

	static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
	{
		std::string& text = *static_cast<std::string*>(param);
		size_t totalsize = size * nmemb;
		text.append(static_cast<char*>(buffer), totalsize);
		return totalsize;
	}
public:
	Requests();
	~Requests();
	void send_share();
};

inline std::unique_ptr<Requests> reqs = std::make_unique<Requests>();
