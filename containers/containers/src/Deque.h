#pragma once
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "AbstractQueue.h"
#include "LinkedElement.h"

#include <stdexcept>

class Deque : public AbstractQueue
{
private:
	LinkedElement * _head;
	
	void copy(const Deque & other);

public:
	Deque();
	Deque(const Deque & other);
	Deque(Deque && other) noexcept;
	~Deque();

	Deque & operator=(const Deque & other) = delete;
	Deque & operator=(Deque && other) = delete;

	void clear();

	void push_back(const LinkedElement & el);
	void push_front(const LinkedElement & el);
	void pop_back();
	void pop_front();

	const LinkedElement & at(size_t idx) const;
	LinkedElement & at(size_t idx);
	LinkedElement & operator[](size_t idx) noexcept;

	const LinkedElement & front() const;
	const LinkedElement & back() const;

	void insert(size_t idx, const LinkedElement & el);
	void erase(size_t idx);

};

#endif
