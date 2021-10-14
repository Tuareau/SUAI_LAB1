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
	if (other.empty()) {
		_head = nullptr;
		_size = 0; _is_empty = true;
	}
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

AbstractQueue::ContainerType ForwardList::type() const {
	return AbstractQueue::ContainerType::FORWARD_LIST;
}

void ForwardList::clear() {
	while (_head) {
		HalfLinkedElement * curr = _head;
		_head = _head->ptr();
		delete curr;
	}
	_is_empty = true; _size = 0; _head = nullptr;
}

void ForwardList::push(const Element & el) {
	using std::cout;
	enum choices { FRONT = 1, BACK, INDEX, CANCEL };
	int choice = 0;
	cout << "\nForward list asks where to push:\n";
	cout << "1 - front\n";
	cout << "2 - back\n";
	cout << "3 - by index\n";
	cout << "4 - cancel\n";

	IInput<int> input;
	choice = input.getValueFromInput();
	if (choice < FRONT || choice > CANCEL) {
		cout << "\nWrong choice, canceled\n";
		return;
	}

	size_t idx;
	switch (choice) {
	case FRONT:
		push_front(el);
		break;
	case BACK:
		push_back(el);
		break;
	case INDEX:
		cout << "\nPut index (0 - " << this->size() << "): ";
		idx = (size_t)input.getValueFromInput();
		insert(idx, el);
		break;
	case CANCEL:
		break;
	default:
		break;
	}
}

void ForwardList::pop() {
	if (this->empty()) {
		throw std::out_of_range("ForwardList::pop(): list was empty");
	}
	using std::cout;
	enum choices { FRONT = 1, BACK, INDEX, CANCEL };
	int choice = 0;
	cout << "\nForward list asks where to pop from:\n";
	cout << "1 - front\n";
	cout << "2 - back\n";
	cout << "3 - by index\n";
	cout << "4 - cancel\n";

	IInput<int> input;
	choice = input.getValueFromInput();
	if (choice < FRONT || choice > CANCEL) {
		cout << "\nWrong choice, canceled\n";
		return;
	}

	size_t idx;
	switch (choice) {
	case FRONT:
		pop_front();
		break;
	case BACK:
		pop_back();
		break;
	case INDEX:
		cout << "\nPut index (0 - " << this->size() - 1 << "): ";
		idx = (size_t)input.getValueFromInput();
		erase(idx);
		break;
	case CANCEL:
		break;
	default:
		break;
	}
}

void ForwardList::push_back(const Element & el) {
	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	if (_head) {
		HalfLinkedElement * last = _head;
		while (last->ptr())
			last = last->ptr();

		last->set_ptr(element);
	}
	else {
		_head = element;
	}
	_size++; _is_empty = false;
}

void ForwardList::pop_back() {
	HalfLinkedElement * last = _head;
	HalfLinkedElement * beside = nullptr;
	while (last->ptr()) {
		beside = last;
		last = last->ptr();
	}
	if (beside) {
		beside->set_ptr(nullptr);
	}
	delete last;
	_size--;
	if (!_size) {
		_head = nullptr;
		_is_empty = true;
	}
}

const HalfLinkedElement & ForwardList::back() const {
	if (this->empty()) {
		throw std::out_of_range("ForwardList::back(): list was empty");
	}
	HalfLinkedElement * last = _head;
	while (last->ptr()) {
		last = last->ptr();
	}
	return *last;
}

void ForwardList::push_front(const Element & el) {
	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	if (_head) {
		element->set_ptr(_head);
	}
	_head = element;
	++_size; _is_empty = false;
}

void ForwardList::pop_front() {
	HalfLinkedElement * element = _head;
	_head = _head->ptr();
	delete element;
	if (!--_size) {
		_is_empty = true;
		_head = nullptr;
	}
}

const HalfLinkedElement & ForwardList::front() const {
	if (this->empty()) {
		throw std::out_of_range("ForwardList::front(): list was empty");
	}
	return *_head;
}

void ForwardList::insert(size_t idx, const Element & el) {
	if (idx > _size) {
		throw std::invalid_argument("ForwardList::insert(): invalid index");
	}

	HalfLinkedElement * curr = _head;
	while (--idx)
		curr = curr->ptr();

	if (curr == _head) {
		push_front(el);
		return;
	}
	if (!curr) {
		push_back(el);
		return;
	}

	HalfLinkedElement * element = new HalfLinkedElement(el.value());
	element->set_ptr(curr->ptr());
	curr->set_ptr(element);

	_size++; _is_empty = false;
}

void ForwardList::erase(size_t idx) {
	if (idx >= _size) {
		throw std::invalid_argument("ForwardList::erase(): invalid index");
	}

	HalfLinkedElement * curr = _head;
	HalfLinkedElement * beside = curr;
	while (idx--) {
		beside = curr;
		curr = curr->ptr();
	}

	if (curr == _head) {
		pop_front();
		return;
	}

	beside->set_ptr(curr->ptr());
	delete curr;

	if (!(--_size)) {
		_head = nullptr;
		_is_empty = true;
	}
}

ForwardList::ConstForwardIterator ForwardList::cbegin() const {
	return ConstForwardIterator(_head);
}

void ForwardList::print(std::ostream & os) const {
	for (auto iter = this->cbegin(); iter.ptr() != nullptr; ++iter) {
		os << (*iter).value() << " ";
	}
	os << std::endl;
}