#include "stack.h"

static const unsigned int size = 256;

stack::stack() : sp(size)
{
	/* void */
}

stack::~stack()
{
	/* void */
}

void stack::push(int i)
{
	buf[--sp] = i;
}

int stack::pop()
{
	return buf[sp++];
}

bool stack::empty()
{
	return sp == size;
}

bool stack::full()
{
	return sp == 0;
}
