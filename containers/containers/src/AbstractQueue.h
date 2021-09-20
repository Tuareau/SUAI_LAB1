#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include "Element.h"

class AbstractQueue
{
private:
	Element * _tail;
	size_t _size;

protected:
	Element * tail() const { return _tail; }
	size_t size() const { return _size; }

public:
	AbstractQueue() { _tail = NULL; _size = 0; }
	AbstractQueue(const AbstractQueue & qu);
	~AbstractQueue();
	
	bool empty() const;
	void enqueue(int val);
	void dequeue(int & destination);
};

#endif