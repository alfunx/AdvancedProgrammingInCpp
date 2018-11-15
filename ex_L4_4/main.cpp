#include <iostream>
#include <vector>

#include "stack.h"
#include "unlimited_stack.h"

using namespace std;

void copy_stack_pop(stack s)
{
	cout << s.pop() << endl;
}

void ref_stack_pop(stack& s)
{
	cout << s.pop() << endl;
}

void ptr_stack_pop(stack* s)
{
	cout << s->pop() << endl;
}

void print_help()
{
	cout << "usage: stack [-c] [-r] [-p]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 2) {
		print_help();
		return 1;
	}

	vector<stack*> vector_of_stacks;
	stack s1;
	unlimited_stack s2;

	for (int i = 0; i < 100; ++i) {
		s1.push(i);
		s2.push(i);
	}

	for (int i = 1; i < argc; i++) {
		if ("-c" == args[i]) {

			copy_stack_pop(s1);
			copy_stack_pop(s2);

		} else if ("-r" == args[i]) {

			ref_stack_pop(s1);
			ref_stack_pop(s2);

		} else if ("-p" == args[i]) {

			ptr_stack_pop(&s1);
			ptr_stack_pop(&s2);

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
