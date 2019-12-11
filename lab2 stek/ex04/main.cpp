#include <stack>
#include <iostream>

#define  USER_TEXT_BUFFER_SZ 1024

struct duple
{
	int		op;
	int		cl;
};

void	put_duple(duple dup)
{
	std::cout << "(";
	std::cout << dup.op;
	std::cout << ", ";
	std::cout << dup.cl;
	std::cout << ")";
}

void put_duples_stack(std::stack <duple> s, char const *name) 
{
	std::cout << name << "  ";
	if (s.empty())
	{
		std::cerr << "EMPTY\n";
		return ;
	}
	while (!s.empty())
	{
		put_duple(s.top());
		s.pop();
		!s.empty() ? std::cout << " " : 0;
	}
	std::cout << std::endl;
}

std::stack <duple> reversestack(std::stack <duple> s) 
{
	std::stack	<duple> rvs;

	while (!s.empty())
	{
		rvs.push(s.top());
		s.pop();
	}
	return (rvs);
}

int		resolve_brackets(char *str)
{
	duple		item = {-1, -1};
	std::stack	<duple> s;
	std::stack	<duple> ops;
	std::stack	<duple> cls;
	size_t		i = -1;
	int			check = 0;

	while (str[++i])
	{
		if (str[i] == '(')
		{
			++check;
			item.op = i + 1;
			s.push(item);
		}
		else if (str[i] == ')')
		{
			--check;
			if (check < 0)
			{
				std::cerr << "BAD INPUT\n\n";
				return (1);
			}
			item = s.top();
			s.pop();
			item.cl = i + 1;
			cls.push(item);
		}
	}
	if (check && i != 0)
	{
		std::cerr << "BAD INPUT\n\n";
		return (1);
	}
	while (i-- > 0)
	{
		if (str[i] == ')')
		{
			item.cl = i + 1;
			s.push(item);
		}
		else if (str[i] == '(')
		{
			item = s.top();
			s.pop();
			item.op = i + 1;
			ops.push(item);
		}
	}
	cls = reversestack(cls);
	put_duples_stack(cls, "A:");
	put_duples_stack(ops, "B:");
	std::cout << std::endl;
	return (0);
}

int		main(void)
{
	char		input[USER_TEXT_BUFFER_SZ];

	while (1)
	{
		bzero(input, sizeof(input));
		std::cout << "Type an expression: ";
		std::cin.getline(input, sizeof(input));
		if (std::cin.good() != true)
			break ;
		if (!strcmp(input, "/exit"))
			return (EXIT_SUCCESS);
		resolve_brackets(input);
	}
	return (EXIT_FAILURE);
}