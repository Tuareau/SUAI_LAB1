#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#include "AbstractQueue.h"
#include "StackElement.h"

class Stack : public AbstractQueue
{
private:
	StackElement * _top;

public:
	Stack();
	Stack(const AbstractQueue & qu);
	Stack(AbstractQueue && qu) noexcept;
	~Stack();

	Stack & operator=(const Stack & other);
	Stack & operator=(Stack && other);

	StackElement * top() const;

	void push(const StackElement & el);
	StackElement pop();
};

#endif
