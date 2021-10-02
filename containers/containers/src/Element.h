#pragma once
#ifndef _ELEMENT_H_
#define _ELEMENT_H_

class Element 
{
private:
	int _value;

public:
	Element() : _value(0) {}
	explicit Element(int val) : _value(val) {}
	~Element() = default;

	int value() const { return _value; }

	void set_value(int val) { _value = val; }
};

#endif