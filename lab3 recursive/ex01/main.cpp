#include "list.h"
#include <iostream>

int		recursive_numbers(List<int> *lst)
{
	int			summ_n = 0;
	List<int>	*it_lst;

	if (!lst)
		return (1);
	it_lst = lst;
	while (it_lst)
	{
		summ_n += it_lst->data;
		it_lst = it_lst->next;
	}
	return (recursive_numbers(lst->next) * summ_n);
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
		std::cout << "Type an integer numbers (type help for user manual):\n";
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
			num = atoi(tok);
			list_push(num, &list);
		}
		if (list)
		{
			num = recursive_numbers(list);
			std::cout << "YOUR RESULT: " << num << "\n";
			list_destroy(&list, nulldel);
		}
		list = NULL;
		if (tok && !strncmp(tok, "exit", 4))
			break ;
		if (tok && !strncmp(tok, "help", 4))
		{
			std::cout << "\nUSAGE:\n"
			"Type integers separated by spaces,\n"
			"if you type a word, it equals to 0.\n"
			"If you want to exit, just type exit.\n\n";
		}
	}
	return (EXIT_SUCCESS);
}