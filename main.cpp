#include <iostream>
#include <curl/curl.h>

#include "Helpers.h"
#include "Requests.h"

#include "ThreadPool.h"

void send_task()
{
	reqs->send_share();
}

int main()
{
	ThreadPool pool(100);

	for (int i = 0; i < 100000; i++)
	{
		pool.enqueue(&send_task);
	}
}