#include <stack>
#include <iostream>
#include <cstring>
#include "stack_arr.h"
#include  "stack_list.h"

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
		if (!s.empty())
				std::cout << " ";
	}
	std::cout << std::endl;
}

void put_duples_stack(StackAR <duple> *s, char const *name) 
{
	std::cout << name << "  ";
	if (s->size() == 0)
	{
		std::cerr << "EMPTY\n";
		return ;
	}
	while (s->size())
	{
		put_duple(s->top());
		s->pop();
		if (s->size())
				std::cout << " ";
	}
	std::cout << std::endl;
}

void put_duples_stack(StackL <duple> *s, char const *name) 
{
	std::cout << name << "  ";
	if (s->size() == 0)
	{
		std::cerr << "EMPTY\n";
		return ;
	}
	while (s->size())
	{
		put_duple(s->top());
		s->pop();
		if (s->size())
				std::cout << " ";
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

StackAR<duple> *reversestack(StackAR <duple> *s) 
{
	StackAR<duple>	*rvs = new StackAR<duple>;

	while (s->size())
	{
		rvs->push(s->top());
		s->pop();
	}
	delete s;
	return (rvs);
}

StackL<duple> *reversestack(StackL <duple> *s) 
{
	StackL<duple>	*rvs = new StackL<duple>;

	while (s->size())
	{
		rvs->push(s->top());
		s->pop();
	}
	delete s;
	return (rvs);
}

int		resolve_brackets(char *str)
{
	duple		item = {-1, -1};
	std::stack	<duple> s;
	std::stack	<duple> ops;
	std::stack	<duple> cls;

	StackAR		<duple> *s_ar = new StackAR<duple>;
	StackAR		<duple> *o_ar = new StackAR<duple>;
	StackAR		<duple> *c_ar = new StackAR<duple>;

	StackL		<duple> *s_l = new StackL<duple>;
	StackL		<duple>	*o_l = new StackL<duple>;
	StackL		<duple>	*c_l = new StackL<duple>;

	size_t		i = -1;
	int			check = 0;

	while (str[++i])
	{
		if (str[i] == '(')
		{
			++check;
			item.op = i + 1;
			s.push(item);
			s_ar->push(item);
			s_l->push(item);
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
			s_ar->pop();
			s_l->pop();
			item.cl = i + 1;
			cls.push(item);
			c_ar->push(item);
			c_l->push(item);
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
			s_ar->push(item);
			s_l->push(item);
		}
		else if (str[i] == '(')
		{
			item = s.top();
			s.pop();
			s_ar->pop();
			s_l->pop();
			item.op = i + 1;
			ops.push(item);
			o_ar->push(item);
			o_l->push(item);
		}
	}
	cls = reversestack(cls);
	c_l = reversestack(c_l);
	c_ar = reversestack(c_ar);
	put_duples_stack(cls, "A STL:");
	put_duples_stack(c_l, "A LST:");
	put_duples_stack(c_ar, "A ARR:");
	put_duples_stack(ops, "B STL:");
	put_duples_stack(o_l, "B LST:");
	put_duples_stack(o_ar, "B ARR:");

	delete c_l;
	delete c_ar;
	delete o_l;
	delete o_ar;
	delete s_l;
	delete s_ar;
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
