#pragma once

#include "list.h"
#include <iostream>

#ifndef ULONG_TPDF
# define UNLONG_TPDF
typedef unsigned long	ulong;
#endif

template 	<typename T>
class		StackL
{
	private:
	List<T>		*node;
	ulong		size_;
	void		(*del)(T);

	public:
	StackL(void);
	StackL(void (*del)(T));
	~StackL(void);

	void		push(T);
	T			pop(void);
	ulong		size(void);
	void		print(void);
	T			top(void);
};

template 	<typename T>
StackL<T>::StackL(void)
{
	this->node = NULL;
	this->size_ = 0;
	this->del = nulldel;
}

template 	<typename T>
StackL<T>::StackL(void (*del)(T))
{
	this->node = NULL;
	this->size_ = 0;
	this->del = del;
}

template 	<typename T>
StackL<T>::~StackL(void)
{
	list_destroy<T>(&(this->node), this->del);
}

template 	<typename T>
ulong		StackL<T>::size(void)
{
	return(this->size_);
}

template	<typename T>
void		StackL<T>::push(T data)
{
	list_unshift(data, &(this->node));
	this->size_ += 1;
}

template	<typename T>
T			StackL<T>::pop(void)
{
	if (this->size_ == 0)
		throw("Stack already empty!");
	this->size_ -= 1;
	return (list_shift(&(this->node)));
}

template	<typename T>
T			StackL<T>::top(void)
{
	if (this->size_ == 0)
		throw("STACK EMPTY");
	return (this->node->data);
}

template	<typename T>
void		StackL<T>::print(void)
{
	List<T>*		lst = this->node;

	if (lst)
	{
		std::cout << ">>: " << lst->data << std::endl;
		lst = lst->next;
		while (lst)
		{
			std::cout << "  : " << lst->data << std::endl;
			lst = lst->next;
		}
	}
	else
		std::cout << "STACK EMPTY!\n";
}
