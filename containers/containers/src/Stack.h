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

	virtual void print(std::ostream & os) const override;

	class ConstForwardIterator
	{
	private:
		HalfLinkedElement * _ptr;
	public:
		ConstForwardIterator() : _ptr(nullptr) {}
		explicit ConstForwardIterator(HalfLinkedElement * ptr) : _ptr(ptr) {}
		ConstForwardIterator(const ConstForwardIterator & iter) : _ptr(iter._ptr) {}
		~ConstForwardIterator() = default;

		ConstForwardIterator operator++() { _ptr = _ptr->ptr(); return ConstForwardIterator(_ptr); }
		const HalfLinkedElement & operator*() const { return *_ptr; }
		const HalfLinkedElement * ptr() const { return _ptr; }
	};
	ConstForwardIterator cbegin() const;

};

#endif