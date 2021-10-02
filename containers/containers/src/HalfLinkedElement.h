#pragma once
#ifndef _STACK_ELEMENT_H_
#define _STACK_ELEMENT_H_

#include "Element.h"

class HalfLinkedElement : public Element
{
private:
	HalfLinkedElement * _ptr;

public:
	HalfLinkedElement() : Element(0), _ptr(nullptr) {}
	explicit HalfLinkedElement(int val) : Element(val), _ptr(nullptr) {}
	~HalfLinkedElement() = default;

	HalfLinkedElement * ptr() const { return _ptr; }

	void set_ptr(HalfLinkedElement * ptr) { _ptr = ptr; }
};

#endif
