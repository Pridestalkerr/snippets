#include <set>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

int main(int argc, char **argv)
{
	std::ifstream file(argv[1]);

	int n;
	file >> n;

	std::vector <std::pair <int, int>> jobs(n); //start finish
	for(std::size_t itr = 0; itr < n; ++itr)
	{
		int start, finish;
		file >> start >> finish;
		jobs[itr] = {start, finish};
	}

	std::sort(jobs.begin(), jobs.end(), [](std::pair <int, int> left, std::pair <int, int> right) {
		if(left.first < right.first)
			return true;
		if(left.first > right.first)
			return false;

		if(left.second < right.second)
			return true;
		if(left.second > right.second)
			return false;

		return false;
	});

	/*for(auto itr : jobs)
		std::cout << itr.first;*/

	std::multimap <int, int> queue; //current room end time, room index
	std::vector <std::vector <std::pair <int,int>>> rooms;

	for(auto &itr : jobs)
	{
		auto match = queue.upper_bound(itr.first);
		if(match == queue.begin() || !queue.size())
		{
			rooms.push_back(std::vector <std::pair <int, int>>(1, itr));
			queue.insert({itr.second, rooms.size() - 1});
		}
		else
		{
			--match;
			rooms[match->second].push_back(itr);
			auto nh = queue.extract(match);
			nh.key() = itr.second;
			queue.insert(std::move(nh));
		}
	}

	for(auto &itr : rooms)
	{
		for(auto &jtr : itr)
			std::cout << jtr.first << ' ' << jtr.second << '\t';
		std::cout << std::endl;
	}

	return 0;
}