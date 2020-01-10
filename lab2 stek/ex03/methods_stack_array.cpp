#include "stack_arr.h"
#include <iostream>
#include "linux_header.h"

template	<>
int			StackAR<int>::top(void)
{
	if (this->sp == 0)
		throw("STACK EMPTY");
	return (this->array[this->sp - 1]);
}

template <>
StackAR<int>::StackAR(void)
{
	this->sp = 0;
	this->array = new int[STACKARR_BLKSZ];
	this->allocated = STACKARR_BLKSZ;
}

template <>
StackAR<int>::~StackAR(void)
{
	this->sp = 0;
	delete this->array;
	this->allocated = 0;
}

template <>
ulong	StackAR<int>::size(void)
{
	return (this->sp);
}

template <>
void	StackAR<int>::push(int num)
{
	int			*ptr;

	if (this->sp <= this->allocated)
		this->array[this->sp++] = num;
	else
	{
		ptr = new int[this->allocated + STACKARR_BLKSZ];
		this->allocated += STACKARR_BLKSZ;
		memcpy(ptr, this->array, this->allocated * sizeof(int));
		delete this->array;
		this->array = ptr;
		this->array[this->sp++] = num;
	}
}

template <>
int		StackAR<int>::pop(void)
{
	int			*ptr;
	int			item;

	if (this->sp == 0)
		throw("Stack already empty!");
	this->sp -= 1;
	item = this->array[this->sp];
	if ((this->sp > STACKARR_BLKSZ) &&
	(this->allocated - (STACKARR_BLKSZ * 2) > this->sp))
	{
		ptr = new int[this->allocated - STACKARR_BLKSZ];
		this->allocated -= STACKARR_BLKSZ;
		memcpy(ptr, this->array, this->sp * sizeof(int));
		delete (this->array);
		this->array = ptr;
	}
	return (item);
}

template	<>
void		StackAR<int>::print(void)
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
