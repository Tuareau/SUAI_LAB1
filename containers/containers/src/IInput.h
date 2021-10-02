#pragma once
#ifndef _IINPUT_H_
#define _IINPUT_H_

#include <iostream>

template <typename ValueType>
class IInput
{
public:
	enum class mode { clear, skip };

	void clearInput() const
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	ValueType getValueFromInput(mode input_mode = mode::clear) const
	{
		using std::cin;
		using std::cout;
		using std::endl;

		ValueType value = ValueType();
		while (!(cin >> value))
		{
			cout << "\nInvalid input, try again\n";
			clearInput();
		}
		cout << "- " << (typeid(value)).name() << " given" << endl;
		if (input_mode == mode::clear)
			clearInput();
		return value;
	}
};

template <>
class IInput<char *>
{
private:
	const static size_t BUFF = 100;
public:
	enum class mode { clear, skip };

	void clearInput() const
	{
		if (!std::cin)
			std::cin.clear();
		while (std::cin.get() != '\n');
	}

	char * getValueFromInput(mode input_mode = mode::clear, size_t size = BUFF) const
	{
		using std::cin;
		using std::cout;
		using std::endl;

		char * str = new char[size];
		while (!(cin >> str))
		{
			cout << "\nInvalid input, try again\n";
			clearInput();
		}
		cout << "- string for " << (typeid(str)).name() << " given" << endl;
		if (input_mode == mode::clear)
			clearInput();
		return str;
	}
};

#endif