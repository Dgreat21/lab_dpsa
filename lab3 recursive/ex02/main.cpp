#include "list.h"
#include <iostream>

List<int>	*global;
int			debug;

int		list_snap()
{
	std::cout <<
	"\n===:\t" << global << "\n";
	return (1);
}

template	<typename T>
List<T>		*recursive_list_zeroid(List<T> *list, void (*del)(T data))
{
	
	if (list == NULL)
		return (NULL);
	if (list->data == static_cast<T>(0))
	{
		List<T> *const next = recursive_list_zeroid(list->next, del);
		if (del)
			del(list->data);
		delete list;
		return (next);
	}
	if (list->next != (list->next = recursive_list_zeroid(list->next, del)))
		debug ? list_snap() : 0;
	return (list);
}

int		main(void)
{
	char		input[256];
	char		*tok = NULL;
	char		*brkb = NULL;
	int			num = 0;
	List<int>	*list = NULL;

	while (std::cin.good())
	{
		list = NULL;
		std::cout << "Type an integer numbers (type `help` for manual):\n";
		std::cout << "$> ";
		bzero(input, sizeof(input));
		std::cin.getline(input, sizeof(input));
		for (
			tok = strtok_r(input, " \t\n", &brkb);
			tok;
			tok = strtok_r(NULL, " \t\n", &brkb)
		)
		{
			if (!strncmp(tok, "help", 4))
				break ;
			if (!strncmp(tok, "exit", 4))
				break ;
			if (!strncmp(tok, "verbose", 7))
				break ;
			num = atoi(tok);
			list_push(num, &list);
		}
		if (list)
		{
			global = list;
			std::cout << "\nBEF:\t" << list << "\n";
			list = recursive_list_zeroid(list, LIST_NOTFREE);
			std::cout << "\nAFT:\t" << list << "\n\n";
			list_destroy(&list, nulldel);
		}
		list = NULL;
		if (tok && !strncmp(tok, "exit", 4))
			break ;
		if (tok && !strncmp(tok, "verbose", 7))
		{
			std::cout << "\nVERBOSE MODE ON (to turn it off, type it again)\n\n";
			debug = !debug;
		}
		if (tok && !strncmp(tok, "help", 4))
		{
			std::cout << "\nUSAGE:\n"
			"Programm removes zero elements from the list.\n\n"
			"Type `verbose` for long output.\n\n"
			"Type integers separated by spaces,\n"
			"if you type a word, it equals to 0.\n"
			"If you want to exit, just type `exit`.\n\n";
		}
	}
	return (EXIT_SUCCESS);
}

