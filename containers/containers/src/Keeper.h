#pragma once
#ifndef _KEEPER_H_
#define _KEEPER_H_

#include "Array.h"
#include "AbstractQueue.h"
#include "Deque.h"
#include "Stack.h"
#include "ForwardList.h"

#include "Element.h"
#include "IInput.h"

#include <iostream>
#include <fstream>

class Keeper
{
public:
	enum class ContainerType;

private:
	Array<AbstractQueue *> _containers;
	bool has_stack, has_deque, has_list;
	const static size_t CONTAINERS = 3;

	AbstractQueue * find_container(ContainerType type) const;

	void add_container(AbstractQueue * container);
	void delete_container(ContainerType type);

	void clear();

	enum process_menu { ENQUEUE = 1, DEQUEUE, OUTPUT, END };

public:
	Keeper();
	Keeper(const Keeper &) = delete;
	Keeper(Keeper &&) = delete;
	~Keeper();

	enum class ContainerType { STACK, DEQUE, FORWARD_LIST, NONE };

	void add();
	void remove();
	void save() const;
	void load();
	void output() const;
	void process();

	void run();
	enum menu { ADD = 1, DELETE, SAVE, LOAD, PROCESS, QUIT };

};

#endif