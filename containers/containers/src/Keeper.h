#pragma once
#ifndef _KEEPER_H_
#define _KEEPER_H_

#include "AbstractQueue.h"
#include "ContainersFactory.h"
#include "KeeperHandler.h"

#include <iostream>
#include <fstream>

class Keeper
{
private:
	ContainersFactory _factory;
	AbstractQueue * _containers[AbstractQueue::CONTAINERS_COUNT];
	AbstractKeeperHandler * _handler;

	void insert_container(AbstractQueue * container);
	void erase_container(AbstractQueue::ContainerType type);

	void print_type(AbstractQueue::ContainerType type) const;

	bool empty() const;
	void clear();

	void add_container();
	void remove_container();

	void process_enqueue();
	void process_dequeue();

	void save_containers() const;
	void load_containers();

	void print_containers() const;
	void process_containers();

public:
	Keeper() = delete;
	explicit Keeper(AbstractKeeperHandler * handler);
	Keeper(const Keeper &) = delete;
	Keeper(Keeper &&) = delete;
	~Keeper();

	void run();
};

#endif