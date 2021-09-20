#pragma once
#ifndef _ELEMENT_H_
#define _ELEMENT_H_

class Element 
{
private:
	int _value;
	Element * _prev;
public:
	Element() : _value(0), _prev(nullptr) {}
	explicit Element(int val) : _value(val), _prev(nullptr) {}
	~Element() = default;

	void set_ptr(Element * p) { _prev = p; }
	Element * get_ptr() { return _prev; }
	int value() { return _value; }
};

#endif