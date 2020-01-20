#include "list.h"
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

map<string, List>		g_list_map = {};
char					line[1024];
u32_t					find_polis;
u32_t					find_date;
u32_t					find_dg;

vector<string>	split(string strToSplit, char delimeter) {
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter)) {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

vector<string>	get_arguments(void) {
	string			line_str;
	vector<string>	args;

	cin.getline(line, sizeof(line));
	line_str = line;
	args = split(line_str, ' ');
	return (args);
}

void		put_err(const char *message) {
	cerr << "Ошибка: " << message << endl;
}

void		put_greeting_mess(void) {
	printf(
		"Приветствуем вас в программе тестирования списков!\n"
		"Для инструкции наберите `help`\n"
		"Автор: Мазохин Д.И.\n"
	);
}

void		put_prompt(void) {
	cout << "$> ";
}

bool		is_list_exists(const string &name) {
	return	g_list_map.count(name) != 0;
}

void		put_help_message(void) {
	printf(
		"\n		Инструкция:\n\n\n"
		"`create <name> [count]` - создать список с именем name и с количеством\n" // create_list //
		"	элементов count.\n\n"
		"`delete <name>` - удалить список\n\n" // delete_list //
		"`print <name>` - вывести список на экран.\n\n" // put_list //
		"`get <name> <polis_id>` - получение элементов списка по ключу.\n\n" // get_values //
		"`push <name> <polis> <diagnosis> <date> [before_polis]` - вставка\n" // push_list //
		"	элемента, если указан before_polis, то элемент вставляется перед\n"
		"	элемнтом с указаным полисом.\n\n"
		"`sublist <name> <sub_name> <mv|cp> <-pd <polis> | -dg <diagnosis> | -dt <date>>` -\n" // sub_list //
		"	создает новый список из списка name, по значениям. mv - перенос элементов, cp - копирование.\n\n"
		"`get_dt_dg <name> <diagnosis> <date>` - определяет количество элементов в списке\n" // get_dt_dg //
		"	с задаными диагнозом и датой.\n\n"
		"`list` - выводит список доступных вам списков.\n\n" // list_list //
		"`exit` - выход из программы.\n\n" //
	);
}

void		delete_list(const string &name) {
	if (is_list_exists(name) == false) {
		put_err("Список с таким именем отсуствует!\n");
	} else {
		g_list_map[name].empty();
		g_list_map.erase(name);
	}
}

void		create_list(const string &name, u32_t size) {
	List			new_list;
	vector<string>	args;
	
	if (is_list_exists(name)) {
		put_err("Список с таким именем уже существует!\n");
	} else {
		new_list = List(size);
		for (u32_t i = 0; i < size; ++i) {
			cout << "Введите данные элемента №" << i << ": ";
			args = get_arguments();
			if (args.size() != 3 || stol(args[0]) == 0) {
				i -= 1;
				put_err("Введите правильный формат данных: <polis >1 > <diagnosis any> <date any>!");
				continue ;
			} else {
				new_list[i]->polis_id = (u32_t)stol(args[0]);
				new_list[i]->diagnosis = (u32_t)stol(args[1]);
				new_list[i]->date = (u32_t)stol(args[2]);
			}
			args.clear();
		}
		g_list_map.insert({name, new_list});
	}
}

void		get_values(const string &name, u32_t polis_id) {
	if (is_list_exists(name) == false) {
		put_err("Список с таким именем отсуствует!\n");
	} else {
		List	request;

		find_polis = polis_id;
		request = g_list_map[name].sublist([](const List_Node &n) -> bool {
			return (n.polis_id == find_polis);
		});
		cout << "\nСПИСОК ЗНАЧЕНИЙ ОТВЕЧАЮШИХ ЗАПРОСУ:\n";
		request.print();
		request.empty();
	}
}

void		get_dt_dg(const string &name, u32_t dg, u32_t dt) {
	if (is_list_exists(name) == false) {
		put_err("Список с таким именем отсуствует!\n");
	} else {
		List	request;

		find_dg = dg;
		find_date = dt;
		request = g_list_map[name].sublist([](const List_Node &n) -> bool {
			return (n.diagnosis == find_dg && n.date == find_date);
		});
		cout << "Количество ответов: " << request.size() << "\n";
		request.print("Запрос");
		request.empty();
	}
}

void		sub_list(const string &src_name, const string &sub_name, u32_t param, bool mv=false, int mode =0) {
	List	new_list;

	if (is_list_exists(src_name) == false) {
		put_err("Список с таким именем отсуствует!\n");
	} else {
		switch (mode) {
			case 1:
				find_polis = param;
				new_list = mv == false?
					g_list_map[src_name].sublist([](const List_Node &n) { return find_polis == n.polis_id ? true : false;}) :
					g_list_map[src_name].sublist_cut([](const List_Node &n) { return find_polis == n.polis_id ? true : false;}) ;
				break;
			case 2:
				find_dg = param;
				new_list = mv == false?
					g_list_map[src_name].sublist([](const List_Node &n) { return find_dg == n.diagnosis ? true : false;}) :
					g_list_map[src_name].sublist_cut([](const List_Node &n) { return find_dg == n.diagnosis ? true : false;}) ;
				break;
			case 3:
				find_date = param;
				new_list = mv  == false?
					g_list_map[src_name].sublist([](const List_Node &n) { return find_date == n.date ? true : false;}) :
					g_list_map[src_name].sublist_cut([](const List_Node &n) { return find_date == n.date ? true : false;}) ;
				break;
			default:
				new_list = mv == false?
					g_list_map[src_name].sublist([](const List_Node &n) { return true;}) :
					g_list_map[src_name].sublist_cut([](const List_Node &n) { return true;}) ;
		};
		if (new_list.is_empty())
			put_err("Подсписок вышел пустым, поэтому не был создан!");
		else {
			g_list_map.insert({sub_name, new_list});
		}
	}
}

void		put_list(const string &name) {
	if (is_list_exists(name) == false) {
		put_err("Список с таким именем отсуствует!\n");
	} else {
		g_list_map[name].print(name.c_str());
	}
}

void		list_list(void) {
	map<string, List>::iterator		it = g_list_map.begin();

	if (g_list_map.size() == 0) {
		printf("У вас нет доступных списков!\n\n");
		return ;
	}
	printf("\nКол-во списков: %zu\n==============================\n", g_list_map.size());
	printf("IND |%16s | SIZE |\n", "LIST_NAME");
	int		i = 0;
	while (it != g_list_map.end()) {
		++i;
		string	name = it->first;
		printf("%3d |%16s | %4llu |\n", i, name.c_str(), it->second.size());
		it++;
	}
	printf("==============================\n\n");
}

void		push_list(const string &name, u32_t pid, u32_t diagnosis, u32_t date, u32_t gpid =0) {
	List_Node	*node;

	if (is_list_exists(name) == false) {
		put_err("Список с таким именем отсуствует!");
	} else if (pid == 0) {
		put_err("Номер полиса не может быть 0!");
	} else {
		node = new List_Node(pid, diagnosis, (Date::date_t)date);
		if (gpid == 0) {
			g_list_map[name].push_back(node);
		} else {
			find_polis = gpid;
			g_list_map[name].push_front(node, [](const List_Node &nd) -> bool {
				if (find_polis == nd.polis_id)
					return (true);
				return (false);
			});
		}
	}
}

void		clean_up(void) {
	map<string, List>::iterator		it = g_list_map.begin();

	while (it != g_list_map.end()) {
		it->second.empty();
		it++;
	}
	g_list_map.clear();
}

void		work_loop(void) {
	vector<string>		args;
	i64_t				sz_arg;
	u32_t				ps_arg;
	u32_t				dg_arg;
	u32_t				dt_arg;
	u32_t				extra_arg;
	bool				logic_arg;

	put_greeting_mess();
	for (;;) {
		try {
			put_prompt();
			args = get_arguments();
			if (args.size() == 0)
				throw ("Введите команду!");
			if (args[0].compare("help") == 0) {
				put_help_message();
			} else if (args[0].compare("exit") == 0) {
				break;
			} else if (args[0].compare("create") == 0) {
				if (args.size() < 2)
					throw("Неверное количество аргументов!");
				else if (args.size() == 2)
					sz_arg = 0;
				else
					sz_arg = atol(args[2].c_str());
				if (sz_arg < 0 || sz_arg > 1000)
					throw("Размер списка не может быть больше 1000 элементов.");
				create_list(args[1], (u32_t)sz_arg);
			} else if (args[0].compare("list") == 0) {
				list_list();
			} else if (args[0].compare("print") == 0) {
				if (args.size() != 2) throw ("Неверное количество аргументов!");
				put_list(args[1]);
			} else if (args[0].compare("get") == 0) {
				if (args.size() != 3) throw "Неверное количество аргументов!";
				get_values(args[1], (u32_t)stol(args[2]));
			} else if (args[0].compare("push") == 0) {
				if (args.size() < 5) throw "Неверное кол-во аргуметов!";
				if (args.size() > 5) {
					push_list(args[1], (u32_t)stol(args[2]), (u32_t)stol(args[3]), (u32_t)stol(args[4]), (u32_t)stol(args[5]));
				} else {
					push_list(args[1], (u32_t)stol(args[2]), (u32_t)stol(args[3]), (u32_t)stol(args[4]));
				}
			} else if (args[0].compare("sublist") == 0) {
				if (args.size() < 4) throw "Неверное количество аргументов";
				if (args[3].compare("mv") == 0) logic_arg = true;
				else if (args[3].compare("cp") == 0) logic_arg = false;
				else throw "Неверный аргумент <cp|mv>!";
				if (args.size() < 6) {
					sub_list(args[1], args[2], 0, logic_arg);
				} else {
					if (args[4].compare("-pd") == 0) sz_arg = 1;
					else if (args[4].compare("-dg") == 0) sz_arg = 2;
					else if (args[4].compare("-dt") == 0) sz_arg = 3;
					else throw "Неверный аргумент -pd | -dt | -dg !";
					sub_list(args[1], args[2], (u32_t)stol(args[5]), logic_arg, sz_arg);
				}
			} else if (args[0].compare("delete") == 0) {
				if (args.size() == 1)
					clean_up();
				else
					delete_list(args[1]);
			} else if (args[0].compare("get_dt_dg") == 0) {
				if (args.size() != 4) throw "Неверное кол-во аргументов!";
				get_dt_dg(args[1], (u32_t)stol(args[2]), (u32_t)stol(args[3]));
			} else {
				put_err("Неизветсная команда!");
			}
			args.clear();
		} catch (const char *mess) {
			put_err(mess);
		}
	}
	clean_up();
}

int 		main(void) {
	work_loop();
}