#include "Keeper.h"

Keeper::Keeper() {
	_containers.resize(CONTAINERS, nullptr);
	has_stack = has_deque = has_list = false;
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
					std::cout << "Stack was added successfuly\n";
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
	using std::cin;
	using std::endl;
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
	using std::cin;
	using std::endl;
	cout << "\n\tADD CONTAINER\n";
	int choice = 0;
	cout << "\nWhat type of container:\n";
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
		cout << "Wrong choice, try again later\n";
	}

	system("cls");
	switch (choice) {
	case (int)ContainerType::DEQUE:
		AbstractQueue * deque = new Deque;


		break;
	case DELETE:


		break;
	case SAVE:


		break;
	case LOAD:


		break;
	case PROCESS:


		break;
	case QUIT:
		break;
	default:
		break;
	}
}