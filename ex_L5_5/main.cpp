#include <iostream>
#include <vector>
#include "binop.h"

using namespace std;

void print_help()
{
	cout << "usage: meta" << endl;
}

struct is_less_than_5 : std::unary_function<int, bool>
{
	    bool operator ()(int i) const { return i < 5; }
};

struct is_even : std::unary_function<int, bool>
{
	    bool operator ()(int i) const { return i % 2 == 0; }
};

struct is_both : std::binary_function<bool, bool, bool>
{
	    bool operator ()(bool i, bool j) const { return i && j; }
};

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 1) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		if ("-o" == args[i]) {
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	auto op = some_function(is_both(), is_less_than_5(), is_even());

	for (int x = 0; x < 10; ++x)
		cout << x << ": " << op(x) << endl;

	return 0;
}
