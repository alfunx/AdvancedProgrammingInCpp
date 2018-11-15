#include "unlimited_stack.h"

unlimited_stack::unlimited_stack()
{
	/* void */
}

unlimited_stack::~unlimited_stack()
{
	/* void */
}

void unlimited_stack::push(int i)
{
	buf.push_back(i);
}

int unlimited_stack::pop()
{
	auto i = buf.back();
	buf.pop_back();
	return i;
}

bool unlimited_stack::empty()
{
	return buf.size() <= 0;
}

bool unlimited_stack::full()
{
	return false;
}
