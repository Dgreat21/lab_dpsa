#ifndef LIST_H
# define LIST_H

#include <inttypes.h>

typedef uint64_t		u64_t;
typedef uint32_t		u32_t;
typedef int64_t			i64_t;
typedef int32_t			i32_t;

const u32_t				JAN = 1;
const u32_t				FEB = 2;
const u32_t				MAR = 3;
const u32_t				APR = 4;
const u32_t				MAY = 5;
const u32_t				JUN = 6;
const u32_t				JUL = 7;
const u32_t				AUG = 8;
const u32_t				SEP = 9;
const u32_t				OCT = 10;
const u32_t				NOV = 11;
const u32_t				DEC = 12;

class		Date {
	private:
		u32_t	year;
		u32_t	month;
		u32_t	day;

	public:
		u32_t	get_year(void) {
			return (this->year);
		}
		u32_t	get_month(void) {
			return (this->month);
		}
		u32_t	get_day(void) {
			return (this->day);
		}
		friend u32_t	get_yyyy_mm_dd(Date date);
		friend Date		set_yyyy_mm_dd(u32_t date);
};

Date		set_yyyy_mm_dd(u32_t date);
u32_t		get_yyyy_mm_dd(Date date);

typedef struct list_s	list_t;

// информация в списке: Номер_мед_полиса, Дата обращения, Код диагноза
struct list_s {
	struct list_s	*next;
	Date			date;
	u32_t			polis_id;
	u32_t			diagnosis_code;
};

list_t		*list_node(u32_t id, u32_t diagnosis, u32_t date); //
list_t		*list_node(void); //

list_t		*list_create_n(u64_t list_size); //

void		list_node_print(list_t *node); //
void		list_print(list_t *list, const char *name); //

void		list_delete(list_t **list); //
void		list_node_delete(list_t **list); //

void		list_push_back(list_t **list, list_t *new_node); //
void		list_push_front(list_t **list, list_t *new_node); //

void		list_push_front(list_t **list, list_t *new_node, int (*callback)(list_t *)); //

list_t		*list_get_index(list_t *list, u64_t index); //
list_t		*list_get_callback(list_t *list, int (*callback)(list_t *)); //

list_t		*list_node_dup(list_t *node); //

list_t		*list_sublist(list_t *list, int (*callback)(list_t *)); //
list_t		*list_sublist_cut(list_t **list, int (*callback)(list_t *)); //

#endif