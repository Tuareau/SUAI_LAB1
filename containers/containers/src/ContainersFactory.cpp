#include "ContainersFactory.h"

AbstractQueue * ContainersFactory::make_container(AbstractQueue::ContainerType type) {
	AbstractQueue * container = nullptr;
	switch (type) {
	case AbstractQueue::ContainerType::DEQUE:
		container = new Deque;
		break;
	case AbstractQueue::ContainerType::STACK:
		container = new Stack;
		break;
	case AbstractQueue::ContainerType::FORWARD_LIST:
		container = new ForwardList;
		break;
	default:
		throw std::logic_error("ContainersFactory::make_container(): container type mismatch in switch");
		break;
	}
	return container;
}