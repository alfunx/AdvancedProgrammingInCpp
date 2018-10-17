#ifndef RPN_CALCULATOR_H_
#define RPN_CALCULATOR_H_

#include "pvector.h"
#include <iostream>

template<typename T, typename C=pvector<T>>
class rpn_calculator
{

	C stack;

	inline void print_error(std::string s)
	{
		std::cout << "  [Error] " << s << std::endl;
	}

public:

	rpn_calculator() : stack("rpn_stack.txt")
	{
		/* void */
	}

	void push(T t)
	{
		stack.push_back(t);
	}

	T pop()
	{
		T t = stack.back();
		stack.pop_back();
		return t;
	}

	void reset()
	{
		stack.clear();
	}

	void print()
	{
		int c = 0;
		for (T& t : stack) {
			if (1 == t.get_denominator())
				std::cout << c++ << ": " << t.get_counter() << std::endl;
			else
				std::cout << c++ << ": " << t << std::endl;
		}
	}

	void add()
	{
		if (stack.size() < 2)
			return;

		push(pop() + pop());
	}

	void sub()
	{
		if (stack.size() < 2)
			return;

		push(pop() - pop());
	}

	void mul()
	{
		if (stack.size() < 2)
			return;

		push(pop() * pop());
	}

	void div()
	{
		if (stack.size() < 2)
			return;

		if (0 == stack.back().get_counter()) {
			print_error("Division by 0!");
			return;
		}

		push(pop() / pop());
	}

	void min()
	{
		if (stack.size() < 2)
			return;

		push(std::min(pop(), pop()));
	}

	void max()
	{
		if (stack.size() < 2)
			return;

		push(std::max(pop(), pop()));
	}

	void swap()
	{
		if (stack.size() < 2)
			return;

		T i = pop();
		T j = pop();
		push(i);
		push(j);
	}

};

#endif  // RPN_CALCULATOR_H_
