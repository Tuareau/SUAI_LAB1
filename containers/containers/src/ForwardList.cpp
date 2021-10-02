#include "ForwardList.h"

ForwardList::ForwardList() : AbstractQueue(), _head(nullptr) {}

ForwardList::ForwardList(const ForwardList & other) : AbstractQueue() {
	copy(other);
}

ForwardList::~ForwardList() {
	clear();
}

ForwardList::ForwardList(ForwardList && other) noexcept : AbstractQueue() {
	_head = other._head;
	_is_empty = other._is_empty;
	_size = other._size;

	other._head = nullptr;
	other._size = 0;
	other._is_empty = true;
}

void ForwardList::copy(const ForwardList & other) {
	clear();
	if (other.empty())
		_head = nullptr;
	else {
		_head = new HalfLinkedElement(other._head->value());
		HalfLinkedElement * curr = _head;
		_is_empty = false; _size++;

		HalfLinkedElement * original = other._head->ptr();

		while (original) {
			curr->set_ptr(new HalfLinkedElement(original->value()));
			curr = curr->ptr();
			original = original->ptr();
			_size++;
		}
	}
}

void ForwardList::clear() {
	while (_head) {
		HalfLinkedElement * curr = _head;
		_head = _head->ptr();
		delete curr;
	}
	_is_empty = true; _size = 0;
}

void ForwardList::push_back(const HalfLinkedElement & el) {
	HalfLinkedElement * last = _head;
	while (last->ptr())
		last = last->ptr();
	HalfLinkedElement * element = new HalfLinkedElement(el);
	last->set_ptr(element);
	_size++; _is_empty = false;
}

void ForwardList::pop_back() {
	if (this->empty())
		throw std::out_of_range("ForwardList::pop_back(): list was empty");
	HalfLinkedElement * last = _head;
	HalfLinkedElement * beside;
	while (last->ptr()) {
		beside = last;
		last = last->ptr();
	}

	beside->ptr()->set_ptr(nullptr);
	delete last;
	_size--;
	if (!size) {
		_head = nullptr;
		_is_empty = true;
	}
}

const HalfLinkedElement & ForwardList::back() const {
	if (this->empty())
		throw std::out_of_range("ForwardList::back(): list was empty");
	HalfLinkedElement * last = _head;
	while (last->ptr())
		last = last->ptr();
	return *last;
}

void ForwardList::push_front(const HalfLinkedElement & el) {
	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	element->set_ptr(_head);
	_head = element;
	++_size; _is_empty = false;
}

void ForwardList::pop_front() {
	if (this->empty())
		throw std::out_of_range("ForwardList::pop_front(): list was empty");
	HalfLinkedElement * element = _head;
	_head = _head->ptr();
	delete element;
	_size--;
	if (!size) _is_empty = true;
}

void ForwardList::push_front(const HalfLinkedElement & el) {
	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	element->set_ptr(_head);
	_head = element;
	++_size; _is_empty = false;
}

const HalfLinkedElement & ForwardList::front() const {
	if (this->empty())
		throw std::out_of_range("ForwardList::front(): list was empty");
	return *_head;
}

void ForwardList::insert(size_t idx, const HalfLinkedElement & el) {
	if (idx > _size)
		throw std::invalid_argument("ForwardList::insert(): invalid index");
	if (this->empty()) {
		push_back(el);
		return;
	}

	HalfLinkedElement * curr = _head;
	while (--idx)
		curr = curr->ptr();

	if (curr == _head) {
		if (!idx)
			push_front(el);
		else
			push_back(el);
		return;
	}

	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	element->set_ptr(curr->ptr());
	curr->set_ptr(element);

	_size++; _is_empty = false;
}

void ForwardList::erase(size_t idx) {
	if (idx >= _size)
		throw std::invalid_argument("ForwardList::erase(): invalid index");

	HalfLinkedElement * curr = _head;
	HalfLinkedElement * beside = curr;
	while (idx--) {
		beside = curr;
		curr = curr->ptr();
	}

	beside->set_ptr(curr->ptr());
	delete curr;

	if (--_size) {
		_head = nullptr;
		_is_empty = true;
	}
}