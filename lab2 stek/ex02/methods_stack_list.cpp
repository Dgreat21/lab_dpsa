#include "stack_list.h"
#include <iostream>

template 	<>
StackL<int>::StackL(void)
{
	this->node = NULL;
	this->size_ = 0;
	this->del = nulldel;
}

template 	<>
StackL<int>::StackL(void (*del)(int))
{
	this->node = NULL;
	this->size_ = 0;
	this->del = del;
}

template 	<>
StackL<int>::~StackL(void)
{
	list_destroy<int>(&(this->node), this->del);
}

template 	<>
ulong		StackL<int>::size(void)
{
	return(this->size_);
}

template	<>
void		StackL<int>::push(int data)
{
	list_unshift(data, &(this->node));
	this->size_ += 1;
}

template	<>
int			StackL<int>::pop(void)
{
	if (this->size_ == 0)
		throw("Stack already empty!");
	this->size_ -= 1;
	return (list_shift(&(this->node)));
}

template	<>
int			StackL<int>::top(void)
{
	if (this->size_ == 0)
		throw("STACK EMPTY");
	return (this->node->data);
}

template	<>
void		StackL<int>::print(void)
{
	List<int>*		lst = this->node;

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
