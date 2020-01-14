#pragma once

#include <iostream>

#ifndef ULONG_TPDF
# define UNLONG_TPDF
typedef unsigned long	ulong;
#endif

// Standart size of block for allocating new memomry for array used in stack
# define STACKARR_BLKSZ	64

template	<typename T>
class		StackAR
{
	private:
	ulong	allocated; // Size of allocated array
	ulong	sp; // Stack top index: [0 - allocated]
	T		*array; // Pointer for stack

	public:
	StackAR(void);
	~StackAR(void);
	
	void	push(T);
	T		pop(void);
	ulong	size(void);
	void	print(void);
	T		top(void);
};

template	<typename T>
T			StackAR<T>::top(void)
{
	if (this->sp == 0)
		throw("STACK EMPTY");
	return (this->array[this->sp - 1]);
}

template <typename T>
StackAR<T>::StackAR(void)
{
	this->sp = 0;
	this->array = new T[STACKARR_BLKSZ];
	this->allocated = STACKARR_BLKSZ;
}

template <typename T>
StackAR<T>::~StackAR(void)
{
	this->sp = 0;
	delete this->array;
	this->allocated = 0;
}

template <typename T>
ulong	StackAR<T>::size(void)
{
	return (this->sp);
}

template <typename T>
void	StackAR<T>::push(T num)
{
	T			*ptr;

	if (this->sp <= this->allocated)
		this->array[this->sp++] = num;
	else
	{
		ptr = new T[this->allocated + STACKARR_BLKSZ];
		this->allocated += STACKARR_BLKSZ;
		memcpy(ptr, this->array, this->allocated * sizeof(T));
		delete this->array;
		this->array = ptr;
		this->array[this->sp++] = num;
	}
}

template <typename T>
T		StackAR<T>::pop(void)
{
	T			*ptr;
	T			item;

	if (this->sp == 0)
		throw("Stack already empty!");
	this->sp -= 1;
	item = this->array[this->sp];
	if ((this->sp > STACKARR_BLKSZ) &&
	(this->allocated - (STACKARR_BLKSZ * 2) > this->sp))
	{
		ptr = new T[this->allocated - STACKARR_BLKSZ];
		this->allocated -= STACKARR_BLKSZ;
		memcpy(ptr, this->array, this->sp * sizeof(T));
		delete[] (this->array);
		this->array = ptr;
	}
	return (item);
}

template	<typename T>
void		StackAR<T>::print(void)
{
	if (this->sp == 0)
	{
		std::cout << "STACK EMPTY!\n";
		return ;
	}
	for (ulong i = this->sp; i > 0;)
	{
		if (i == this->sp)
			std::cout << ">>: " << this->array[--i] << std::endl;
		else
			std::cout << "  : " << this->array[--i] << std::endl;
	}
}
