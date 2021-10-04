#pragma once
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdexcept>

template <typename ValueType>
class Array
{
private:
	ValueType * array_alloc;
	size_t size;
	size_t used;
	static const size_t PORTION = 5;

	void createArray(size_t count = PORTION, ValueType value = ValueType());
	void reallocArray(size_t count = PORTION, ValueType value = ValueType());
	void clearArray();

public:
	Array();
	explicit Array(std::initializer_list<ValueType> values);
	explicit Array(int count);
	~Array();

	ValueType & operator[](size_t i);
	const ValueType operator[](size_t i) const;
	ValueType & operator=(std::initializer_list<ValueType> values);

	void resize(size_t count, ValueType value = ValueType());

	class Iterator
	{
	private:
		ValueType * pointer;
	public:
		Iterator() : pointer(NULL) {}
		explicit Iterator(ValueType * pointer) : pointer(pointer) {}
		Iterator(const Iterator & iter) : pointer(iter.pointer) {}
		~Iterator() {}

		Iterator & operator=(const Iterator & iter)
		{
			pointer = iter.pointer;
			return *this;
		}

		Iterator & operator++()
		{
			++pointer;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator it(pointer++);
			return it;
		}

		Iterator & operator--()
		{
			--pointer;
			return *this;
		}

		bool operator!=(const Iterator & iter)
		{
			return pointer != iter.pointer;
		}

		bool operator<(const Iterator & iter)
		{
			return pointer < iter.pointer;
		}

		bool operator>(const Iterator & iter)
		{
			return pointer > iter.pointer;
		}

		bool operator==(const Iterator & iter)
		{
			return pointer == iter.pointer;
		}

		ValueType & operator*()
		{
			return *pointer;
		}
	};

	Iterator begin() { return Iterator(array_alloc); }
	Iterator end() { return Iterator(array_alloc + used); }
};

template <typename ValueType>
Array<ValueType>::Array() : array_alloc(nullptr), size(0), used(0)
{}

template <typename ValueType>
Array<ValueType>::Array(std::initializer_list<ValueType> values)
{
	createArray(values.size(), ValueType());

	typename std::initializer_list<ValueType>::iterator list_iter;
	Iterator array_iter = this->begin();

	for (list_iter = values.begin(); list_iter != values.end(); list_iter++)
		*array_iter++ = *list_iter;
}

template <typename ValueType>
Array<ValueType>::Array(int count)
{
	if (count >= 0)
		createArray(count, ValueType());
}

template <typename ValueType>
void Array<ValueType>::createArray(size_t count, ValueType value)
{
	size_t new_size = count + PORTION;
	array_alloc = new ValueType[new_size];
	for (size_t i = 0; i < new_size; i++)
		array_alloc[i] = value;
	this->size = new_size;
	used = count;
}

template <typename ValueType>
Array<ValueType>::~Array()
{
	clearArray();
}

template <typename ValueType>
void Array<ValueType>::clearArray()
{
	delete[] array_alloc;
	array_alloc = nullptr;
	size = used = 0;
}

template<typename ValueType>
void Array<ValueType>::resize(size_t count, ValueType value)
{
	clearArray();
	createArray(count, value);
}

template <typename ValueType>
ValueType & Array<ValueType>::operator[](size_t i)
{
	if (i < 0 || i >= used)
		throw std::out_of_range("Error: Array's indexation was out of bounds\n");
	return array_alloc[i];
}

template<typename ValueType>
const ValueType Array<ValueType>::operator[](size_t i) const
{
	if (i < 0 || i >= used)
		throw std::out_of_range("Error: Array's indexation was out of bounds\n");
	return array_alloc[i];
}

template<typename ValueType>
ValueType & Array<ValueType>::operator=(std::initializer_list<ValueType> values)
{
	delete[] array_alloc;
	createArray(values.size(), ValueType());

	typename std::initializer_list<ValueType>::iterator list_iter;
	Iterator array_iter = this->begin();

	for (list_iter = values.begin(); list_iter != values.end(); list_iter++)
		*array_iter++ = *list_iter;
}

template <typename ValueType>
void Array<ValueType>::reallocArray(size_t count, ValueType value)
{
	ValueType * new_alloc = new ValueType[size + count];
	for (int i = 0; i < size; i++)
		new_alloc[i] = array_alloc[i];
	for (int i = size; i < size + count; i++)
		new_alloc[i] = value;

	delete array_alloc;
	array_alloc = new_alloc;
	size += count;
}

#endif