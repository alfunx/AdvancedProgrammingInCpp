#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "counting_iterator.h"

using namespace std;

void print_help()
{
	cout << "usage: count [-p] [-v] <start> <end>" << endl;
}

template<typename C>
void print(const C& c)
{
	for (auto e : c)
		std::cout << e << std::endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 3) {
		print_help();
		return 1;
	}

	auto end = std::stoi(args.back());
	args.pop_back();
	auto start = std::stoi(args.back());
	args.pop_back();

	for (auto it = ++args.begin(); it < args.end(); ++it) {
		if ("-p" == *it) {

			for_each(counter(start), counter(end), [](int i) {
				std::cout << i <<endl;
			});

		} else if ("-v" == *it) {

			std::vector<int> v(counter(start), counter(end));
			for (auto e : v)
				std::cout << e << std::endl;

		} else if ("-h" == *it) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	return 0;
}
