
#include "list.h"
#include <memory>

template	<>
int			list_shift(List<int> **list)
{
	List<int>		*node;
	int				data;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	else if (!(*list))
		throw ("EXCEPTION: can't find list ((List *)list == NULL)");
	node = *list;
	(*list) = (*list)->next;
	data = node->data;
	delete node;
	return (data);
}

template	<>
void		list_destroy(List<int> **list, void (*del)(int data))
{
	int			data;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	while (*list)
	{
		data = list_shift(list);
		if (del)
			del(data);
	}
	(*list) = NULL;
}

template	<>
void		list_unshift(int data, List<int> **list)
{
	List<int>		*node;

	if (!list)
		throw ("EXCEPTION: can't find list location ((List **)list == NULL)");
	node = new List<int>;
	node->data = data;
	node->next = (*list);
	*list = node;
}

template	<>
void		nulldel(int data)
{
	bzero(&data, sizeof(int));
	return ;
}
