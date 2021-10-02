#pragma once
#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "AbstractQueue.h"
#include "HalfLinkedElement.h"

#include <stdexcept>

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

	void push_back(const HalfLinkedElement & el);
	void push_front(const HalfLinkedElement & el);
	void pop_back();
	void pop_front();

	const HalfLinkedElement & front() const;
	const HalfLinkedElement & back() const;

	void insert(size_t idx, const HalfLinkedElement & el);
	void erase(size_t idx);

};

#endif
