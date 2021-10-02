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


	class Iterator
	{
	private:
		LinkedElement * _ptr;

	public:
		Iterator();
		explicit Iterator(LinkedElement * ptr);
		Iterator(const Iterator & iter);
		~Iterator() = default;

		Iterator & operator=(const Iterator & iter);

		Iterator & operator++();
		Iterator & operator--();
		Iterator operator++(int);
		Iterator operator--(int);

		bool operator!=(const Iterator & iter);
		bool operator==(const Iterator & iter);

		LinkedElement & operator*();

	};

	Iterator begin() const;
	Iterator end() const;

	void insert(const Iterator & pos, const LinkedElement & el);
	void erase(const Iterator & pos);

};

#endif
