#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include <set>

using namespace std;

template<typename A, typename B, typename I>
void merge(A& a, B& b, I i)
{
	std::merge(a.begin(), a.end(), b.begin(), b.end(), i);
}

void print_help()
{
	cout << "usage: merger [-v* | -s* | -l*]" << endl;
}

template<typename C>
void print(const C& c)
{
	for (auto e : c)
		cout << e << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 2) {
		print_help();
		return 1;
	}

	vector<int> v1 = {1, 2, 3};
	set<int>    s1 = {1, 2, 3};
	list<int>   l1 = {1, 2, 3};
	vector<int> v2 = {5, 4, 3, 2};
	set<int>    s2 = {5, 4, 3, 2};
	list<int>   l2 = {5, 4, 3, 2};

	for (int i = 1; i < argc; i++) {
		if ("-vv" == args[i]) {

			vector<int> dst;
			merge(v1, v2, back_inserter(dst));
			print(dst);

		} else if ("-ss" == args[i]) {

			set<int> dst;
			merge(s1, s2, inserter(dst, dst.begin()));
			print(s1);

		} else if ("-ll" == args[i]) {

			list<int> dst;
			merge(l1, l2, back_inserter(dst));
			print(l1);

		} else if ("-vl" == args[i]) {

			vector<int> dst;
			merge(v1, l2, back_inserter(dst));
			print(v1);

		} else if ("-vs" == args[i]) {

			vector<int> dst;
			merge(v1, s2, back_inserter(dst));
			print(v1);

		} else if ("-sl" == args[i]) {

			set<int> dst;
			merge(s1, l2, inserter(dst, dst.begin()));
			print(s1);

		} else if ("-sv" == args[i]) {

			set<int> dst;
			merge(s1, v2, inserter(dst, dst.begin()));
			print(s1);

		} else if ("-lv" == args[i]) {

			list<int> dst;
			merge(l1, v2, back_inserter(dst));
			print(l1);

		} else if ("-ls" == args[i]) {

			list<int> dst;
			merge(l1, s2, back_inserter(dst));
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
