#include "rpn_calculator.h"
#include <iostream>
#include <string>
#include <vector>

rpn_calculator::rpn_calculator()
{
	/* void */
}

inline void print_error(std::string s)
{
	std::cout << "  [Error] " << s << std::endl;
}

void rpn_calculator::push(double i)
{
	stack.push_back(i);
}

double rpn_calculator::pop()
{
	double i = stack.back();
	stack.pop_back();
	return i;
}

void rpn_calculator::reset()
{
	stack.clear();
}

void rpn_calculator::print()
{
	for (std::vector<double>::iterator it = stack.begin() ; it != stack.end(); ++it) {
		std::cout << it - stack.begin() << ": " << *it << std::endl;;
	}
}

void rpn_calculator::add()
{
	if (stack.size() < 2)
		return;

	push(pop() + pop());
}

void rpn_calculator::sub()
{
	if (stack.size() < 2)
		return;

	push(-pop() + pop());
}

void rpn_calculator::mul()
{
	if (stack.size() < 2)
		return;

	push(pop() * pop());
}

void rpn_calculator::div()
{
	if (stack.size() < 2)
		return;

	if (0.0 == stack.back()) {
		print_error("Division by 0!");
		return;
	}

	push(1 / pop() * pop());
}

void rpn_calculator::min()
{
	if (stack.size() < 2)
		return;

	push(std::min(pop(), pop()));
}

void rpn_calculator::max()
{
	if (stack.size() < 2)
		return;

	push(std::max(pop(), pop()));
}

void rpn_calculator::swap()
{
	if (stack.size() < 2)
		return;

	double i = pop();
	double j = pop();
	push(i);
	push(j);
}
