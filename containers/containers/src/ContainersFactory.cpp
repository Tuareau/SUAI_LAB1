#include "ContainersFactory.h"

AbstractQueue * ContainersFactory::make_container(AbstractQueue::ContainerType type) {
	AbstractQueue * container = nullptr;
	if (type == AbstractQueue::ContainerType::DEQUE)
		container = new Deque;
	if (type == AbstractQueue::ContainerType::STACK)
		container = new Stack;
	if (type == AbstractQueue::ContainerType::FORWARD_LIST)
		container = new ForwardList;
	return container;
}