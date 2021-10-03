#include "Keeper.h"

Keeper::Keeper() {
	_containers.resize(CONTAINERS, nullptr);
	has_stack = has_deque = has_list = false;
}

Keeper::~Keeper() {
	clear();
}

void Keeper::add_container(AbstractQueue * container) {
	if (dynamic_cast<Deque *>(container)) {
		if (has_deque)
			std::cout << "Sorry, limited count of deques was reached\n";
		else {
			for (size_t i = 0; i < CONTAINERS; ++i)
				if (!_containers[i]) {
					_containers[i] = container;
					has_deque = true;
					std::cout << "Deque was added successfuly\n";
					break;
				}
		}		
	}
	else if (dynamic_cast<Stack *>(container)) {
		if (has_stack)
			std::cout << "Sorry, limited count of stacks was reached\n";
		else {
			for (size_t i = 0; i < CONTAINERS; ++i)
				if (!_containers[i]) {
					_containers[i] = container;
					has_stack = true;
					std::cout << "Stack was added successfuly\n";
					break;
				}
		}
	}
	else if (dynamic_cast<ForwardList *>(container)) {
		if (has_list)
			std::cout << "Sorry, limited count of lists was reached\n";
		else {
			for (size_t i = 0; i < CONTAINERS; ++i)
				if (!_containers[i]) {
					_containers[i] = container;
					has_list = true;
					std::cout << "Forward list was added successfuly\n";
					break;
				}
		}
	}
}

void Keeper::delete_container(ContainerType type) {
	if (type == ContainerType::DEQUE) {
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<Deque *>(_containers[i])) {
				_containers[i] = nullptr;
				has_deque = false;
				std::cout << "Deque was removed successfuly\n";
			}
	}
	else if (type == ContainerType::STACK) {
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<Stack *>(_containers[i])) {
				_containers[i] = nullptr;
				has_stack = false;
				std::cout << "Stack was removed successfuly\n";
			}
	}
	else if (type == ContainerType::FORWARD_LIST) {
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<ForwardList *>(_containers[i])) {
				_containers[i] = nullptr;
				has_list = false;
				std::cout << "List was removed successfuly\n";
			}
	}
}

void Keeper::run() {
	using std::cout;
	cout << "\n\tKEEPER\n";
	cout << "\n\tKeeper object has information about containers:\n";
	cout << "\n- Stack\n- Deque\n- Forward List\n";
	cout << "\n\tAny of these can be added once\n";
	int choice = 0;
	while (choice != QUIT)
	{
		cout << "\nChoose action:\n";
		cout << "1 - add container\n";
		cout << "2 - delete container\n";
		cout << "3 - load from file\n";
		cout << "4 - save in file\n";
		cout << "5 - work with containers\n";
		cout << "6 - quit\n";

		IInput<int> input;
		choice = input.getValueFromInput();
		if (choice < ADD || choice > QUIT) {
			system("cls");
			cout << "Wrong choice, try again\n";
			continue;
		}

		system("cls");
		switch (choice) {
		case ADD:
			add();
			break;
		case DELETE:
			remove();
			break;
		case SAVE:
			save();
			break;
		case LOAD:
			load();
			break;
		case PROCESS:
			process();
			break;
		case QUIT:
			break;
		default:
			break;
		}
	}
}

void Keeper::add()
{
	using std::cout;
	cout << "\n\tADD CONTAINER\n";
	int choice = 0;
	cout << "\nWhat type of container:\n";
	cout << "1 - add deque\n";
	cout << "2 - add stack\n";
	cout << "3 - add forward list\n";
	cout << "4 - cancel\n";

	IInput<int> input;
	choice = input.getValueFromInput();
	if (choice < (int)ContainerType::DEQUE 
		|| choice >(int)ContainerType::NONE) {
		cout << "Wrong choice, canceled\n";
		return;
	}

	system("cls");
	AbstractQueue * deque, * stack, * list;
	switch (choice) {
	case (int)ContainerType::DEQUE:
		deque = new Deque;
		add_container(deque);
		break;
	case (int)ContainerType::STACK:
		stack = new Stack;
		add_container(stack);
		break;
	case (int)ContainerType::FORWARD_LIST:
		list = new ForwardList;
		add_container(list);
		break;
	case (int)ContainerType::NONE:
		break;
	default:
		break;
	}
}

void Keeper::remove() {
	using std::cout;
	cout << "\n\tDELETE CONTAINER\n";
	int choice = 0;
	cout << "\nWhat type of container:\n";
	cout << "1 - delete deque\n";
	cout << "2 - delete stack\n";
	cout << "3 - delete forward list\n";
	cout << "4 - cancel\n";

	IInput<int> input;
	choice = input.getValueFromInput();
	if (choice < (int)ContainerType::DEQUE
		|| choice >(int)ContainerType::NONE) {
		cout << "Wrong choice, canceled\n";
		return;
	}

	system("cls");
	switch (choice) {
	case (int)ContainerType::DEQUE:
		delete_container(ContainerType::DEQUE);
		break;
	case (int)ContainerType::STACK:
		delete_container(ContainerType::STACK);
		break;
	case (int)ContainerType::FORWARD_LIST:
		delete_container(ContainerType::FORWARD_LIST);
		break;
	case (int)ContainerType::NONE:
		break;
	default:
		break;
	}
}

void Keeper::process() {
	using std::cout;
	cout << "\n\tWORK WITH CONTAINERS\n";
	int choice = 0;
	while (choice != END) {
		cout << "\nNote that we'll work with all containers at one time:\n";
		cout << "Containers manipulations:\n";
		cout << "1 - add element\n";
		cout << "2 - delete element\n";
		cout << "3 - output\n";
		cout << "4 - cancel\n";

		IInput<int> input;
		choice = input.getValueFromInput();
		if (choice < ENQUEUE
			|| choice > END) {
			system("cls");
			cout << "Wrong choice, try again\n";
			continue;
		}

		int value;
		system("cls");
		switch (choice) {
		case ENQUEUE:
			cout << "Put your element: ";
			value = input.getValueFromInput();
			for (size_t i = 0; i < CONTAINERS; ++i)
				if (_containers[i])
					_containers[i]->push(Element(value));
			break;
		case DEQUEUE:
			for (size_t i = 0; i < CONTAINERS; ++i)
				if (_containers[i])
					_containers[i]->pop();
			break;
		case OUTPUT:
			output();
			break;
		case END:
			break;
		default:
			break;
		}
	}
}

AbstractQueue * Keeper::find_container(ContainerType type) const {
	switch (type) {
	case ContainerType::DEQUE:
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<Deque *>(_containers[i]))
				return _containers[i];
		break;
	case ContainerType::STACK:
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<Stack *>(_containers[i]))
				return _containers[i];
		break;
	case ContainerType::FORWARD_LIST:
		for (size_t i = 0; i < CONTAINERS; ++i)
			if (dynamic_cast<ForwardList *>(_containers[i]))
				return _containers[i];
		break;
	case ContainerType::NONE:
		break;
	default:
		break;
	}
	return nullptr;
}

void Keeper::output() const {
	Deque * deque = dynamic_cast<Deque *>(find_container(ContainerType::DEQUE));
	if (deque) {
		std::cout << "\nDEQUE\n";
		for (Deque::Iterator iter = deque->begin(); iter.ptr() != nullptr; ++iter)
			std::cout << (*iter).value() << " ";
		std::cout << std::endl;
	}
	Stack * stack = dynamic_cast<Stack *>(find_container(ContainerType::STACK));
	if (stack) {
		std::cout << "\nSTACK\n";
		for (Stack::Iterator iter = stack->begin(); iter.ptr() != nullptr; ++iter)
			std::cout << (*iter).value() << " ";
		std::cout << std::endl;
	}
	ForwardList * list = dynamic_cast<ForwardList *>(find_container(ContainerType::FORWARD_LIST));
	if (list) {
		std::cout << "\nFORWARD LIST\n";
		for (ForwardList::Iterator iter = list->begin(); iter.ptr() != nullptr; ++iter)
			std::cout << (*iter).value() << " ";
		std::cout << std::endl;
	}
}

void Keeper::save() const {
	std::ofstream fout("containers.txt", std::ios_base::trunc | std::ios_base::out);
	Deque * deque = dynamic_cast<Deque *>(find_container(ContainerType::DEQUE));
	if (deque) {
		fout << (int)ContainerType::DEQUE << " ";
		fout << deque->size() << "\n";
		for (Deque::Iterator iter = deque->begin(); iter.ptr() != nullptr; ++iter)
			fout << (*iter).value() << " ";
		fout << std::endl;
	}
	Stack * stack = dynamic_cast<Stack *>(find_container(ContainerType::STACK));
	if (stack) {
		fout << (int)ContainerType::STACK << " ";
		fout << stack->size() << "\n";
		for (Stack::Iterator iter = stack->begin(); iter.ptr() != nullptr; ++iter)
			fout << (*iter).value() << " ";
		fout << std::endl;
	}
	ForwardList * list = dynamic_cast<ForwardList *>(find_container(ContainerType::FORWARD_LIST));
	if (list) {
		fout << (int)ContainerType::FORWARD_LIST << " ";
		fout << list->size() << "\n";
		for (ForwardList::Iterator iter = list->begin(); iter.ptr() != nullptr; ++iter)
			fout << (*iter).value() << " ";
		fout << std::endl;
	}
	std::cout << "\nEverything was saved successfuly\n";
	fout.close();
}

void Keeper::load() {
	std::ifstream fin("containers.txt", std::ios_base::in);
	clear();
	if (!fin.good()) {
		std::cout << "\nCouldn't open file\n";
		return;
	}

	int type, value;
	size_t size;
	AbstractQueue * container = nullptr;
	while (fin.good() && !fin.eof() && fin.peek() != EOF) {
		fin >> type >> size;
		switch (type) {
		case (int)ContainerType::DEQUE:
			container = new Deque;
			break;
		case (int)ContainerType::STACK:
			container = new Stack;
			break;
		case (int)ContainerType::FORWARD_LIST:
			container = new ForwardList;
			break;
		default:
			break;
		}
		while (size--) {
			fin >> value;
			container->push(Element(value));
		}
		for (size_t i = 0; i < CONTAINERS; i++)
			if (!_containers[i])
				_containers[i] = container;		
	}
	std::cout << "\nEverything was loaded successfuly\n";
	fin.close();
}

void Keeper::clear() {
	for (size_t i = 0; i < CONTAINERS; ++i) {
		delete _containers[i];
		_containers[i] = nullptr;
	}
}