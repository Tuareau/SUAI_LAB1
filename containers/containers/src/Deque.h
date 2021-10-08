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

	virtual ContainerType type() const override;

	void insert(size_t idx, const Element & el);
	void erase(size_t idx);

	virtual void print(std::ostream & os) const override;

	class ConstForwardIterator
	{
	private:
		LinkedElement * _ptr;
	public:
		ConstForwardIterator() : _ptr(nullptr) {}
		explicit ConstForwardIterator(LinkedElement * ptr) : _ptr(ptr) {}
		ConstForwardIterator(const ConstForwardIterator & iter) : _ptr(iter._ptr) {}
		~ConstForwardIterator() = default;

		ConstForwardIterator operator++() { _ptr = _ptr->right_ptr(); return ConstForwardIterator(_ptr); }
		const LinkedElement & operator*() const { return *_ptr; }
		const LinkedElement * ptr() const { return _ptr; }
	};
	ConstForwardIterator cbegin() const;

};

#endif