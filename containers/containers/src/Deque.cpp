#include "Deque.h"

Deque::Deque() : AbstractQueue(), _head(nullptr) {
	std::cout << "\n# Deque::Deque() constructor called\n";
}

Deque::Deque(const Deque & other) : AbstractQueue() {
	std::cout << "\n# Deque::Deque(const Deque &) constructor called\n";
	copy(other);
}

Deque::~Deque() {
	std::cout << "\n# Deque::~Deque() destructor called\n";
	clear();
}

Deque::Deque(Deque && other) noexcept : AbstractQueue() {
	std::cout << "\n# Deque::Deque(Deque &&) constructor called\n";
	_head = other._head;
	_is_empty = other._is_empty;
	_size = other._size;

	other._head = nullptr;
	other._size = 0;
	other._is_empty = true;
}

AbstractQueue::ContainerType Deque::type() const {
	return AbstractQueue::ContainerType::DEQUE;
}

void Deque::copy(const Deque & other) {
	clear();
	if (other.empty()) {
		_head = nullptr;
		_size = 0; _is_empty = true;
	}
	else {
		_head = new LinkedElement(other._head->value());
		LinkedElement * beside_curr = _head;
		_is_empty = false; _size++;

		LinkedElement * original = other._head->right_ptr();

		while (original) {
			auto * curr = new LinkedElement(original->value());
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
	_is_empty = true; _size = 0; _head = nullptr;
}

void Deque::push(const Element & el) {
	using std::cout;
	enum choices { FRONT = 1, BACK, INDEX, CANCEL };
	size_t choice = 0;
	cout << "\nDeque asks where to push:\n";
	cout << "1 - front\n";
	cout << "2 - back\n";
	cout << "3 - by index\n";
	cout << "4 - cancel\n";

	IInput<size_t> input;
	choice = input.getValueFromInput();

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
		idx = input.getValueFromInput();
		insert(idx, el);
		break;
	case CANCEL:
		break;
	default:
		cout << "\nWrong choice, canceled\n";
		return;
	}
}

void Deque::pop() {
	if (this->empty()) {
		throw std::out_of_range("Deque::pop(): deque was empty");
	}
	using std::cout;
	enum choices { FRONT = 1, BACK, INDEX, CANCEL };
	size_t choice = 0;
	cout << "\nDeque asks where to pop from:\n";
	cout << "1 - front\n";
	cout << "2 - back\n";
	cout << "3 - by index\n";
	cout << "4 - cancel\n";

	IInput<size_t> input;
	choice = input.getValueFromInput();

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
		idx = input.getValueFromInput();
		erase(idx);
		break;
	case CANCEL:
		break;
	default:
		cout << "\nWrong choice, canceled\n";
		return;
	}
}

void Deque::push_back(const Element & el) {
	LinkedElement * element = new LinkedElement(el.value());
	if (_head) {
		LinkedElement * last = _head;
		while (last->right_ptr())
			last = last->right_ptr();

		last->set_right_ptr(element);
		element->set_left_ptr(last);
	}
	else {
		_head = element;
	}
	_size++; _is_empty = false;
}

void Deque::pop_back() {
	LinkedElement * last = _head;
	LinkedElement * beside = nullptr;
	while (last->right_ptr()) {
		beside = last;
		last = last->right_ptr();
	}

	if (beside) {
		beside->set_right_ptr(nullptr);
	}
	delete last;
	_size--;
	if (!_size) {
		_head = nullptr;
		_is_empty = true;
	}
}

const LinkedElement & Deque::back() const {
	if (this->empty()) {
		throw std::out_of_range("Deque::back(): deque was empty");
	}
	LinkedElement * last = _head;
	while (last->right_ptr())
		last = last->right_ptr();
	return *last;
}

void Deque::push_front(const Element & el) {
	LinkedElement * element = new LinkedElement(el.value());
	if (_head) {
		element->set_right_ptr(_head);
		_head->set_left_ptr(element);
	}
	_head = element;
	++_size; _is_empty = false;
}

void Deque::pop_front() {
	LinkedElement * element = _head;
	_head = _head->right_ptr();
	if (_head)
		_head->set_left_ptr(nullptr);
	delete element;
	if (!--_size) {
		_head = nullptr;
		_is_empty = true;
	}
}

const LinkedElement & Deque::front() const {
	if (this->empty()) {
		throw std::out_of_range("Deque::front(): deque was empty");
	}
	return *_head;
}

const LinkedElement & Deque::at(size_t idx) const {
	if (idx >= _size) {
		throw std::invalid_argument("Deque::at(): invalid index");
	}
	LinkedElement * curr = _head;
	while (idx--)
		curr = curr->right_ptr();
	return *curr;
}

LinkedElement & Deque::at(size_t idx) {
	if (idx >= _size) {
		throw std::invalid_argument("Deque::at(): invalid index");
	}
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

void Deque::insert(size_t idx, const Element & el) {
	if (idx > _size) {
		throw std::invalid_argument("Deque::insert(): invalid index");
	}

	LinkedElement * curr = _head;
	while (idx--) {
		curr = curr->right_ptr();
	}

	if (curr == _head) {
		push_front(el); 
		return;
	}
	if (!curr) {
		push_back(el);
		return;
	}

	LinkedElement * element = new LinkedElement(el.value());
	element->set_left_ptr(curr->left_ptr());
	curr->left_ptr()->set_right_ptr(element);
	curr->set_left_ptr(element);
	element->set_right_ptr(curr);

	_size++; _is_empty = false;
}

void Deque::erase(size_t idx) {
	if (idx >= _size) {
		throw std::invalid_argument("Deque::erase(): invalid index");
	}

	LinkedElement * curr = _head;
	while (idx--)
		curr = curr->right_ptr();

	if (!(curr->left_ptr())) {
		pop_front(); return;
	}
	if (!(curr->right_ptr())) {
		pop_back(); return;
	}

	curr->left_ptr()->set_right_ptr(curr->right_ptr());
	curr->right_ptr()->set_left_ptr(curr->left_ptr());
	delete curr;

	if (!(--_size)) {
		_head = nullptr;
		_is_empty = true;
	}
}

Deque::ConstForwardIterator Deque::cbegin() const {
	return ConstForwardIterator(_head);
}

void Deque::print(std::ostream & os) const {
	for (auto iter = this->cbegin(); iter.ptr() != nullptr; ++iter) {
		os << (*iter).value() << " ";
	}
	os << std::endl;
}