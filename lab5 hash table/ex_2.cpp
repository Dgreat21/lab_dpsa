#include "hash_table.h"
#include <stdio.h>

using namespace std;

struct Student
{
	char	*group;
	char	*name;
};

ostream& operator<<(ostream& os, const Student& s)
{
    os << "[\"" << s.name << "\", " << s.group << "]";
    return os;
}

void	free_stud(Student *s)
{
	delete s->group;
	delete s->name;
}

// int		main(void)
// {
// 	HashTable<Student>		*hs;

// 	hs = new HashTable<Student>(4, &free_stud);

// 	hs->print();
// 	delete hs;
// }

struct Commands
{
	char	id[1024];
	char	group[1024];
	char	name[1024];
	char	type;
};

Commands		get_command(void)
{
	char		input[1024];
	char		*tok;
	Commands	command;

	bzero(&command, sizeof(Commands));
	std::cout << "$> ";
	std::cin.getline(input, 1024);
	tok = strtok(input, "/");
	command.type = tok[0];
	if ((tok = strtok(NULL, "/")))
		strncpy(command.id, tok, 1024);
	if ((tok = strtok(NULL, "/")))
		strncpy(command.group, tok, 1024);
	if ((tok = strtok(NULL, "/")))
		strncpy(command.name, tok, 1024);
	return command;
}

int		main(void)
{
	HashTable<Student>		*hs;
	Student					stud;
	Student					*std_ptr;
	Commands				command;
	
	hs = new HashTable<Student>(4, &free_stud);

	while (std::cin.good())
	{
		switch ((command = get_command()).type)
		{
			case ('+'):
				if (!command.id[0] || !command.group[0] || !command.name[0])
				{
					std::cerr << "Invalid arguments\n";
					break ;
				}
				stud.group = strdup(command.group);
				stud.name = strdup(command.name);
				hs->set(command.id, stud);
				break;
			case ('-'):
				if (!command.id[0])
				{
					std::cerr << "Invalid arguments\n";
					break ;
				}
				hs->del(command.id);
				break;
			case ('?'):
				if (!command.id[0])
				{
					std::cerr << "Invalid arguments\n";
					break ;
				}
				std_ptr = hs->get(command.id);
				if (!std_ptr)
					std::cout << "Student with such id, not found\n";
				else
					std::cout << "Student found:\n" << command.id << ", " << std_ptr->group << ", " << std_ptr->name << "\n";
				break;
			case ('p'):
				hs->print();
				break;
			case ('h'):
				std::cout << "\nUSAGE:\n"
				"+/ID/GROUP/NAME - command for adding student with such ID, GROUP and NAME\n"
				"-/ID - command for delete student with such ID.\n"
				"?/ID - command to print info about student with such ID.\n"
				"p - to print info about hash table.\n\n"
				"h - for users manual.\n"
				"q - for quit.\n\n";
				break;
			case ('q'):
				exit(0);
				break;
			default:
				std::cerr << command.type << " - unknown command\n";
		};
	}
	delete hs;
	return (EXIT_SUCCESS);
}
