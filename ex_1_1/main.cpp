#include "fraction.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

void static_test()
{
	cout << "Running static tests..." << endl << endl;

	fraction f(5, 9);
	fraction g(3, 7);

	cout << f << " + " << g << " = " << f + g << endl;
	cout << f << " - " << g << " = " << f - g << endl;
	cout << f << " * " << g << " = " << f * g << endl;
	cout << f << " / " << g << " = " << f / g << endl;

	cout << f << " * " << 6 << " = " << f * 6 << endl;
	cout << f << " / " << 3 << " = " << f / 3 << endl;

	cout << f << " == " << g << " = " << (f == g) << endl;
	cout << f << " != " << g << " = " << (f != g) << endl;
	cout << f << " == " << f << " = " << (f == f) << endl;
	cout << f << " < " << g << " = " << (f < g) << endl;
	cout << f << " > " << g << " = " << (f > g) << endl;

	cout << f << " = " << (double)f << endl;
	cout << f << " = " << (float)f << endl;
	cout << f << " = " << (int)f << endl;
}

void interactive_test()
{
	cout << "Send SIGINT to quit." << endl
		<< "Example usage: (1/3) + (2/4)" << endl << endl;

	for (;;) {
		fraction f, g;
		string op;

		cout << ">>> ";
		if (!(cin >> f >> op >> g)) {
			cout << "Bad format!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if ("+" == op)
			cout << f + g << endl;
		else if ("-" == op)
			cout << f - g << endl;
		else if ("*" == op)
			cout << f * g << endl;
		else if ("/" == op)
			cout << f / g << endl;
		else if ("==" == op)
			cout << (f == g) << endl;
		else if ("!=" == op)
			cout << (f != g) << endl;
		else if ("<" == op)
			cout << (f < g) << endl;
		else if (">" == op)
			cout << (f > g) << endl;
		else
			cout << "Unknown operator!" << endl;
		cout << endl;
	}
}

void print_help()
{
	cout << "usage: fraction [-s] [-i]" << endl;
}

int main(int argc, char** argv)
{
	if (argc <= 1) {
		print_help();
		return 1;
	}

	vector<string> args(argv, argv + argc);

	for (int i = 1; i < argc; i++) {
		if ("-s" == args[i])
			static_test();
		else if ("-i" == args[i])
			interactive_test();
		else if ("-h" == args[i])
			print_help();
		else {
			print_help();
			return 1;
		}
	}

	return 0;
}
