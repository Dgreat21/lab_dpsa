#ifndef LIST_H
# define LIST_H

#include <stdint.h>
#include <stdio.h>

typedef uint64_t	u64_t;
typedef uint32_t	u32_t;
typedef int64_t		i64_t;
typedef int32_t		i32_t;

namespace Date {
	const u32_t		JAN = 1;
	const u32_t		FEB = 2;
	const u32_t		MAR = 3;
	const u32_t		APR = 4;
	const u32_t		MAY = 5;
	const u32_t		JUN = 6;
	const u32_t		JUL = 7;
	const u32_t		AUG = 8;
	const u32_t		SEP = 9;
	const u32_t		OCT = 10;
	const u32_t		NOV = 11;
	const u32_t		DEC = 12;

	typedef	u32_t	date_t;

	inline u32_t	get_year(date_t date) {
		return (date / 10000);
	}

	inline u32_t	get_month(date_t date) {
		return (date / 100 % 100);
	}

	inline u32_t	get_dat(date_t date) {
		return (date % 100);
	}
}

class	List_Node {
private:
	List_Node		*_next;
public:
	Date::date_t	date;
	u32_t			polis_id;
	u32_t			diagnosis;

	List_Node(void) {
		this->_next = 0x0;
		this->date = 0x0;
		this->polis_id = 0x0;
		this->diagnosis = 0x0;
	}
	List_Node(u32_t id, u32_t diagnosis, Date::date_t date) {
		this->_next = 0x0;
		this->date = date;
		this->diagnosis = diagnosis;
		this->polis_id = id;
	}
	List_Node(List_Node *list) {
		this->date = list->date;
		this->diagnosis = list->diagnosis;
		this->polis_id = list->polis_id;
		this->_next = 0x0;
	}

	u32_t		get_date(void) {
		return this->date;
	}
	u32_t		get_p_id(void) {
		return this->polis_id;
	}
	u32_t		get_d_id(void) {
		return this->diagnosis;
	}
	List_Node	*next(void) {
		return this->_next;
	}
	List_Node	*next(List_Node *node) {
		return (this->_next = node);
	}
	void		print(void) {
		printf("  %.7u | %.2u/%.2u/%.4u | %2u\n",
			this->polis_id,
			Date::get_dat(this->date),
			Date::get_month(this->date),
			Date::get_year(this->date),
			this->diagnosis);
	}
};

class List {
private:
	List_Node		*root;
public:
	List(u32_t size) {
		List_Node *new_it;
		if (size-- == 0) {
			this->root = 0x0;
			return ;
		}
		this->root = new List_Node;
		for (List_Node *it = this->root; size != 0; --size) {
			new_it = new List_Node;
			it->next(new_it);
		}
	}

	List(const List& list) {
		this->root = list.root;
	}

	List(void) {
		this->root = 0x0;
	}

	void			empty(void) {
		List_Node	*node = this->root;
		List_Node	*del;

		while (node != 0x0) {
			del = node;
			node = node->next();
			delete del;
		}
	}

	bool			is_empty(void) {
		return (this->root == 0x0 ? true : false);
	}

	List_Node		*operator[](u32_t index) {
		return (this->get(index));
	}

	List_Node		*operator[](bool (*cb)(const List_Node &)) {
		return (this->get(cb));
	}

	List			sublist(bool (*cb)(const List_Node &));
	List			sublist_cut(bool (*cb)(const List_Node &));
	List_Node		*get(u32_t);
	List_Node		*get(bool (*cb)(const List_Node &));
	void			push_back(List_Node *node);
	void			push_front(List_Node *node);
	void			push_front(List_Node *node, bool (*cb)(const List_Node &));
	void			print(const char *str = 0x0);
};

#endif