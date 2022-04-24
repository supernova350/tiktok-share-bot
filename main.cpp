#include <iostream>
#include <curl/curl.h>

#include "Helpers.h"
#include "Requests.h"

#include "ThreadPool.h"

void send_task()
{
	reqs->send_req();
}

void display_task()
{
	while (true)
	{
		std::cout << reqs->get_sent() * 60 << std::endl;
		Sleep(60 * 1000);
	}
}

int main()
{
	ThreadPool pool(1000);
	pool.enqueue(&display_task);

	for (int i = 0; i < 100000; i++)
	{
		pool.enqueue(&send_task);
	}
}