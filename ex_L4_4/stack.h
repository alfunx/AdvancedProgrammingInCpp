#ifndef STACK_H_
#define STACK_H_

class stack
{

	int buf[256];
	int sp;

public:

	stack();
	virtual ~stack();
	virtual void push(int i);
	virtual int pop();
	virtual bool empty();
	virtual bool full();

};

#endif  // STACK_H_
