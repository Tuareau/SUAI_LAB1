#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

class AbstractQueue
{
protected:
	bool _is_empty;
	size_t _size;

public:
	AbstractQueue() : _size(0), _is_empty(true) {}
	AbstractQueue(const AbstractQueue & qu) : _size(qu._size), _is_empty(qu._is_empty) {}
	AbstractQueue(AbstractQueue && qu) noexcept = default;
	~AbstractQueue() = default;

	virtual size_t size() const = 0 { return _size; }
	virtual bool empty() const = 0 { return _is_empty; }
};

#endif