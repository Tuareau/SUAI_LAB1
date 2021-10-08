#pragma once
#ifndef _KEEPER_HANDLER_H_
#define _KEEPER_HANDLER_H_

#include <random>

#include "AbstractQueue.h"
#include "IInput.h"
#include "Element.h"

class AbstractKeeperHandler
{
public:
	AbstractKeeperHandler() = default;
	virtual ~AbstractKeeperHandler() = default;

	const static size_t KEEPER_ACTIONS_COUNT = 6;
	enum class KeeperAction { ADD = 1, DELETE, SAVE, LOAD, PROCESS, QUIT };

	const static size_t CONTAINER_ACTIONS_COUNT = 4;
	enum class ContainerAction { ENQUEUE = 1, DEQUEUE, OUTPUT, QUIT };

	virtual KeeperAction get_keeper_action() const = 0;
	virtual AbstractQueue::ContainerType get_container_type() const = 0;

	virtual ContainerAction get_container_action() const = 0;
	virtual Element get_element() const = 0;
};

class IOKeeperHandler : public AbstractKeeperHandler
{
public:
	IOKeeperHandler() = default;
	~IOKeeperHandler() = default;

	virtual KeeperAction get_keeper_action() const override;
	virtual AbstractQueue::ContainerType get_container_type() const override;

	virtual ContainerAction get_container_action() const override;
	virtual Element get_element() const override;
};

class AutoTestKeeperHandler : public AbstractKeeperHandler
{
private:
	bool _added_containers[AbstractQueue::CONTAINERS_COUNT];

	size_t _keeper_actions_count[KEEPER_ACTIONS_COUNT];
	size_t _containers_actions_count[CONTAINER_ACTIONS_COUNT];
public:
	AutoTestKeeperHandler();
	~AutoTestKeeperHandler() = default;

	virtual KeeperAction get_keeper_action() const override;
	virtual AbstractQueue::ContainerType get_container_type() const override;

	virtual ContainerAction get_container_action() const override;
	virtual Element get_element() const override;
};

#endif