#include "Lab1.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// вывод списка

void	print_node(t_node* head)
{
	t_node* tmp;
	unsigned	i;

	i = 0;
	tmp = head;
	if (!tmp)
		std::cout << "Please insert full list" << endl;
	while (tmp)
	{
		cout << "id №" << i << ": " << endl;
		cout << "\tPolis id: " << tmp->id << endl;
		cout << "\tCalling date: " << tmp->date << endl;
		cout << "\tDiagnosys code: " << tmp->code << endl;
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

	std::cout << "How much elements need?";
	std::cin >> n;
	i = 0;
	head = NULL;
	tmp = NULL;
	while (++i <= n)
	{
		if (!head)
		{
			head = node_init();
			std::cout << "Inserting" << i << "element :\n";
			std::cout << "\tisert polis id: ";
			std::cin >> id;
			std::cout << "\tinsert calling date: ";
			std::cin >> date;
			std::cout << "\tinsert diagnosys code: ";
			std::cin >> code;
			head->id = id;
			head->date = date;
			head->code = code;
			tmp = head;
		}
		else
		{
			std::cout << "for " << i << " element:\n";
			std::cout << "\tinsert polis id: ";
			std::cin >> id;
			std::cout << "\tinsert calling date: ";
			std::cin >> date;
			std::cout << "\tinsert daignosys code: ";
			std::cin >> code;
			tmp->next = add_new(id, date, code);
			tmp = tmp->next;
		}
	}
	return (head);
}

int		select_menu(const char *str)
{

	if (strcmp(str, "create"))
		return (1);
	else if (strcmp(str, "print"))
		return (2);
	else if (strcmp(str, "push"))
		return (3);
	else if (strcmp(str, "delete"))                                                                                                      
		return (4); 
	else if (strcmp(str, "move"))
		return (5);
	else if (strcmp(str, "count"))
		return (6);
	else if (strcmp(str, "exit"))
		return (7);
	else if (strcmp(str, "help"))
		return (8);
	return (0);
}

void	print_help(void)
{
	std::cout<< std::endl << "type one of folowing menu items" << std::endl;
	std::cout << "create" << std::endl
			<<   "print" << std::endl
			<<   "push" << std::endl
			<<   "delete" << std::endl
			<<   "move" << std::endl
			<<   "count" << std::endl 
			<<   "exit" << std::endl
			<<   "help" << std::endl;
} 

int	main(void)
{
	t_node* head;
	string	str;
	char* str1;

	int	f_m;
	int c;

	c = 1;
	f_m = 1;
	head = NULL;
	
	std::cout << "For help type \"help\"" << std::endl;
	while (c){
		std::cout << "$>";
		std::cin >> str;
		switch (select_menu(str.c_str())) {
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
		case 7:
			exit(1);
			break;
		case 8:
			print_help();
		default :
			std::cout << "Bad input" << endl;
			break;
		}
	}
	return (0);
}
