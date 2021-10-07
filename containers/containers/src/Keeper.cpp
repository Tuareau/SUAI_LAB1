#include "Keeper.h"

Keeper::Keeper() {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i)
		_containers[i] = nullptr;
}

Keeper::~Keeper() {
	clear();
}

void Keeper::clear() {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		delete _containers[i];
		_containers[i] = nullptr;
	}
}

void Keeper::insert_container(AbstractQueue * container) {
	const auto index = size_t(container->type());
	if (index >= AbstractQueue::CONTAINERS_COUNT)
		std::cout << "\nYour type of container is not allowed\n";
	if (_containers[index])
		std::cout << "\nSorry, limited count of that type of container (1) was reached\n";
	else {
		_containers[index] = container;
		std::cout << "\nContainer was added successfuly\n";
	}
}

void Keeper::remove_container(AbstractQueue::ContainerType type) {
	const auto index = size_t(type);
	if (index >= AbstractQueue::CONTAINERS_COUNT)
		std::cout << "\nThis type of container is not allowed\n";
	if (_containers[index]) {
		delete _containers[index];
		_containers[index] = nullptr;
		std::cout << "\nContainer was removed successfuly\n";
	}
	else std::cout << "\nKeeper already hasn't container you tried to remove\n";
}

//void Keeper::run() {
//	using std::cout;
//	cout << "\n\tKEEPER\n";
//	cout << "\n\tKeeper object has information about containers:\n";
//	cout << "\n\t- Stack\n\t- Deque\n\t- Forward List\n";
//	cout << "\n\tAny of these can be added once\n";
//	int choice = 0;
//	while (choice != QUIT)
//	{
//		cout << "\nChoose action:\n";
//		cout << "1 - add container\n";
//		cout << "2 - delete container\n";
//		cout << "3 - load from file\n";
//		cout << "4 - save in file\n";
//		cout << "5 - work with containers\n";
//		cout << "6 - quit\n";
//
//		IInput<int> input;
//		choice = input.getValueFromInput();
//		if (choice < ADD || choice > QUIT) {
//			system("cls");
//			cout << "\nWrong choice, try again\n";
//			continue;
//		}
//
//		system("cls");
//		switch (choice) {
//		case ADD:
//			add_container();
//			break;
//		case DELETE:
//			remove();
//			break;
//		case SAVE:
//			load();
//			break;
//		case LOAD:
//			save();
//			break;
//		case PROCESS:
//			process();
//			break;
//		case QUIT:
//			break;
//		default:
//			break;
//		}
//	}
//}

void Keeper::add_container(AbstractQueue::ContainerType type)
{
	//using std::cout;
	//cout << "\n\tADD CONTAINER\n";
	//int choice = 0;
	//cout << "\nWhat type of container:\n";
	//cout << "1 - add deque\n";
	//cout << "2 - add stack\n";
	//cout << "3 - add forward list\n";
	//cout << "4 - cancel\n";

	//IInput<int> input;
	//choice = input.getValueFromInput();
	//if (choice < (int)AbstractQueue::ContainerType::DEQUE
	//	|| choice >(int)AbstractQueue::ContainerType::NONE) {
	//	cout << "\nWrong choice, canceled\n";
	//	return;
	//}

	//system("cls");
	AbstractQueue * container = _factory.make_container(type);
	insert_container(container);
}

void Keeper::remove(AbstractQueue::ContainerType type) {
	//using std::cout;
	//cout << "\n\tDELETE CONTAINER\n";
	//int choice = 0;
	//cout << "\nWhat type of container:\n";
	//cout << "1 - delete deque\n";
	//cout << "2 - delete stack\n";
	//cout << "3 - delete forward list\n";
	//cout << "4 - cancel\n";

	//IInput<int> input;
	//choice = input.getValueFromInput();
	//if (choice < (int)AbstractQueue::ContainerType::DEQUE
	//	|| choice >(int)AbstractQueue::ContainerType::NONE) {
	//	cout << "\nWrong choice, canceled\n";
	//	return;
	//}

	//system("cls");
	remove_container(type);
}

void Keeper::process() {
	using std::cout;
	cout << "\n\tWORK WITH CONTAINERS\n";
	int choice = 0;
	while (choice != END) {
		cout << "\nNote that we'll work with all containers at one time:\n";
		cout << "\nContainers manipulations:\n";
		cout << "1 - add element\n";
		cout << "2 - delete element\n";
		cout << "3 - output\n";
		cout << "4 - cancel\n";

		IInput<int> input;
		choice = input.getValueFromInput();
		if (choice < ENQUEUE
			|| choice > END) {
			system("cls");
			cout << "\nWrong choice, try again\n";
			continue;
		}

		int value;
		system("cls");
		switch (choice) {
		case ENQUEUE:
			if (!_has_deque && !_has_stack && !_has_list)
				cout << "\nNo containers to push to\n";
			else {
				cout << "\nPut your element: ";
				value = input.getValueFromInput();
				for (size_t i = 0; i < CONTAINERS; ++i)
					if (_containers[i])
						_containers[i]->push(Element(value));
			}
			break;
		case DEQUEUE:
			if (!_has_deque && !_has_stack && !_has_list)
				cout << "\nNo containers to pop from\n";
			else {
				for (size_t i = 0; i < CONTAINERS; ++i)
					if (_containers[i]) {
						try {
							_containers[i]->pop();
						}
						catch (const std::out_of_range & range_error) {
							std::cout << "\nException catched: " << range_error.what() << std::endl;
						}
						catch (const std::invalid_argument & arg_error) {
							std::cout << "\nException catched: " << arg_error.what() << std::endl;
						}
					}
			}
			break;
		case OUTPUT:
			output();
			break;
		case END:
			cout << "\nDon't forget to save changes in file\n";
			break;
		default:
			break;
		}
	}
}

//AbstractQueue * Keeper::find_container(ContainerType type) const {
//	switch (type) {
//	case ContainerType::DEQUE:
//		for (size_t i = 0; i < CONTAINERS; ++i)
//			if (dynamic_cast<Deque *>(_containers[i]))
//				return _containers[i];
//		break;
//	case ContainerType::STACK:
//		for (size_t i = 0; i < CONTAINERS; ++i)
//			if (dynamic_cast<Stack *>(_containers[i]))
//				return _containers[i];
//		break;
//	case ContainerType::FORWARD_LIST:
//		for (size_t i = 0; i < CONTAINERS; ++i)
//			if (dynamic_cast<ForwardList *>(_containers[i]))
//				return _containers[i];
//		break;
//	case ContainerType::NONE:
//		break;
//	default:
//		break;
//	}
//	return nullptr;
//}

void Keeper::output() const {
	std::cout << "\nDEQUE\n\n";
	Deque * deque = dynamic_cast<Deque *>(find_container(ContainerType::DEQUE));
	if (deque) {
		if (deque->empty())
			std::cout << "- empty\n";
		else {
			for (Deque::Iterator iter = deque->begin(); iter.ptr() != nullptr; ++iter)
				std::cout << (*iter).value() << " ";
			std::cout << std::endl;
		}
	}
	else std::cout << "- no deque\n";
	
	std::cout << "\nSTACK\n\n";
	Stack * stack = dynamic_cast<Stack *>(find_container(ContainerType::STACK));
	if (stack) {
		if (stack->empty())
			std::cout << "- empty\n";
		else {
			for (Stack::Iterator iter = stack->begin(); iter.ptr() != nullptr; ++iter)
				std::cout << (*iter).value() << " ";
			std::cout << std::endl;
		}
	}
	else std::cout << "- no stack\n";

	std::cout << "\nFORWARD LIST\n\n";
	ForwardList * list = dynamic_cast<ForwardList *>(find_container(ContainerType::FORWARD_LIST));
	if (list) {
		if (list->empty())
			std::cout << "- empty\n";
		else {
			for (ForwardList::Iterator iter = list->begin(); iter.ptr() != nullptr; ++iter)
				std::cout << (*iter).value() << " ";
			std::cout << std::endl;
		}
	}
	else std::cout << "- no forward list\n";
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
		std::cout << "\nCouldn't open file: make sure you made save at least once\n";
		return;
	}

	int type, value;
	size_t size;
	AbstractQueue * container = nullptr;
	while (fin.good() && !fin.eof() && fin.peek() != EOF) {
		if (!(fin >> type >> size))
			break;
		switch (type) {
		case (int)ContainerType::DEQUE:
			container = new Deque;
			while (size--) {
				fin >> value;
				dynamic_cast<Deque *>(container)->push_back(Element(value));
			}
			break;
		case (int)ContainerType::STACK:
			container = new Stack;
			while (size--) {
				fin >> value;
				container->push(Element(value));
			}
			break;
		case (int)ContainerType::FORWARD_LIST:
			container = new ForwardList;
			while (size--) {
				fin >> value;
				dynamic_cast<ForwardList *>(container)->push_back(Element(value));
			}
			break;
		default:
			break;
		}
		insert_container(container);		
	}
	std::cout << "\nEverything was loaded successfuly\n";
	fin.close();
}