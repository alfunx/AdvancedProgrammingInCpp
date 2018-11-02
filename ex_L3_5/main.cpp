#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include "merger.h"

using namespace std;
using namespace merger;

void print_help()
{
	cout << "usage: merger [-v* | -s* | -l*]" << endl;
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

	if (argc < 2) {
		print_help();
		return 1;
	}

	std::vector<int> v1 = {1, 2, 3};
	std::set<int>    s1 = {1, 2, 3};
	std::list<int>   l1 = {1, 2, 3};
	std::vector<int> v2 = {5, 4, 3, 2};
	std::set<int>    s2 = {5, 4, 3, 2};
	std::list<int>   l2 = {5, 4, 3, 2};

	for (int i = 1; i < argc; i++) {
		if ("-vv" == args[i]) {

			merge<int>(v1, v2);
			print(v1);

		} else if ("-ss" == args[i]) {

			merge<int>(s1, s2);
			print(s1);

		} else if ("-ll" == args[i]) {

			merge<int>(l1, l2);
			print(l1);

		} else if ("-vl" == args[i]) {

			merge<int>(v1, l2);
			print(v1);

		} else if ("-vs" == args[i]) {

			merge<int>(v1, s2);
			print(v1);

		} else if ("-sl" == args[i]) {

			merge<int>(s1, l2);
			print(s1);

		} else if ("-sv" == args[i]) {

			merge<int>(s1, v2);
			print(s1);

		} else if ("-lv" == args[i]) {

			merge<int>(l1, v2);
			print(l1);

		} else if ("-ls" == args[i]) {

			merge<int>(l1, s2);
			print(l1);

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
