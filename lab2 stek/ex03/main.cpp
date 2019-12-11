#include <iostream>
#include <string>
#include "stack_list.h"
#include "stack_arr.h"

template <class STACK>
void	test_loop(STACK *stack)
{
	char		input[256];
	int			number = 0;
	int			err = 0;
	
	stack = new STACK;
	while (strcmp(input, "/exit"))
	{
		try
		{
			bzero(input, sizeof(input));
			if (err == 0)
				std::cout << "Please, type a command ( '/help' for usage ).\n$> ";
			else
				err = 0;
			std::cin.width(sizeof(input));
			std::cin >> input;
			std::cout << "\n";
			if (!strncmp(input, "/help", 5))
			{
				std::cout << "USAGE:\n"
				"    '/push NUMBER' - push a number into the stack\n"
				"    '/pop' - pop a number from top of the stack\n"
				"    '/print' - print the stack\n"
				"    '/top' - print the top number\n"
				"    '/exit' - exit\n\n";
			}
			else if (!strncmp(input, "/push", 5))
			{
				std::cin >> input;
				number = atoi(input);
				stack->push(number);
				std::cout << number << ": PUSHED!\n\n";
			}
			else if (!strncmp(input, "/pop", 4))
			{
				number = stack->pop();
				std::cout << number << ": POPED!\n\n";
			}
			else if (!strncmp(input, "/top", 4))
			{
				number = stack->top();
				std::cout << number << ": at the top!\n\n";
			}
			else if (!strncmp(input, "/print", 4))
			{
				std::cout << "YOUR STACK:\n";
				stack->print();
				std::cout << "\n";
			}
			else if ((err = 1))
				std::cerr << "Error: Unkown command, write '/help' to see the Usage\n$> ";
		}
		catch (char const *a)
		{
			std::cout << "Error: " << a << "\n";
		}
	}

	delete stack;
}

int		main(int ac, char **av)
{
	if (ac == 2 && !strcmp("Array", av[1]))
	{
		StackAR<int>	*stack_a = NULL;

		test_loop(stack_a);
		return (EXIT_SUCCESS);
	}
	else if (ac == 2 && !strcmp("List", av[1]))
	{
		StackL<int>		*stack_l = NULL;

		test_loop(stack_l);
		return (EXIT_SUCCESS);
	}
	else
		std::cerr << "Usage: " << av[0] << " Array | List\n";
	return (EXIT_FAILURE);
}
