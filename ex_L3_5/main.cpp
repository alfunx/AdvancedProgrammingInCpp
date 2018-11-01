#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include "merger.h"
using namespace std;

void print_help()
{
	cout << "usage: merger [-v | -s | -l]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	for (int i = 1; i < argc; i++) {
		if ("-v" == args[i]) {

			merger<std::vector<int>, int> merge;

			std::vector<int> a = {1, 2, 3};
			std::vector<int> b = {3, 4, 5};

			merge(a, b);
			for (auto e : a)
				std::cout << e << std::endl;

		} else if ("-s" == args[i]) {

			merger<std::set<int>, int> merge;

			std::set<int> a = {1, 2, 3};
			std::set<int> b = {3, 4, 5};

			merge(a, b);
			for (auto e : a)
				std::cout << e << std::endl;

		} else if ("-l" == args[i]) {

			merger<std::list<int>, int> merge;

			std::list<int> a = {1, 2, 3};
			std::list<int> b = {3, 4, 5};

			merge(a, b);
			for (auto e : a)
				std::cout << e << std::endl;

		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	return 0;
}
