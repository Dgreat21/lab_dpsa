#include "Lab1.h"

t_node	*push_node(t_node* head)
{
	t_node* res;
	t_node* node;
	unsigned	id;

	std::cout << "Введите номер Мед.Карты: ";
	std::cin >> id;
	res = new t_node;
	res->id = id;
	node = head;
	while (node->next && node->next->id != id)
		node = node->next;
	res->next = node->next;
	node->next = res;
	std::cout << "\tВведите дату обращения: ";
	std::cin >> res->date;
	std::cout << "\tВведите код диагноза: ";
	std::cin >> res->code;
	return (head);
}

void	delete_by_code(t_node* head)
{
	t_node* cur;
	t_node* prev;
	unsigned	code;

	std::cout << "\nВведите код диагноза: "; std::cin >> code;
	cur = head;
	prev = NULL;
	while (cur)
	{
		if (cur->code == code)
		{
			if (prev)
			{
				prev->next = cur->next;
				delete cur;
				cur = prev->next;
			}
			else
			{
				head = head->next;
				delete cur;
				cur = head;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

t_node* move_to_new(t_node* head)
{
	t_node* node;
	t_node* res;
	t_node* prev;
	t_node* next;
	unsigned	code;

	std::cout << "\nВведите номер Мед.Карты: ";
	std::cin >> code;
	node = head;
	res = 0;
	while (node && node->id != code)
	{
		prev = node;
		node = node->next;
	}
	res = node;
	while (node && node->id == code)
		node = node->next;
	prev->next = node;
	node = res;
	while (node && node->next != prev->next)
		node = node->next;
	node->next = 0;
	return (res);
}

void	 count_codes(t_node* head)
{
	t_node* tmp;
	unsigned	counter;
	unsigned	code;
	std::string	data;

	counter = 0;
	std::cout << "\nВведите код диагноза: "; std::cin >> code;
	std::cout << "Введите дату обращения: "; std::cin >> data;
	tmp = head;
	while (tmp)
	{
		if (tmp->code == code && tmp->date == data)
			counter++;
		tmp = tmp->next;
	}
	std::cout << "Количество обращений: " << counter << std::endl;
}
