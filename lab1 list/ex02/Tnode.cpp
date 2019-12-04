#include "Tnode.h"

unsigned	Tnode::get_id()
{
	return (this->id);
}

std::string	Tnode::get_date()
{
	return (this->date);
}

unsigned	Tnode::get_code()
{
	return (this->code);
}

Tnode* Tnode::get_next()
{
	return (this->next);
}

void	Tnode::set_next(Tnode* n)
{
	this->next = n;
}

void	Tnode::set_id(unsigned i)
{
	id = i;
}

Tnode::Tnode()
{
	id = 0;
	date = "";
	code = 0;
	next = 0;
}

Tnode* add_new(unsigned id, string date, unsigned code)
{
	Tnode* res;

	if (!(res = (new Tnode(id, date, code, NULL))))
		exit(-1);
	return (res);
}

Tnode::Tnode(unsigned i, std::string d, unsigned c, Tnode* n)
{
	id = i;
	this->date = d;
	this->code = c;
	this->next = n;
}

void	Tnode::move_data(Tnode* n)
{
	unsigned id;
	std::string date;
	unsigned code;
	Tnode* tmp;

	id = this->id;
	date = this->date;
	code = this->code;
	tmp = this->next;

	this->id = n->get_id();
	this->date = n->get_date();
	this->code = n->get_code();
	delete n;
	n = new Tnode(id, date, code, tmp);
	this->next = n;
}

void	Tnode::push_node()
{
	unsigned	id;
	Tnode *res;
	Tnode* node;

	std::cout << "Введите номер Мед.Карты: ";
	std::cin >> id;
	res = add_new(id, "\0", 0);
	node = this;
	while (node->get_next() && node->get_next()->id != id)
		node = node->get_next();
	res->set_next(node->get_next());
	node->set_next(res);
	std::cout << "\tВведите дату обращения: ";
	std::cin >> res->date;
	std::cout << "\tВведите код диагноза: ";
	std::cin >> res->code;
}

void	Tnode::delete_by_code()
{
	Tnode* cur;
	Tnode* prev;
	unsigned	code;

	std::cout << "\nВведите код диагноза: "; std::cin >> code;
	cur = this;
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
				move_data(this->next);
				delete cur;
				cur = this;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}


Tnode* Tnode::move_to_new()
{
	Tnode* node;
	Tnode* res;
	Tnode* prev;
	Tnode* next;
	unsigned	code;

	std::cout << "\nВведите номер Мед.Карты: ";
	std::cin >> code;
	node = this;
	res = 0;
	while (node && node->get_id() != code)
	{
		prev = node;
		node = node->get_next();
	}
	res = node;
	while (node && node->get_id() == code)
		node = node->get_next();
	prev->set_next(node);
	node = res;
	while (node && node->get_next() != prev->get_next())
		node = node->get_next();
	node->set_next(0);
	return (res);
}

void	 Tnode::count_codes()
{
	Tnode* tmp;
	unsigned	counter;
	unsigned	code;
	std::string	data;

	counter = 0;
	std::cout << "\nВведите код диагноза: "; std::cin >> code;
	std::cout << "Введите дату обращения: "; std::cin >> data;
	tmp = this;
	while (tmp)
	{
		if (tmp->code == code && tmp->date == data)
			counter++;
		tmp = tmp->next;
	}
	std::cout << "Количество обращений: " << counter << std::endl;
}

void	Tnode::print_node()
{
	Tnode* tmp;
	unsigned	i;

	i = 0;
	tmp = this;
	if (!tmp)
		std::cout << "Список пуст" << endl;
	while (tmp)
	{
		cout << "Элемент №" << i << ": " << endl;
		cout << "\tНомер Мед.Карты: " << tmp->id << endl;
		cout << "\tДата обращщения: " << tmp->date << endl;
		cout << "\tКод диагноза: " << tmp->code << endl;
		if (!tmp->next)
			cout << "\n";
		tmp = tmp->get_next();
		i++;
	}
}

Tnode* node_init(void)
{
	Tnode* res;

	if (!(res = new Tnode(0, "\0", 0, NULL)))
		exit(-1);
	return (res);
}

void	Tnode::createnode(void)
{
	Tnode		*tmp;
	size_t  	i;
	size_t		n;
	unsigned	id;
	std::string	date;
	unsigned	code;

	std::cout << "Сколько элементов нужно создать: ";
	std::cin >> n;
	i = 0;
	tmp = this;
	while (++i <= n)
	{
		if (i == 1)
		{
			std::cout << "Для " << i << " элемента:\n";
			std::cout << "\tВведите номер Мед.Книжки: ";
			std::cin >> id;
			std::cout << "\tВведите дату: ";
			std::cin >> date;
			std::cout << "\tВведите код диагноза: ";
			std::cin >> code;
			this->id = id;
			this->date = date;
			this->code = code;
			tmp = this;
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
			tmp->set_next(add_new(id, date, code));
			tmp = tmp->get_next();
		}
	}
}
