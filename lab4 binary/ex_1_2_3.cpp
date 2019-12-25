#include "btree.h"
#include <iostream>

int		main(void)
{
	ASTree		*ast = new ASTree("1 + 2");

	ASTree		*ast_cp = new ASTree(ast);
	std::cout << "Orig: " << ast->execute() << "\nCopy: " << ast_cp->execute() << "\n\n";

	ast->prepare("2 + 3");
	std::cout << "Orig: " << ast->execute() << "\nCopy: " << ast_cp->execute() << "\n\n";

	std::cout << "ORIGINAL:\n";
	ast->put_formula();
	ast->console_log();

	std::cout << "\nCOPY:\n";
	ast_cp->put_formula();
	ast_cp->console_log();
	std::cout << "\n";

	delete ast;
	delete ast_cp;
}