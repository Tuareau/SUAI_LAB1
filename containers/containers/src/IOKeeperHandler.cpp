#include "KeeperHandler.h"

AbstractKeeperHandler::KeeperAction IOKeeperHandler::get_keeper_action() const {
	using std::cout;
	cout << "\n\tKEEPER\n";
	cout << "\n\tKeeper object has information about containers:\n";
	cout << "\n\t- Stack\n\t- Deque\n\t- Forward List\n";
	cout << "\n\tAny of these can be added once\n";

	int choice = 0;
	while (choice != int(AbstractKeeperHandler::KeeperAction::QUIT)) {
		cout << "\nChoose action:\n";
		cout << "1 - add container\n";
		cout << "2 - delete container\n";
		cout << "3 - load from file\n";
		cout << "4 - save in file\n";
		cout << "5 - work with containers\n";
		cout << "6 - quit\n";

		IInput<int> input;
		choice = input.getValueFromInput();
		if (choice < 0 || choice > 6) {
			system("cls");
			cout << "\nWrong choice, try again\n";
			continue;
		}

		system("cls");
		if (choice == 1) return KeeperAction::ADD;
		if (choice == 2) return KeeperAction::DELETE;
		if (choice == 3) return KeeperAction::LOAD;
		if (choice == 4) return KeeperAction::SAVE;
		if (choice == 5) return KeeperAction::PROCESS;
	}
	return KeeperAction::QUIT;
}

AbstractQueue::ContainerType IOKeeperHandler::get_container_type() const {
	using std::cout;
	cout << "\nWhat type of container:\n";
	cout << "1 - deque\n";
	cout << "2 - stack\n";
	cout << "3 - forward list\n";
	cout << "4 - cancel\n";

	int choice = IInput<int>().getValueFromInput();
	if (choice < (int)AbstractQueue::ContainerType::DEQUE
		|| choice > (int)AbstractQueue::ContainerType::NONE) {
		system("cls");
		cout << "\nWrong choice, canceled\n";
		return AbstractQueue::ContainerType::NONE;
	}

	system("cls");
	if (choice == 1) return AbstractQueue::ContainerType::DEQUE;
	if (choice == 2) return AbstractQueue::ContainerType::STACK;
	if (choice == 3) return AbstractQueue::ContainerType::FORWARD_LIST;
	return AbstractQueue::ContainerType::NONE;
}

AbstractKeeperHandler::ContainerAction IOKeeperHandler::get_container_action() const {
	using std::cout;
	cout << "\n\tWORK WITH CONTAINERS\n";
	int choice = 0;
	while (choice != int(ContainerAction::QUIT)) {
		cout << "\nNote that we'll work with all containers at one time:\n";
		cout << "\nContainers manipulations:\n";
		cout << "1 - add element\n";
		cout << "2 - delete element\n";
		cout << "3 - output\n";
		cout << "4 - cancel\n";

		IInput<int> input;
		choice = input.getValueFromInput();
		if (choice < int(ContainerAction::ENQUEUE)
			|| choice > int(ContainerAction::QUIT)) {
			system("cls");
			cout << "\nWrong choice, try again\n";
			continue;
		}

		system("cls");
		if (choice == 1) return ContainerAction::ENQUEUE;
		if (choice == 2) return ContainerAction::DEQUEUE;
		if (choice == 3) return ContainerAction::OUTPUT;
	}
	return ContainerAction::QUIT;
}

Element IOKeeperHandler::get_element() const {
	using std::cout;
	IInput<int> input;
	cout << "\nPut your element: ";
	const auto value = input.getValueFromInput();
	return Element(value);
}