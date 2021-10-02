#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#include "AbstractQueue.h"
#include "StackElement.h"

#include <stdexcept>

class Stack : public AbstractQueue
{
private:
	StackElement * _top;

	void clear();
	void copy(const Stack & other);

public:
	Stack();
	Stack(const Stack & other);
	Stack(Stack && other) noexcept;
	~Stack();

	Stack & operator=(const Stack & other) = delete;
	Stack & operator=(Stack && other) = delete;

	const StackElement & top() const;

	void push(const StackElement & el);
	void pop();

};

#endif
