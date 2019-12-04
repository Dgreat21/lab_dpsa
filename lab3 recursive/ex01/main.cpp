//
// Created by Dyan Great on 04/12/2019.
//
#include <iostream>
#include <string.h>

typedef	struct	numbers{
	double			num;
	struct	numbers	*next;
};

#define MALLOC_NEW_LIST 0

void		error_rise(int error_code)
{
	std::cout << "Something went wrong" << std::endl;
	switch (error_code)
	{
		case : MALLOC_NEW_LIST
			std::cout << "MALLOC_NEW_LIST error" << std::endl;
			break;
		default:
			std::cout << "unexpected error" << endl;
	}
	exit();
}

double		prv_factorial(numbers *node)
{
	double num;

	if (node->next == NULL)
		return (num);
	num = prv_factorial(node->num * node->next->num);
	return (num);
}

numbers		*lst_add(numbers *node, int content, bool end = true)
{
	numbers *new;

	if (!(new = (numbers *)malloc(sizeof(numbers))))
	{
		error_rise(MALLOC_NEW_LIST);
		return (NULL);
	}
	new->next = NULL;
	if (end){
		node->next = new;
	}
	else
		new->next = node;
	return (new);
}

double input(int i)
{
	double number;
	string input;

	std::cout << "enter " << i << "-st number" << endl;
	std::cin >> input;

	number = atol(input);
	return (number);
}


numbers	*menu(){

	std::cout<< "Hello!" << std::endl << " program usage is very simple : if you input string instead number it will be 0\n";
	std:cout << "How much numbers in list?" << std::endl;
	size_t size;
	std::cin >> size;

	numbers *begin, *list;

	begin = list;

	for(int i = 1; i < size; i++)
	{
		lst_add(list, input(i), false);
		list = list->next;
	}

	double number;
	string input;

	std::cout << "enter last number" << endl;
	std::cin >> input;

	number = atol(input);
	lst_add(list, input(i), false);
	list = begin;
}

void	input()
{

}

int		main(int argc, std::string){

}