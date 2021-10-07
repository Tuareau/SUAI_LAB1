#pragma once
#ifndef _KEEPER_H_
#define _KEEPER_H_

#include "AbstractQueue.h"
#include "ContainersFactory.h"

#include "Element.h"
#include "IInput.h"

#include <iostream>
#include <fstream>

class Keeper
{
private:
	ContainersFactory _factory;
	AbstractQueue * _containers[AbstractQueue::CONTAINERS_COUNT];

	//AbstractQueue * find_container(AbstractQueue::ContainerType type) const;
	void insert_container(AbstractQueue * container);
	void remove_container(AbstractQueue::ContainerType type);

	template<class Container>
	void output_container(const Container & c, const std::ostream & os);

	void clear();

	//enum process_menu { ENQUEUE = 1, DEQUEUE, OUTPUT, END };
	//enum menu { ADD = 1, DELETE, SAVE, LOAD, PROCESS, QUIT };

public:
	Keeper();
	Keeper(const Keeper &) = delete;
	Keeper(Keeper &&) = delete;
	~Keeper();

	void add_container(AbstractQueue::ContainerType type);
	void remove(AbstractQueue::ContainerType type);
	void save() const;
	void load();
	void output() const;
	void process();

	//void run();

};

template <class Container>
void Keeper::output_container(const Container & c, const std::ostream & os) {
	for (const auto iter = c.cbegin(); iter.ptr() != nullptr; ++iter)
		os << (*iter).value() << " ";
	os << std::endl;
}

#endif