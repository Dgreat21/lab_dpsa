#include "btree.h"
#include <iostream>

// int		main(void)
// {
// 	ASTree		*ast = new ASTree("1 + 2");

// 	ASTree		*ast_cp = new ASTree(ast);
// 	std::cout << "Orig: " << ast->execute() << "\nCopy: " << ast_cp->execute() << "\n\n";

// 	ast->prepare("2 + 3");
// 	std::cout << "Orig: " << ast->execute() << "\nCopy: " << ast_cp->execute() << "\n\n";

// 	std::cout << "ORIGINAL:\n";
// 	ast->put_formula();
// 	ast->console_log();

// 	std::cout << "\nCOPY:\n";
// 	ast_cp->put_formula();
// 	ast_cp->console_log();
// 	std::cout << "\n";

// 	delete ast;
// 	delete ast_cp;
// }

void	resolve_tree(char *const input)
{
	ASTree		*ast = new ASTree(input);

	std::cout << "\nResult: " << ast->execute() << "\n\n";
	ast->put_formula();
	std::cout << "\nTREE:\n";
	ast->console_log();
	std::cout << "\n";
	delete ast;
}

int		main()
{
	char		input[1024];

	while (1)
	{
		bzero(input, sizeof(input));
		std::cout << "Type an expression: ";
		std::cin.getline(input, sizeof(input));
		if (std::cin.good() != true)
			break ;
		if (!strcmp(input, "exit"))
			return (EXIT_SUCCESS);
		try
		{
			resolve_tree(input);
		}
		catch (char a)
		{
			std::cerr << "Error caucht near: `" << a << "`\n";
		}
	}
	return (EXIT_FAILURE);
}
