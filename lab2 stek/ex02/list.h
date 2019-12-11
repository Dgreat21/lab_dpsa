#pragma once

# define LIST_NOTFREE nulldel

template	<typename TP>
struct		List
{
	TP		data;
	List	*next;
};

// DESTROY WHOLE LIST
// Delete every data with callback (if data dont have any heap pointers, just send NULL)
template	<typename T>
void		list_destroy(List<T> **list, void (*del)(T data));

// PUSH DATA TO THE BEGIN OF LIST
template	<typename T>
void		list_unshift(int data, List<T> **list);

// TAKE DATA FROM THE BEGIN OF LIST
template	<typename T>
int			list_shift(List<T> **list);

// STANDART DELITER CALLBACK FUNCTION TO NON-ALLOCATED TYPES
template	<typename T>
void		nulldel(T data);
