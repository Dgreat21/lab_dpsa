#pragma once

#include <memory>
#include <iostream>

#define LIST_NOTFREE nulldel

template	<typename TP>
struct		List
{
	TP		data;
	List	*next;
};

std::ostream& operator << (std::ostream &o, List<int> *p)
{
	if (!p)
		o << "null";
	else if (!p->next)
    	o << " " << p->data << " ";
	else
		o << " " << p->data << " -" << p->next;
	return o;
}

// TAKE DATA FROM THE BEGIN OF LIST
template	<typename T>
T			list_shift(List<T> **list)
{
	List<T>		*node;
	T			data;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	else if (!(*list))
		throw ("EXCEPTION: can't find list ((List *)list == NULL)");
	node = *list;
	(*list) = (*list)->next;
	data = node->data;
	delete node;
	return (data);
};

// DESTROY WHOLE LIST
// Delete every data with callback (if data dont have any heap pointers, just send NULL)
template	<typename T>
void		list_destroy(List<T> **list, void (*del)(T data))
{
	T			data;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	while (*list)
	{
		data = list_shift(list);
		if (del)
			del(data);
	}
	(*list) = NULL;
};

// PUSH DATA TO THE BEGIN OF LIST
template	<typename T>
void		list_unshift(T data, List<T> **list)
{
	List<T>		*node;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	node = new List<T>;
	node->data = data;
	node->next = (*list);
	*list = node;
};

// PUSH DATA TO THE END OF LIST
template	<typename T>
void		list_push(T data, List<T> **list)
{
	List<T>		*node;
	List<T>		*it;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	node = new List<T>;
	node->data = data;
	node->next = NULL;
	if (!(it = (*list)))
	{
		(*list) = node;
		return ;
	}
	while (it->next)
		it = it->next;
	it->next = node;
};

// STANDART DELITER CALLBACK FUNCTION TO NON-ALLOCATED TYPES
template	<typename T>
void		nulldel(T data)
{
	bzero(&data, sizeof(T));
	return ;
}
