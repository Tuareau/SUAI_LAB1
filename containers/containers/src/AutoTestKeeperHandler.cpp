#include "KeeperHandler.h"

AutoTestKeeperHandler::AutoTestKeeperHandler() {
	std::srand(unsigned int(std::time(nullptr)));
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		_added_containers[i] = false;
	}
	for (size_t i = 0; i < CONTAINER_ACTIONS_COUNT; ++i) {
		_containers_actions_count[i] = 0;
	}
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		_keeper_actions_count[i] = 0;
	}
}

AbstractKeeperHandler::KeeperAction AutoTestKeeperHandler::get_keeper_action() const {
	// TODO
	//return KeeperAction::ADD;
	//return KeeperAction::DELETE;
	//return KeeperAction::LOAD;
	//return KeeperAction::SAVE;
	//return KeeperAction::PROCESS;
	return KeeperAction::QUIT;
}

AbstractQueue::ContainerType AutoTestKeeperHandler::get_container_type() const {

	// TODO
	//return AbstractQueue::ContainerType::DEQUE;
	//return AbstractQueue::ContainerType::STACK;
	//return AbstractQueue::ContainerType::FORWARD_LIST;
	return AbstractQueue::ContainerType::NONE;
}

AbstractKeeperHandler::ContainerAction AutoTestKeeperHandler::get_container_action() const {

	// TODO
	//return ContainerAction::ENQUEUE;
	//return ContainerAction::DEQUEUE;
	//return ContainerAction::OUTPUT;
	return ContainerAction::QUIT;
}

Element AutoTestKeeperHandler::get_element() const {
	const auto value = std::rand() % 10;
	return Element(value);
}