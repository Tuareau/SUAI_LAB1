#pragma once
#ifndef _STACK_ELEMENT_H_
#define _STACK_ELEMENT_H_

#include "Element.h"

class StackElement : public Element
{
private:
	StackElement * _lower;

public:
	StackElement() : Element(0), _lower(nullptr) {}
	explicit StackElement(int val) : Element(val), _lower(nullptr) {}
	~StackElement() = default;

	StackElement * ptr() const { return _lower; }

	void set_ptr(StackElement * ptr) { _lower = ptr; }
};

#endif
