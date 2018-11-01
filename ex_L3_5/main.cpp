#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <set>
#include "merger.h"
using namespace std;

void print_help()
{
	cout << "usage: merger [-v* | -s* | -l*]" << endl;
}

template<typename C>
void print(C c)
{
	for (auto e : c)
		std::cout << e << std::endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	std::vector<int> v1 = {1, 2, 3};
	std::set<int>    s1 = {1, 2, 3};
	std::list<int>   l1 = {1, 2, 3};
	std::vector<int> v2 = {2, 3, 4, 5};
	std::set<int>    s2 = {2, 3, 4, 5};
	std::list<int>   l2 = {2, 3, 4, 5};

	for (int i = 1; i < argc; i++) {
		if ("-vv" == args[i]) {

			merger<std::vector<int>, std::vector<int>, int> merge;
			merge(v1, v2);
			print(v1);

		} else if ("-ss" == args[i]) {

			merger<std::set<int>, std::set<int>, int> merge;
			merge(s1, s2);
			print(s1);

		} else if ("-ll" == args[i]) {

			merger<std::list<int>, std::list<int>, int> merge;
			merge(l1, l2);
			print(l1);

		} else if ("-vl" == args[i]) {

			merger<std::vector<int>, std::list<int>, int> merge;
			merge(v1, l2);
			print(v1);

		} else if ("-vs" == args[i]) {

			merger<std::vector<int>, std::set<int>, int> merge;
			merge(v1, s2);
			print(v1);

		} else if ("-sl" == args[i]) {

			merger<std::set<int>, std::list<int>, int> merge;
			merge(s1, l2);
			print(s1);

		} else if ("-sv" == args[i]) {

			merger<std::set<int>, std::vector<int>, int> merge;
			merge(s1, v2);
			print(s1);

		} else if ("-lv" == args[i]) {

			merger<std::list<int>, std::vector<int>, int> merge;
			merge(l1, v2);
			print(l1);

		} else if ("-ls" == args[i]) {

			merger<std::list<int>, std::set<int>, int> merge;
			merge(l1, s2);
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
