#include "hash_table.h"

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

int		main(void)
{
	HashTable<Student>		*hs;

	hs = new HashTable<Student>(4, &free_stud);

	hs->print();
	delete hs;
}

struct Commands
{
	char	id[1024];
	char	group[1024];
	char	name[1024];
	char	type;
};


int		main(void)
{
	char					input[256];
	HashTable<Student>		*hs;
	Commands				command;
	
	hs = new HashTable<Student>(4, &free_stud);

	while (std::cin.good())
	{
		switch ((command = get_command(void)))
		{
			case ('+'):
				break;
			case ('-'):
				break;
			case ('?'):
				break;
			case ('p'):
				break;
			case ('h'):
				break;
			case ('q'):
				break;
			default:
				std::cerr << command.type << " - unknown error!\n";
		};
		{
			std::cout << "\nUSAGE:\n"
			"+/ID/GROUP/NAME - command for adding student with such ID, GROUP and NAME\n"
			"-/ID - command for delete student with such ID.\n"
			"?/ID - command to print info about student with such ID.\n"
			"p - to print info about hash table.\n\n"
			"h - for users manual.\n"
			"q - for quit.\n\n";
		}
	}
	delete hs;
	return (EXIT_SUCCESS);
}
