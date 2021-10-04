#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Element.h"

class AbstractQueue
{
protected:
	bool _is_empty;
	size_t _size;

public:
	AbstractQueue() : _size(0), _is_empty(true) {}
	AbstractQueue(const AbstractQueue & qu) : _size(qu._size), _is_empty(qu._is_empty) {}
	AbstractQueue(AbstractQueue && qu) noexcept = default;
	virtual ~AbstractQueue() = default;

	size_t size() const { return _size; }
	bool empty() const { return _is_empty; }

	virtual void push(const Element & el) = 0;
	virtual void pop() = 0;

};

#endif