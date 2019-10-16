
//TAP 1ST LAB ASSIGNMENT

#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>
#include <locale>
#include <vector>

class alpha : public std::ctype <char> //everything BUT alpha is whitespace
{
public:
	alpha()
		:
		std::ctype <char>(get_table())
	{};

	static std::ctype_base::mask const* get_table()
	{
		static std::vector <std::ctype_base::mask> rc(std::ctype <char>::table_size, std::ctype_base::space);

		std::fill(&rc['a'], &rc['z'], std::ctype_base::lower);
		std::fill(&rc['A'], &rc['Z'], std::ctype_base::upper);

		return &rc[0];
	};
};

int main(int argc, char **argv)
{
	std::ifstream f1(argv[1]);
	std::ifstream f2(argv[2]);

	f1.imbue(std::locale(std::locale(), new alpha));
	f2.imbue(std::locale(std::locale(), new alpha));

	std::unordered_map <std::string, std::pair <unsigned int, unsigned int>> words; //word and count for f1, f2

	std::string word;

	while(f1 >> word)
		words[word].first++;

	while(f2 >> word)
		words[word].second++;

	unsigned long long prod = 0, sq1 = 0, sq2 = 0;

	for(auto &itr : words)
	{
		prod += itr.second.first * itr.second.second;
		sq1 += itr.second.first * itr.second.first;
		sq2 += itr.second.second * itr.second.second;
	}

	std::cout << double(prod)/(std::sqrt(sq1)*std::sqrt(sq2)) << std::endl;

	return 0;
}
