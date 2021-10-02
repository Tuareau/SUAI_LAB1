#include "Stack.h"

Stack::Stack() 
	: _top(nullptr), AbstractQueue() {}

Stack::Stack(const Stack & other) : AbstractQueue() {
	copy(other);
}

void Stack::copy(const Stack & other)
{
	if (other.empty())
		_top = nullptr;
	else {
		_top = new StackElement(other._top->value());
		StackElement * curr = _top;
		_is_empty = false;

		StackElement * original = other._top->ptr();

		while (original) {
			curr->set_ptr(new StackElement(original->value()));
			curr = curr->ptr();
			original = original->ptr();
			_size++;
		}
	}
}

Stack::Stack(Stack && other) noexcept : AbstractQueue() {
	_top = other._top;
	_is_empty = false;
	_size = other._size;

	other._top = nullptr;
	other._size = 0;
	other._is_empty = true;
}

Stack::~Stack() {
	clear();
}

void Stack::clear() {
	while (_top) {
		StackElement * curr = _top;
		_top = _top->ptr();
		delete curr;
	}
	AbstractQueue::_is_empty = true;
	AbstractQueue::_size = 0;
}

const StackElement & Stack::top() const {
	return *_top;
}

void Stack::push(const StackElement & el) {
	StackElement * curr = new StackElement(el);
	curr->set_ptr(_top);
	_top = curr;		
	_size++; _is_empty = false;
}

void Stack::pop() {
	if (this->empty())
		throw std::out_of_range("Stack::pop(): stack was empty");
	StackElement * curr = _top;
	_top = _top->ptr();
	delete curr;
	_size--;
	if (!_top) _is_empty = true;
}