#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#include "AbstractQueue.h"
#include "HalfLinkedElement.h"

#include <stdexcept>

class Stack : public AbstractQueue
{
private:
	HalfLinkedElement * _top;

	void clear();
	void copy(const Stack & other);

public:
	Stack();
	Stack(const Stack & other);
	Stack(Stack && other) noexcept;
	~Stack();

	Stack & operator=(const Stack & other) = delete;
	Stack & operator=(Stack && other) = delete;

	const HalfLinkedElement & top() const;

	void push(const HalfLinkedElement & el);
	void pop();

};

#endif
