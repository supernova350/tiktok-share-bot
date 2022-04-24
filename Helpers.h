#pragma once

#include <random>
#include <vector>

class Helpers
{
private:
public:
	static long long random_long(long long low, long long high)
	{
		static std::random_device rnd_dev;
		static std::mt19937 rnd_eng(rnd_dev());

		const std::uniform_int_distribution dist(low, high);

		return dist(rnd_eng);
	}

	static std::string random_choice(std::vector<std::string> items)
	{
		size_t idx = Helpers::random_long(0, items.size() - 1);
		return items[idx];
	}
};