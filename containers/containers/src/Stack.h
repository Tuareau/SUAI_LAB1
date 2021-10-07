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

	virtual void push(const Element & el) override;
	virtual void pop() override;

	virtual ContainerType type() const override;

	class Iterator
	{
	private:
		HalfLinkedElement * _ptr;
	public:
		Iterator() : _ptr(nullptr) {}
		explicit Iterator(HalfLinkedElement * ptr) : _ptr(ptr) {}
		Iterator(const Iterator & iter) : _ptr(iter._ptr) {}
		~Iterator() = default;
		Iterator & operator=(const Iterator & iter) { _ptr = iter._ptr; }
		Iterator operator++() { _ptr = _ptr->ptr(); return Iterator(_ptr); }
		HalfLinkedElement & operator*() { return *_ptr; }
		HalfLinkedElement * ptr() { return _ptr; }
	};
	Iterator begin() { return Iterator(_top); }

};

#endif