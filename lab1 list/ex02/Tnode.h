#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class Tnode
{
private:
	unsigned		id;		//	Номер мед карты
	std::string		date;	//	Дата обращения
	unsigned		code;	//	Код диагноза
	Tnode*			next;
public:
	Tnode(unsigned i, std::string d, unsigned c, Tnode* n);
	Tnode();
	void		move_data(Tnode* n);
	unsigned	get_id();
	std::string	get_date();
	unsigned	get_code();
	Tnode*		get_next();
	void		set_next(Tnode* n);
	void		set_id(unsigned i);
	void		push_node();
	void		delete_by_code();
	Tnode*		move_to_new();
	void		count_codes();
	void		print_node();
	void		createnode();
};

