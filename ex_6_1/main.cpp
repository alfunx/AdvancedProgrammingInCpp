#include "fraction.h"
#include "rpn_calculator.h"
#include <sstream>
#include <string>
#include <vector>
using namespace std;

inline void interactive_help()
{
	cout << endl
		<< "Following commands can be used:" << endl << endl
		<< "  n [number]  --  push [number] on stack" << endl
		<< "  +           --  perform operation on first two [number]s on stack" << endl
		<< "  -           --  perform operation on first two [number]s on stack" << endl
		<< "  *           --  perform operation on first two [number]s on stack" << endl
		<< "  /           --  perform operation on first two [number]s on stack" << endl
		<< "  min         --  perform operation on first two [number]s on stack" << endl
		<< "  max         --  perform operation on first two [number]s on stack" << endl
		<< "  d           --  delete first [number] on stack" << endl
		<< "  s           --  swap first two [number]s on stack" << endl
		<< "  r           --  reset stack" << endl
		<< "  q           --  quit" << endl << endl
		<< "Hint: You can use fractions as [number]s!" << endl << endl
		<< "Example usage: n 3 n 2 n 1 + * n 3 /" << endl << endl;
}

template<typename T>
void interactive_mode(rpn_calculator<T>& rpn)
{
	cout << "Enter 'q' to quit, enter 'h' for help." << endl << endl;
	rpn.print();

	for (;;) {
		string input;

		cout << endl << ">>> ";
		getline(cin, input);
		istringstream iss(input);

		while (iss) {
			fraction f;
			string s;
			iss >> s;

			if ("n" == s) {
				iss >> f;
				rpn.push(f);
			} else if ("+" == s)
				rpn.add();
			else if ("-" == s)
				rpn.sub();
			else if ("*" == s)
				rpn.mul();
			else if ("/" == s)
				rpn.div();
			else if ("min" == s)
				rpn.min();
			else if ("max" == s)
				rpn.max();
			else if ("d" == s)
				rpn.pop();
			else if ("s" == s)
				rpn.swap();
			else if ("r" == s)
				rpn.reset();
			else if ("h" == s)
				interactive_help();
			else if ("q" == s)
				return;
		}

		rpn.print();
	}
}

void print_help()
{
	cout << "usage: rpn [-d | -f] <persistence-file>" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	bool _double = false;
	bool _fraction = true;

	for (int i = 1; i < argc - 1; i++) {
		if ("-d" == args[i]) {
			_double = true;
			_fraction = false;
		} else if ("-f" == args[i]) {
			_double = false;
			_fraction = true;
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	if (argc < 2) {
		print_help();
		return 1;
	}
	string file = args[argc - 1];

	if (_double) {
		rpn_calculator<double> rpn(file);
		interactive_mode(rpn);
	} else if (_fraction) {
		rpn_calculator<fraction> rpn(file);
		interactive_mode(rpn);
	}

	return 0;
}
