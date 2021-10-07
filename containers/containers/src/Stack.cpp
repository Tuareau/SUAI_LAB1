#include "Stack.h"

Stack::Stack() 
	: _top(nullptr), AbstractQueue() {}

Stack::Stack(const Stack & other) : AbstractQueue() {
	copy(other);
}

void Stack::copy(const Stack & other) {
	clear();
	if (other.empty()) {
		_top = nullptr;
		_size = 0; _is_empty = true;
	}
	else {
		_top = new HalfLinkedElement(other._top->value());
		HalfLinkedElement * curr = _top;
		_is_empty = false; _size++;

		HalfLinkedElement * original = other._top->ptr();

		while (original) {
			curr->set_ptr(new HalfLinkedElement(original->value()));
			curr = curr->ptr();
			original = original->ptr();
			_size++;
		}
	}
}

Stack::Stack(Stack && other) noexcept : AbstractQueue() {
	_top = other._top;
	_is_empty = other._is_empty;
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
		HalfLinkedElement * curr = _top;
		_top = _top->ptr();
		delete curr;
	}
	_is_empty = true; _size = 0; _top = nullptr;
}

const HalfLinkedElement & Stack::top() const {
	if (this->empty())
		throw std::out_of_range("Stack::top(): stack was empty");
	return *_top;
}

void Stack::push(const Element & el) {
	HalfLinkedElement * curr = new HalfLinkedElement(el.value());
	curr->set_ptr(_top);
	_top = curr;		
	_size++; _is_empty = false;
}

void Stack::pop() {
	if (this->empty())
		throw std::out_of_range("Stack::pop(): stack was empty");
	HalfLinkedElement * curr = _top;
	_top = _top->ptr();
	delete curr;
	_size--;
	if (!_top) _is_empty = true;
}

AbstractQueue::ContainerType Stack::type() const {
	return AbstractQueue::ContainerType::STACK;
}