#include "Deque.h"

Deque::Deque() : AbstractQueue(), _head(nullptr) {}

Deque::Deque(const Deque & other) : AbstractQueue() {
	copy(other);
}

Deque::~Deque() {
	clear();
}

Deque::Deque(Deque && other) noexcept : AbstractQueue() {
	_head = other._head;
	_is_empty = other._is_empty;
	_size = other._size;

	other._head = nullptr;
	other._size = 0;
	other._is_empty = true;
}

void Deque::copy(const Deque & other) {
	clear();
	if (other.empty())
		_head = nullptr;
	else {
		_head = new LinkedElement(other._head->value());
		LinkedElement * curr;
		LinkedElement * beside_curr = _head;
		_is_empty = false; _size++;

		LinkedElement * original = other._head->right_ptr();		

		while (original) {
			curr = new LinkedElement(original->value());
			curr->set_left_ptr(beside_curr);
			beside_curr->set_right_ptr(curr);

			beside_curr = curr;
			original = original->right_ptr();
			_size++;
		}
	}
}

void Deque::clear() {
	while (_head) {
		LinkedElement * curr = _head;
		_head = _head->right_ptr();
		delete curr;
	}
	_is_empty = true; _size = 0;
}

void Deque::push_back(const LinkedElement & el) {
	LinkedElement * last = _head;
	while (last->right_ptr())
		last = last->right_ptr();

	LinkedElement * element = new LinkedElement(el);
	last->set_right_ptr(element);
	last->right_ptr()->set_left_ptr(last);
	_size++; _is_empty = false;
}

void Deque::pop_back() {
	if (this->empty())
		throw std::out_of_range("Deque::pop_back(): deque was empty");
	LinkedElement * last = _head;
	while (last->right_ptr())
		last = last->right_ptr();

	last->left_ptr()->set_right_ptr(nullptr);
	delete last;
	_size--;
	if (!size) {
		_head = nullptr;
		_is_empty = true;
	}
}

const LinkedElement & Deque::back() const {
	if (this->empty())
		throw std::out_of_range("Deque::back(): deque was empty");
	LinkedElement * last = _head;
	while (last->right_ptr())
		last = last->right_ptr();
	return *last;
}

void Deque::push_front(const LinkedElement & el) {
	LinkedElement * element = new LinkedElement(el.value());
	element->set_right_ptr(_head);
	_head->set_left_ptr(element);
	_head = element;
	++_size; _is_empty = false;
}

void Deque::pop_front() {
	if (this->empty())
		throw std::out_of_range("Deque::pop_front(): deque was empty");
	LinkedElement * element = _head;
	_head = _head->right_ptr();
	_head->set_left_ptr(nullptr);
	delete element;
	_size--;
	if (!size) {
		_head = nullptr;
		_is_empty = true;
	}
}

void Deque::push_front(const LinkedElement & el) {
	LinkedElement * element = new LinkedElement(el.value());
	element->set_right_ptr(_head);
	_head->set_left_ptr(element);
	_head = element;
	++_size; _is_empty = false;
}

const LinkedElement & Deque::front() const {
	if (this->empty())
		throw std::out_of_range("Deque::front(): deque was empty");
	return *_head;
}

const LinkedElement & Deque::at(size_t idx) const
{
	if (idx >= _size)
		throw std::invalid_argument("Deque::at(): invalid index");
	LinkedElement * curr = _head;
	while (idx--)
		curr = curr->right_ptr();
	return *curr;
}

LinkedElement & Deque::at(size_t idx) {
	if (idx >= _size)
		throw std::invalid_argument("Deque::at(): invalid index");
	LinkedElement * curr = _head;
	while (idx--)
		curr = curr->right_ptr();
	return *curr;
}

LinkedElement & Deque::operator[](size_t idx) noexcept {
	LinkedElement * curr = _head;
	while (idx--)
		curr = curr->right_ptr();
	return *curr;
}

Deque::Iterator Deque::begin() const {
	return Iterator(_head);
}

Deque::Iterator Deque::end() const {
	return Iterator(nullptr);
}



Deque::Iterator::Iterator() : _ptr(nullptr) {}

explicit Deque::Iterator::Iterator(LinkedElement * ptr) 
	: _ptr(ptr) {}

Deque::Iterator::Iterator(const Deque::Iterator & iter) 
	: _ptr(iter._ptr) {}

Deque::Iterator & Deque::Iterator::operator=(const Deque::Iterator & iter) {
	_ptr = iter._ptr;
	return *this;
}

Deque::Iterator & Deque::Iterator::operator++() {
	if (!_ptr)
		throw std::out_of_range("Stack::Iterator: operator++(): ptr was nullptr");
	_ptr = _ptr->right_ptr();
	return *this;
}

Deque::Iterator & Deque::Iterator::operator--() {
	if (!_ptr)
		throw std::out_of_range("Stack::Iterator: operator--(): ptr was nullptr");
	_ptr = _ptr->left_ptr();
	return *this;
}

Deque::Iterator Deque::Iterator::operator++(int) {
	if (!_ptr)
		throw std::out_of_range("Stack::Iterator: operator++(int): ptr was nullptr");
	Iterator it(_ptr->right_ptr());
	return it;
}

Deque::Iterator Deque::Iterator::operator--(int) {
	if (!_ptr)
		throw std::out_of_range("Stack::Iterator: operator--(int): ptr was nullptr");
	Iterator it(_ptr->left_ptr());
	return it;
}

bool Deque::Iterator::operator!=(const Iterator & iter) {
	return _ptr != iter._ptr;
}

bool Deque::Iterator::operator==(const Iterator & iter) {
	return _ptr == iter._ptr;
}

LinkedElement & Deque::Iterator::operator*() {
	return *_ptr;
}
