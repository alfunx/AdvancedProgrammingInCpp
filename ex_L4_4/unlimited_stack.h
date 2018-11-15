#ifndef UNLIMITED_STACK_H_
#define UNLIMITED_STACK_H_

#include <vector>

#include "stack.h"

class unlimited_stack : public stack
{

	std::vector<int> buf;

public:

	unlimited_stack();
	virtual ~unlimited_stack();
	virtual void push(int i);
	virtual int pop();
	virtual bool empty();
	virtual bool full();

};

#endif  // UNLIMITED_STACK_H_
