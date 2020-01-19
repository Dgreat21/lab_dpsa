#include "list.h"

List_Node*		List::get(u32_t index) {
	for (List_Node *it = this->root; it != 0x0; it = it->next()) {
		if (index-- == 0)
			return (it);
	}
	return (0x0);
}

List_Node*		List::get(bool (*cb)(const List_Node &list)) {
	for (List_Node *it = this->root; it != 0x0; it = it->next()) {
		if (cb(*it) == true)
			return (it);
	}
	return (0x0);
}

void			List::push_back(List_Node *node) {
	List_Node *it;

	if (this->is_empty()) {
		this->root = node;
		return ;
	}
	for (it = this->root; it->next() != 0x0; it = it->next()) ;
	it->next(node);
}

void			List::push_front(List_Node *node) {
	if (node) {
		node->next(this->root);
		this->root = node;
	}
}

void			List::push_front(List_Node *node, bool (*cb)(const List_Node &)) {
	List_Node	*it;

	if (this->is_empty()) {
		this->root = node;
	} else if (node) {
		for (it = this->root; it->next() && !cb(*(it->next())); it = it->next()) ;
		node->next(it->next());
		it->next(node);
	}
}

List			List::sublist(bool (*cb)(const List_Node &)) {
	List		list(0);
	List_Node	*it_s = this->root;
	List_Node	*it_d;
	List_Node	*new_l;

	while (it_s != 0x0) {
		if (cb(*it_s)) {
			if (list.is_empty()) {
				list.root = new List_Node(it_s);
				it_d = list.root;
			} else {
				new_l = new List_Node(it_s);
				it_d->next(new_l);
				it_d = it_d->next();
			}
		}
		it_s = it_s->next();
	}
	return (list);
}

List			List::sublist_cut(bool (*cb)(const List_Node &)) {
	List_Node	*prev = 0x0;
	List_Node	*next;
	List_Node	*current = this->root;
	List		list(0);
	List_Node	*it_sub = 0x0;

	while (current) {
		next = current->next();
		if (cb(current)) {
			if (prev == 0x0) {
				if (list.is_empty()) {
					list.root = current;
					it_sub = list.root;
				} else {
					it_sub = it_sub->next(current);
				}
				this->root = next;
			} else {
				if (list.is_empty()) {
					list.root = current;
					it_sub = list.root;
				} else {
					it_sub = it_sub->next(current);
				}
				prev->next(next);
			}
			it_sub->next(0x0);
		} else {
			prev = current;
		}
		current = next;
	}
	return (list);
}

void			List::print(const char *str) {
	if (this->is_empty() && str)
		printf("\"%s\": list is empty.\n", str);
	else {
		if (str)
			printf("\"%s\":\n", str);
		printf("  %7s | %2s/%2s/%4s | %s\n", "POLIS", "DD", "MM", "YYYY", "DGN");
		printf("  ==========================\n");
		for (List_Node *it = this->root; it != 0x0; it = it->next())
			it->print();
		printf("\n");
	}
}