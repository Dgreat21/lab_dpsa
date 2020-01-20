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

vector<string> split(string strToSplit, char delimeter) {
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter)) {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

void		put_greeting_mess(void) {
	printf(
		"Приветствуем вас в программе тестирования списков!\n"
		"Автор: Мазохин Д.И.\n"
	);
}

void		put_prompt(void) {
	cout << "Для инструкции наберите `help`\n" << "$> ";
}

bool		is_list_exists(const string &name) {
	return	g_list_map.count(name) != 0;
}

void		put_help_message(void) {
	printf(
		"\n		Инструкция:\n\n\n"
		"`create <name> [count]` - Создать список с именем name и с количеством\n"
		"	элементов count.\n\n"
		"`print <name>` - вывести список на экран.\n\n"
		"`get <name> <polis_id>` - получение элементов списка по ключу.\n\n"
		"`push <name> <polis> <diagnosis> <date> [before_polis]` - вставка\n"
		"	элемента, если указан before_polis, то элемент вставляется перед\n"
		"	элемнтом с указаным полисом.\n\n"
		"`sublist <name> <sub_name> [-pid polis | -dig diagnosis | -dat date]` - \n\n"
		"`sublist <name> <sub_name> [-pd polis | -dg diagnosis | -dt date]` -\n"
		"	создает новый список из списка name, по значениям.\n\n"
		"`get_dt_dg <name> <diagnosis> <date>` - определяет количество элементов в списке\n"
		"	с задаными диагнозом и датой.\n\n"
		"`list` - выводит список доступных вам списков.\n\n"
		"`exit` - выход из программы.\n\n"
	);
}

void		put_err(const char *message) {
	cerr << "Ошибка: " << message << endl;
}

void		create_list(const string &name, u32_t size) {
	List			new_list;
	string			line_str;
	vector<string>	args;
	
	if (is_list_exists(name)) {
		put_err("Список с таким именем уже существует!\n");
	} else {
		new_list = List(size);
		for (u32_t i = 0; i < size; ++i) {
			cout << "Введите данные элемента №" << i << ": ";
			cin.getline(line, sizeof(line));
			line_str = line;
			args = split(line_str, ' ');
			if (args.size() != 3) {
				size -= 1;
				put_err("Введите правильный формат данных: <polis> <diagnosis> <date>!");
				continue ;
			} else {
				new_list[i]->polis_id = (u32_t)atol(args[0].c_str());
				new_list[i]->date = (u32_t)atol(args[1].c_str());
				new_list[i]->diagnosis = (u32_t)atol(args[2].c_str());
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
			if (n.polis_id == ::find_polis)
				return (true);
			return (false);
		});
		request.print("Запрос");
		request.empty();
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
		printf("У вас нет доступных списков!\n");
		return ;
	}
	while (it != g_list_map.end()) {
		string	name = it->first;
		printf("> %s\n", name.c_str());
		it++;
	}
}

int 		main(void) {

}