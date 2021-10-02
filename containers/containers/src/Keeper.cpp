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