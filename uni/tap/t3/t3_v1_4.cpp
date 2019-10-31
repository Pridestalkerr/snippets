#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

typedef std::pair <long, long> point_t;

long squared_dist(point_t a, point_t b)
{
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

//pair of indexes to the points
std::pair <std::size_t, std::size_t> closest_pair(const std::vector <point_t> &points, std::size_t start, std::size_t end, std::vector <std::pair <std::size_t, long>> &y_sorted) //start, end INCLUSIVE
{
	//base case
	if(end - start == 1)
	{
		return {start, end};
	}
	if(end - start == 2)
	{
		std::pair <std::size_t, std::size_t> min = {start, start + 1};
		if(std::sqrt(squared_dist(points[min.first], points[min.second])) > squared_dist(points[start + 1], points[end]))
			min = {start + 1, end};
		if(std::sqrt(squared_dist(points[min.first], points[min.second])) > squared_dist(points[end], points[start]))
			min = {start, end};
		return min;
	}

	//divide
	//array is already sorted so we can split in the middle and choose the middle points as our vertical line
	long mid = (end + start) / 2; //points[mid] is split point
	auto left = closest_pair(points, start, mid, y_sorted);
	auto right = closest_pair(points, mid + 1, end, y_sorted);

	std::pair <std::size_t, std::size_t> min;
	if(squared_dist(points[left.first], points[left.second]) <= squared_dist(points[right.first], points[right.second]))
		min = left;
	else
		min = right;

	long min_dd = squared_dist(points[min.first], points[min.second]);
	double min_dist = std::sqrt(min_dd);

	long split_point = points[mid].first;

	std::vector <std::pair <point_t, std::size_t>> strip;
	strip.reserve(1000);
	for(auto &itr : y_sorted)
	{
		if((points[itr.first].first <= split_point && points[itr.first].first >= split_point - min_dist) || (points[itr.first].first >= split_point && points[itr.first].first <= split_point + min_dist))
		{
			strip.push_back({points[itr.first], itr.first});
		}
	}

	for(std::size_t itr = 0; itr < strip.size(); ++itr)
	{
		for(std::size_t jtr = itr + 1; jtr < itr + 8 && jtr < strip.size(); ++jtr)
		{
			double dist = squared_dist(strip[itr].first, strip[jtr].first);
			if(dist < min_dd)
			{
				min_dd = dist;
				min = {strip[itr].second, strip[jtr].second};
			}
		}
	}

	return min;
}

int main(int argc, char **argv)
{
	std::ifstream file("cmap.in");

	long n;
	file >> n;

	std::vector <point_t> points;
	std::vector <std::pair <std::size_t, long>> y_sorted; //index towards x and y val

	points.reserve(n);
	for(std::size_t itr = 0; itr < n; ++itr)
	{
		long x, y;
		file >> x >> y;
		points.push_back({x, y});
	}
	std::sort(points.begin(), points.end(), [](point_t a, point_t b){
		if(a.first < b.first)
			return true;
		if(a.first > b.first)
			return false;
		if(a.second < b.second)
			return true;
		return false;
	});

	y_sorted.reserve(n);
	for(std::size_t itr = 0; itr < n; ++itr)
	{
		y_sorted.push_back({itr, points[itr].second});
	}
	std::sort(y_sorted.begin(), y_sorted.end(), [](std::pair <std::size_t, long> a, std::pair <std::size_t, long> b){
		if(a.second < b.second)
			return true;
		return false;
	});

	/*for(auto &itr : points)
		std::cout << itr.first << ' ' << itr.second << std::endl;*/

	auto solution = closest_pair(points, 0, n - 1, y_sorted);

	std::ofstream out("cmap.out");

	//std::cout << points[solution.first].first << ' ' << points[solution.first].second << std::endl << points[solution.second].first << ' ' << points[solution.second].second << std::endl;
	double dd = std::sqrt(squared_dist(points[solution.first], points[solution.second]));
	out <<std::setprecision(15)<< dd;
 
	return 0;
}