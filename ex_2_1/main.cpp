#include "rpn_calculator.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void static_test()
{
	rpn_calculator rpn;

	cout << ">>> n 1 n 2" << endl;
	rpn.push(1.0);
	rpn.push(2.0);
	rpn.print();

	cout << ">>> +" << endl;
	rpn.add();
	rpn.print();
}

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
		<< "  p           --  print stack" << endl
		<< "  s           --  swap first two [number]s on stack" << endl
		<< "  r           --  reset stack" << endl
		<< "  q           --  quit" << endl << endl
		<< "Example usage: n 3 n 2 n 1 + * n 3 /" << endl << endl;
}

void interactive_test()
{
	cout << "Enter 'q' to quit, enter 'h' for help." << endl << endl;

	rpn_calculator rpn;

	for (;;) {
		string input;

		cout << ">>> ";
		getline(cin, input);
		istringstream iss(input);

		while (iss) {
			double i;
			string s;
			iss >> s;

			if ("n" == s) {
				iss >> i;
				rpn.push(i);
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
			else if ("p" == s)
				rpn.print();
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
	cout << "usage: main [-s]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	for (int i = 1; i < argc; i++) {
		if ("-s" == args[i])
			static_test();
		else if ("-h" == args[i])
			print_help();
	}

	interactive_test();

	return 0;
}