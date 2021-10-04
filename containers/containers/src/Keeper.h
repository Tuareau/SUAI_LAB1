#pragma once
#ifndef _KEEPER_H_
#define _KEEPER_H_

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
private:
	const static size_t CONTAINERS = 3;
	AbstractQueue * _containers[CONTAINERS];
	bool _has_stack, _has_deque, _has_list;

	enum class ContainerType { DEQUE = 1, STACK, FORWARD_LIST, NONE };
	AbstractQueue * find_container(ContainerType type) const;

	void add_container(AbstractQueue * container);
	void delete_container(ContainerType type);

	void clear();

	enum process_menu { ENQUEUE = 1, DEQUEUE, OUTPUT, END };

	void add();
	void remove();
	void save() const;
	void load();
	void output() const;
	void process();

	enum menu { ADD = 1, DELETE, SAVE, LOAD, PROCESS, QUIT };

public:
	Keeper();
	Keeper(const Keeper &) = delete;
	Keeper(Keeper &&) = delete;
	~Keeper();

	void run();

};

#endif