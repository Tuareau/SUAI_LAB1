#pragma once
#ifndef _CONTAINERS_FACTORY_H_
#define _CONTAINERS_FACTORY_H_

#include "AbstractQueue.h"
#include "Deque.h"
#include "Stack.h"
#include "ForwardList.h"

class ContainersFactory
{
public:
	ContainersFactory() = default;
	ContainersFactory(const ContainersFactory &) = delete;
	ContainersFactory(ContainersFactory &&) = delete;
	~ContainersFactory() = default;

	AbstractQueue * make_container(AbstractQueue::ContainerType type);
};

#endif