#include "Keeper.h"

Keeper::Keeper(AbstractKeeperHandler * handler) : _handler(handler) {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i)
		_containers[i] = nullptr;
}

Keeper::~Keeper() {
	clear();
	delete _handler;
}

void Keeper::clear() {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		delete _containers[i];
		_containers[i] = nullptr;
	}
}

bool Keeper::empty() const {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		if (_containers[i])
			return false;
	}
	return true;
}

void Keeper::run() {
	auto action = _handler->get_keeper_action();
	while (action != AbstractKeeperHandler::KeeperAction::QUIT) {
		if (action == AbstractKeeperHandler::KeeperAction::ADD)
			add_container();
		if (action == AbstractKeeperHandler::KeeperAction::DELETE)
			remove_container();
		if (action == AbstractKeeperHandler::KeeperAction::LOAD)
			load_containers();
		if (action == AbstractKeeperHandler::KeeperAction::SAVE)
			save_containers();
		if (action == AbstractKeeperHandler::KeeperAction::PROCESS)
			process_containers();
		action = _handler->get_keeper_action();
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

void Keeper::erase_container(AbstractQueue::ContainerType type) {
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

void Keeper::add_container() {
	std::cout << "\n\tADD CONTAINER\n";
	AbstractQueue::ContainerType type = _handler->get_container_type();
	AbstractQueue * container = _factory.make_container(type);
	insert_container(container);
}

void Keeper::remove_container() {
	std::cout << "\n\tDELETE CONTAINER\n";
	AbstractQueue::ContainerType type = _handler->get_container_type();
	erase_container(type);
}

void Keeper::process_containers() {
	auto action = _handler->get_container_action();
	while (action != AbstractKeeperHandler::ContainerAction::QUIT) {
		if (action == AbstractKeeperHandler::ContainerAction::ENQUEUE)
			process_enqueue();
		if (action == AbstractKeeperHandler::ContainerAction::DEQUEUE)
			process_dequeue();
		if (action == AbstractKeeperHandler::ContainerAction::OUTPUT)
			print_containers();
		action = _handler->get_container_action();
	}
}

void Keeper::process_enqueue() {
	if (!empty()) {
		const auto element = _handler->get_element();
		for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i)
			if (_containers[i])
				_containers[i]->push(element);
	}
	else std::cout << "\nNo containers to push to\n";
}

void Keeper::process_dequeue() {
	if (!empty()) {
		for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i)
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
	else std::cout << "\nNo container to pop from\n";
}

void Keeper::print_containers() const {
	for (size_t i = 0; i < AbstractQueue::CONTAINERS_COUNT; ++i) {
		print_type(static_cast<AbstractQueue::ContainerType>(i));
		std::cout << std::endl;
		if (_containers[i])
			if (_containers[i]->empty())
				std::cout << " - empty\n";
			else
				_containers[i]->print(std::cout);
		else std::cout << " - no container\n";
	}
}

void Keeper::print_type(AbstractQueue::ContainerType type) const {
	if (type == AbstractQueue::ContainerType::DEQUE)
		std::cout << "\nDEQUE\n";
	if (type == AbstractQueue::ContainerType::STACK)
		std::cout << "\nSTACK\n";
	if (type == AbstractQueue::ContainerType::FORWARD_LIST)
		std::cout << "\nFORWARD LIST\n";
}

void Keeper::save_containers() const {
	std::ofstream fout("containers.txt", std::ios_base::trunc | std::ios_base::out);
	for (size_t index = 0; index < AbstractQueue::CONTAINERS_COUNT; ++index) {
		if (_containers[index]) {
			fout << index << " ";
			fout << _containers[index]->size() << "\n";
			_containers[index]->print(fout);
		}
	}
	std::cout << "\nEverything was saved successfuly\n";
	fout.close();
}

void Keeper::load_containers() {
	std::ifstream fin("containers.txt", std::ios_base::in);
	clear();
	if (!fin.good()) {
		std::cout << "\nCouldn't open file: make sure you made save at least once\n";
		return;
	}

	int id, value; size_t size;
	while (fin.good() && !fin.eof() && fin.peek() != EOF) {
		if (!(fin >> id >> size))
			break;
		auto type = static_cast<AbstractQueue::ContainerType>(id);
		auto container = _factory.make_container(type);
		while (size--) {
			if (fin >> value) {
				if (type == AbstractQueue::ContainerType::DEQUE)
					dynamic_cast<Deque *>(container)->push_back(Element(value));
				else if (type == AbstractQueue::ContainerType::FORWARD_LIST)
					dynamic_cast<ForwardList *>(container)->push_back(Element(value));
				else container->push(Element(value));
			}
			else break;
		}
		insert_container(container);	
	}
	std::cout << "\nEverything was loaded successfuly\n";
	fin.close();
}