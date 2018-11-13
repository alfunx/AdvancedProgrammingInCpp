#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "counting_iterator.h"

using namespace std;

void print_help()
{
	cout << "usage: count [-d]" << endl;
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

	if (argc < 1) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc - 1; i++) {
		if ("-d" == args[i]) {
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	// vector with elements [10, 20)
	std::cout << "vector:" << std::endl;
	std::vector<int> v(counter(10), counter(20));
	for (auto e : v)
		std::cout << e << std::endl;

	// print [20, 30)
	std::cout << "print:" << std::endl;
	for_each(counter(20), counter(30), [](int i){std::cout << i <<endl;});

	return 0;
}
