#include "AbstractQueue.h"

#include <list>
#include <deque>
#include <stack>

/*
bool empty() const { return _size == 0; }
void enqueue(int x);
int dequeue();
*/

/*
list 
	push/pop back_front 
	emplace back_front 
	front back
	begin end
	empty clear merge size
	erase

deque
	push/pop back_front
	emplace back_front 
	front back
	begin end
	empty clear size
	erase

stack
	push/pop
	emplace
	top
	begin end
	empty size

*/

AbstractQueue::~AbstractQueue()
{

	Element *iter;
	while (_tail)
	{
		iter = _tail;
		_tail = _tail->get_ptr();
		delete iter;		
	}
}

void AbstractQueue::enqueue(int x)
{
	Element *curr = new Element(x);

	if (_tail)
		curr->set_ptr(_tail);

	_tail = curr;
	_size++;
}

void AbstractQueue::dequeue(int & dest)
{
	int x = 0;
	if (!_tail)
		std::cout << "Already empty\n";
	else
	{
		Element * destr = _tail;
		Element * first = NULL;
		while (destr->get_ptr())
		{
			first = destr;
			destr = destr->get_ptr();
		}

		dest = destr->value();
		delete destr;
		if (first)
			first->set_ptr(NULL);
		else
			_tail = NULL;
		_size--;
	}
}

bool AbstractQueue::empty() const
{
	return _size == 0;
}

AbstractQueue::AbstractQueue(const AbstractQueue & qu)
{
	if (qu.tail == NULL)
	{
		_tail = NULL;
		_size = 0;
	}
	else
	{
		Element *curr = qu.tail;
		_tail = new Element(curr->value());
		Element *iter = _tail;
		_size++;

		curr = curr->get_ptr();
		Element *tmp;
		while (curr)
		{
			tmp = new Element(curr->value());
			iter->set_ptr(tmp);
			iter = iter->get_ptr();
			curr = curr->get_ptr();
			_size++;
		}
	}
}