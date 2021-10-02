#pragma once
#ifndef _LIST_ELEMENT_H_
#define _LIST_ELEMENT_H_

#include "Element.h"

class ListElement : public Element
{
private:
	ListElement * _prev;
	ListElement * _next;

public:
	ListElement() : Element(0), _prev(nullptr), _next(nullptr) {}
	explicit ListElement(int val) : Element(val), _prev(nullptr), _next(nullptr) {}
	~ListElement() = default;

	ListElement * prev_ptr() const { return _prev; }
	ListElement * next_ptr() const { return _next; }

	void set_prev(ListElement * ptr) { _prev = ptr; }
	void set_next(ListElement * ptr) { _next = ptr; }
};

#endif