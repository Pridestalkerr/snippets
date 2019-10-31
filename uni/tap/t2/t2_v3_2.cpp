#include <iostream>
#include <fstream>
#include <map>
#include <vector>

std::pair <bool, int> mis(std::vector <std::vector <int>> &list, int node, int parent)
{
	std::pair <bool, int> node_data(1, 0); //choosen, count

	for(auto &edge : list[node])
		if(edge != parent)
		{
			std::pair <bool, int> child_data = mis(list, edge, node);

			if(child_data.first) //child already in set
				node_data.first = false; //remove node from set
			
			node_data.second += child_data.second;
		}

	if(node_data.first)
	{
		std::cout << node << ' ';
		++node_data.second;
	}

	return node_data;
}

int main(int argc, char **argv)
{
	std::ifstream file(argv[1]);

	int node_count, edge_count;
	file >> node_count >> edge_count;

	std::vector <std::vector <int>> list(node_count + 1);

	for(int itr = 0; itr < edge_count; ++itr)
	{
		int parent, child;
		file >> parent >> child;
		list[parent].push_back(child);
		list[child].push_back(parent);
	}

	std::cout << mis(list, 1, 1).second;

	return 0;
}