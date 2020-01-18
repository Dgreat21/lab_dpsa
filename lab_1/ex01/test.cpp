#include "list.h"
#include <stdio.h>

int	list_2_cb(list_t *ls) {
	if (ls->polis_id > 100 && ls->polis_id < 200)
		return (1);
	return (0);
}

int	list_3_cb(list_t *ls) {
	if (ls->polis_id < 100)
		return (1);
	return (0);
}

int	list_4_cb(list_t *ls) {
	if (ls->polis_id > 200)
		return (1);
	return (0);
}

int main(void) {
	list_t		*list_1 = list_create_n(2);
	Date		null_date;

	list_t		*list_ind;

	list_ind = list_get_index(list_1, 0);
	list_ind->polis_id = 1;
	list_ind = list_get_index(list_1, 1);
	list_ind->polis_id = 2;
	list_ind = NULL;

	list_push_back(&list_1, list_node(101, 0, 20200101));
	list_push_back(&list_1, list_node(102, 0, 19420909));
	list_push_back(&list_1, list_node(103, 0, 20070707));
	list_push_back(&list_1, list_node(201, 0, 20070707));
	list_push_back(&list_1, list_node(202, 0, 20070707));
	list_push_back(&list_1, list_node(203, 0, 20070707));
	list_push_back(&list_1, list_node(204, 0, 20070707));

	list_t		*list_4 = list_sublist(list_1, list_4_cb);
	list_t		*list_2 = list_sublist_cut(&list_1, list_2_cb);
	list_t		*list_3 = list_sublist_cut(&list_1, list_3_cb);

	list_print(list_1, "list_1");
	list_print(list_2, "list_2");
	list_print(list_3, "list_3");
	list_print(list_4, "list_4");
}