#include "list.h"
#include <string.h>
#include <stdio.h>

Date		set_yyyy_mm_dd(u32_t date) {
	u32_t	year;
	u32_t	month;
	u32_t	day;
	Date	date_obj;

	year = date / 10000;
	month = (date / 100) % 100;
	day = (date % 100);
	if (day > 31 || day == 0 || month == 0 || month > 12)
		throw ("invalid format for date");
	if (day > 28) {
		if (day == 31 && (
		month == FEB ||
		month == APR ||
		month == JUN ||
		month == SEP ||
		month == NOV))
			throw ("invalid format for date");
		if (month == FEB && year % 4)
			throw ("invalid format for date");
	}
	date_obj.year = year;
	date_obj.month = month;
	date_obj.day = day;
	return (date_obj);
}

u32_t	get_yyyy_mm_dd(Date date) {
	u32_t	date_int = 0;

	date_int += date.get_day();
	date_int += date.get_month() * 100;
	date_int += date.get_year() * 10000;
	return (date_int);
}

list_t			*list_node(void) {
	list_t		*node = new list_t;

	memset(node, 0x0, sizeof(list_t));
	return (node);
}

list_t			*list_node(u32_t id, u32_t diagnosis, u32_t date) {
	list_t		*node = new list_t;

	node->polis_id = id;
	node->date = set_yyyy_mm_dd(date);
	node->diagnosis_code = diagnosis;
	node->next = NULL;
	return (node);
}

list_t			*list_create_n(u64_t list_size) {
	list_t		*node = NULL;

	while(list_size--) {
		list_push_front(&node, list_node());
	}
	return (node);
}

void			list_node_delete(list_t **list) {
	delete *list;
	*list = NULL;
}

void			list_delete(list_t **list) {
	list_t		*node_del;
	list_t		*it = *list;

	while (it != NULL) {
		node_del = it;
		it = it->next;
		delete node_del;
	}
	*list = NULL;
}

void			list_node_print(list_t *node) {
	printf("  %.7u | %.2u/%.2u/%.4u | %2u\n", node->polis_id, 
	node->date.get_day(), node->date.get_month(), node->date.get_year(), node->diagnosis_code);
}

void			list_print(list_t *list, const char *name) {
	if (list == NULL)
		printf("\"%s\" list is empty.\n", name);
	else {
		printf("\"%s\":\n", name);
		printf("  %7s | %2s/%2s/%4s | %s\n", "POLIS", "DD", "MM", "YYYY", "DGN");
		printf("  ==========================\n");
		for (list_t *it = list; it != NULL; it = it->next)
			list_node_print(it);
		printf("\n");
	}
}

void			list_push_back(list_t **list, list_t *new_node) {
	list_t	*it;

	if (*list == NULL)
		*list = new_node;
	else {
		for (it = *list; it->next != NULL; it = it->next) ;
		it->next = new_node;
	}
}

void			list_push_front(list_t **list, list_t *new_node) {
	if (new_node) {
		new_node->next = *list;
		*list = new_node;
	}
}

void			list_push_front(list_t **list, list_t *new_node, int (*callback)(list_t *)) {
	list_t		*it;

	if (new_node) {
		if (*list == NULL) {
			*list = new_node;
			return ;
		}
		for (it = *list; it->next && callback(it->next); it = it->next) ;
		list_push_front(&it, new_node);
	}
}

list_t			*list_get_index(list_t *list, u64_t index) {
	while (index--) {
		if (list == NULL && index)
			throw ("List overflow by index");
		list = list->next;
	}
	return (list);
}

list_t			*list_get_callback(list_t *list, int (*cb)(list_t *)) {
	int		status = 0;

	while (list != NULL) {
		if (cb(list))
			return (list);
		list = list->next;
	}
	return (NULL);
}

list_t		*list_node_dup(list_t *node) {
	list_t	*duplicate;

	duplicate = list_node(node->polis_id, node->diagnosis_code, get_yyyy_mm_dd(node->date));
	return (duplicate);
}

list_t		*list_sublist(list_t *list, int (*callback)(list_t *)) {
	list_t		*sublist_b = NULL;
	list_t		*sublist_it = NULL;

	while (list != NULL) {
		if (callback(list)) {
			if (sublist_b == NULL) {
				sublist_b = list_node_dup(list);
				sublist_it = sublist_b;
			} else {
				sublist_it->next = list_node_dup(list);
				sublist_it = sublist_it->next;
			}
		}
		list = list->next;
	}
	return (sublist_b);
}

list_t		*list_sublist_cut(list_t **list, int (*cb)(list_t *)) {
	list_t		*prev = NULL;
	list_t		*next;
	list_t		*current = *list;
	list_t		*sublist_b = NULL;
	list_t		*sublist_it = NULL;

	while (current) {
		next = current->next;
		if (cb(current)) {
			if (prev == NULL) {
				if (sublist_b == NULL) {
					sublist_b = current;
					sublist_it = sublist_b;
				} else {
					sublist_it->next = current;
					sublist_it = sublist_it->next;
				}
				*list = next;
			} else {
				if (sublist_b == NULL) {
					sublist_b = current;
					sublist_it = sublist_b;
				} else {
					sublist_it->next = current;
					sublist_it = sublist_it->next;
				}
				prev->next = next;
			}
			sublist_it->next = NULL;
		} else {
			prev = current;
		}
		current = next;
	}
	return (sublist_b);
}
