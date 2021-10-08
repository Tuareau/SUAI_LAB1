#pragma once
#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "AbstractQueue.h"
#include "HalfLinkedElement.h"

#include <stdexcept>
#include <iostream>
#include "IInput.h"

class ForwardList : public AbstractQueue
{
private:
	HalfLinkedElement * _head;

public:
	ForwardList();
	ForwardList(const ForwardList & other);
	ForwardList(ForwardList && other) noexcept;
	~ForwardList();

	ForwardList & operator=(const ForwardList & other) = delete;
	ForwardList & operator=(ForwardList && other) = delete;

	void clear();
	void copy(const ForwardList & other);

	void push_back(const Element & el);
	void push_front(const Element & el);
	void pop_back();
	void pop_front();

	virtual ContainerType type() const override;

	virtual void push(const Element & el) override;
	virtual void pop() override;

	const HalfLinkedElement & front() const;
	const HalfLinkedElement & back() const;

	void insert(size_t idx, const Element & el);
	void erase(size_t idx);

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