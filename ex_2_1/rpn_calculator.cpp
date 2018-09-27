#include "fraction.h"
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

void rpn_calculator::push(fraction f)
{
	stack.push_back(f);
}

fraction rpn_calculator::pop()
{
	fraction f = stack.back();
	stack.pop_back();
	return f;
}

void rpn_calculator::reset()
{
	stack.clear();
}

void rpn_calculator::print()
{
	for (std::vector<fraction>::iterator it = stack.begin() ; it != stack.end(); ++it) {
		if (1 == (*it).get_denominator())
			std::cout << it - stack.begin() << ": " << (*it).get_counter() << std::endl;
		else
			std::cout << it - stack.begin() << ": " << *it << std::endl;
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

	push(pop() - pop());
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

	if (0 == stack.back().get_counter()) {
		print_error("Division by 0!");
		return;
	}

	push(pop() / pop());
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

	fraction f = pop();
	fraction g = pop();
	push(f);
	push(g);
}
