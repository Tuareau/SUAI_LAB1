#pragma once
#ifndef _KEEPER_H_
#define _KEEPER_H_

#include "Array.h"
#include "AbstractQueue.h"
#include "Deque.h"
#include "Stack.h"
#include "ForwardList.h"

#include "IInput.h"

#include <iostream>
#include <fstream>

class Keeper
{
private:
	Array<AbstractQueue *> _containers;
	bool has_stack, has_deque, has_list;
	const static size_t CONTAINERS = 3;

	void process_stack();
	void process_deque();
	void process_list();
	void output() const;

	void add_container(AbstractQueue * container);
	enum class ContainerType;
	void delete_container(ContainerType type);

public:
	Keeper();
	Keeper(const Keeper &) = delete;
	Keeper(Keeper &&) = delete;
	~Keeper() = default;

	enum class ContainerType { STACK, DEQUE, FORWARD_LIST, NONE };

	void add();
	void remove();
	void save() const;
	void load();
	void process();

	void run();
	enum menu { ADD = 1, DELETE, SAVE, LOAD, PROCESS, QUIT };

};

#endif