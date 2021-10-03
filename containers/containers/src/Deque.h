#pragma once
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "AbstractQueue.h"
#include "LinkedElement.h"

#include <stdexcept>
#include <iostream>
#include "IInput.h"

class Deque : public AbstractQueue
{
private:
	LinkedElement * _head;

public:
	Deque();
	Deque(const Deque & other);
	Deque(Deque && other) noexcept;
	~Deque();

	Deque & operator=(const Deque & other) = delete;
	Deque & operator=(Deque && other) = delete;

	void clear();
	void copy(const Deque & other);

	virtual void push(const Element & el) override;
	virtual void pop() override;

	const LinkedElement & at(size_t idx) const;
	LinkedElement & at(size_t idx);
	LinkedElement & operator[](size_t idx) noexcept;

	const LinkedElement & front() const;
	const LinkedElement & back() const;

	void push_back(const Element & el);
	void push_front(const Element & el);
	void pop_back();
	void pop_front();

	void insert(size_t idx, const Element & el);
	void erase(size_t idx);

};

#endif
