/*

quick explanation: https://infoarena.ro/problema/cmap

*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

typedef std::pair <long long, long long> point_t;

long long squared_dist(point_t a, point_t b)
{
	return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

//xsort = array containing ALL the points, sorted by x
//start = starting index for xsort
//end = last index for xsort (INCLUSIVE)
//y_division = array containing the current subdivion's (start, end) points, sorted by y
long long closest_distance(const std::vector <point_t> &xsort, std::size_t start, std::size_t end, const std::vector <point_t> y_division) //start, end INCLUSIVE
{
	//base case
	if(end - start == 1)
	{
		return squared_dist(xsort[start], xsort[end]);
	}
	if(end - start == 2)
	{
		long long min = squared_dist(xsort[start], xsort[start + 1]);
		if(min > squared_dist(xsort[start + 1], xsort[end]))
			min = squared_dist(xsort[start + 1], xsort[end]);
		if(min > squared_dist(xsort[end], xsort[start]))
			min = squared_dist(xsort[end], xsort[start]);
		return min;
	}

	//divide
	//array is already sorted so we can split in the middle and choose the middle points as our vertical line
	long long mid = (end + start) / 2; //points[mid] is split point

	//generate the 2 y divisions
	std::vector <point_t> left_div;
	std::vector <point_t> right_div;
	for(auto y_point: y_division)
	{
		//choose where to put every point
		//<=mid => left
		//>mid =>right
		if(y_point <= xsort[mid])
			left_div.push_back(y_point);
		else
			right_div.push_back(y_point);
	}

	//recursive call for the 2 divisions
	long long left = closest_distance(xsort, start, mid, left_div);
	long long right = closest_distance(xsort, mid + 1, end, right_div);

	//after returning from the 2 calls, pick the min distance
	long long min;
	if(left <= right)
		min = left;
	else
		min = right;

	double min_dist = std::sqrt(min);

	long long split_point = xsort[mid].first;

	//generate the needed strip
	std::vector<point_t> strip;
	for(auto &point: y_division)
	{
		if((point.first <= split_point && (double)point.first >= (double)split_point - min_dist) || (point.first >= split_point && (double)point.first <= (double)split_point + min_dist))
		{
			strip.push_back(point);
		}
	}

	//items are already sorted parse the points in strip and compute its distance against the following 7 points, store the min value
	for(std::size_t itr = 0; itr < strip.size(); ++itr)
	{
		for(std::size_t jtr = itr + 1; jtr < itr + 8 && jtr < strip.size(); ++jtr)
		{
			long long dist = squared_dist(strip[itr], strip[jtr]);
			if(dist < min)
			{
				min = dist;
			}
		}
	}

	return min;
}

int main(int argc, char **argv)
{
	std::ifstream file("f4");

	long long n;
	file >> n;

	std::vector <point_t> xsort;
	std::vector <point_t> ysort;

	xsort.reserve(n);
	for(std::size_t itr = 0; itr < n; ++itr)
	{
		long long x, y;
		file >> x >> y;
		xsort.push_back({x, y});
	}
	std::sort(xsort.begin(), xsort.end());

	ysort.reserve(n);
	for(std::size_t itr = 0; itr < n; ++itr)
	{
		ysort.push_back(xsort[itr]);
	}
	std::sort(ysort.begin(), ysort.end());

	auto solution = closest_distance(xsort, 0, n - 1, ysort); //use ysort as the first division
	double dd = std::sqrt(solution);

	std::ofstream out("cmap.out");
	out << std::setprecision(15) << dd;

	return 0;
}