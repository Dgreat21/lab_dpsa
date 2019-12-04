#include "Lab1.h"
#include <iostream>
#include <string>

using namespace std;

// вывод списка

void	print_node(t_node* head)
{
	t_node* tmp;
	unsigned	i;

	i = 0;
	tmp = head;
	if (!tmp)
		std::cout << "Вы не заполнили список" << endl;
	while (tmp)
	{
		cout << "Запись №" << i << ": " << endl;
		cout << "\tНомер Мед.Книжки: " << tmp->id << endl;
		cout << "\tДата обращения: " << tmp->date << endl;
		cout << "\tКод диагноза: " << tmp->code << endl;
		if (!tmp->next)
			cout << "\n";
		tmp = tmp->next;
		i++;
	}
}

t_node* node_init(void)
{
	t_node* res;

	if (!(res = new t_node))
		exit(-1);
	res->date = "";
	res->next = NULL;
	res->id = 0;
	res->code = 0;
	return (res);
}

t_node* add_new(unsigned id, string date, unsigned code)
{
	t_node* res;

	if (!(res = new t_node))
		exit(-1);
	res->id = id;
	res->date = date;
	res->code = code;
	res->next = NULL;
	return (res);
}

// Создание списка из n узлов

t_node* creatennode(void)
{
	t_node* head;
	t_node* tmp;
	size_t  	i;
	size_t		n;
	unsigned	id;
	std::string	date;
	unsigned	code;

	std::cout << "Сколько элементов нужно создать: ";
	std::cin >> n;
	i = 0;
	head = NULL;
	tmp = NULL;
	while (++i <= n)
	{
		if (!head)
		{
			head = node_init();
			std::cout << "Для " << i << " элемента:\n";
			std::cout << "\tВведите номер Мед.Книжки: ";
			std::cin >> id;
			std::cout << "\tВведите дату: ";
			std::cin >> date;
			std::cout << "\tВведите код диагноза: ";
			std::cin >> code;
			head->id = id;
			head->date = date;
			head->code = code;
			tmp = head;
		}
		else
		{
			std::cout << "Для " << i << " элемента:\n";
			std::cout << "\tВведите номер Мед.Книжки: ";
			std::cin >> id;
			std::cout << "\tВведите дату: ";
			std::cin >> date;
			std::cout << "\tВведите код диагноза: ";
			std::cin >> code;
			tmp->next = add_new(id, date, code);
			tmp = tmp->next;
		}
	}
	return (head);
}

int	main(void)
{
	t_node* head;
	string		str;
	int c;
	int	f_m;

	c = 1;
	f_m = 1;
	head = NULL;
	while (c) {
		if (f_m)  //Для того, чтобы меню выводилось 1 раз мы вводим условие
		{
			std::cout << "====================================МЕНЮ====================================" << endl;
			std::cout << " 1. Заполнить узел" << endl
				<< " 2. Вывести узел" << endl
				<< " 3. Добавить элемент" << endl
				<< " 4. Удалить элемент по заданному коду диагноза" << endl
				<< " 5. Переместить в новый список записи с номером Мед.Книжки" << endl
				<< " 6. Посчитать сколько раз обращались в определенную дату с определенным диагнозом" << endl
				<< " 0. Выход" << endl;
			std::cout << "============================================================================" << endl;
		}
		else
			std::cout << "Введите пункт меню: ";
		std::cin >> c;
		switch (c) {
		case 1:
			head = creatennode();
			break;
		case 2:
			print_node(head);
			break;
		case 3:
			head = push_node(head);
			break;
		case 4:
			delete_by_code(head);
			break;
		case 5:
			print_node(move_to_new(head));
			break;
		case 6:
			count_codes(head);
			break;
		case 0:
			exit(1);
			break;
		}
	}
	return (0);
}