#ifndef RPN_CALCULATOR_H_
#define RPN_CALCULATOR_H_

#include <complex>
#include <iostream>
#include <string>
#include "comparison_traits.h"
#include "pvector.h"

template<typename T, typename M=comparison_traits<T>, typename C=pvector<T>>
class rpn_calculator
{

	C stack;

	inline void print_error(std::string s)
	{
		std::cout << "  [Error] " << s << std::endl;
	}

public:

	rpn_calculator(std::string& file) : stack(file)
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

		T t = pop();
		push(pop() - t);
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

		// if (0 == (double)stack.back()) {
		// 	print_error("Division by 0!");
		// 	return;
		// }

		T t = pop();
		push(pop() / t);
	}

	void min()
	{
		if (stack.size() < 2)
			return;

		push(M::min(pop(), pop()));
	}

	void max()
	{
		if (stack.size() < 2)
			return;

		push(M::max(pop(), pop()));
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
