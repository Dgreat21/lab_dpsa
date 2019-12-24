#include "btree.h"

int		main(void)
{
	ASTree		*ast = new ASTree("1 + 2");
	long		result;

	result = ast->execute();
	// ast->console_log();

	ast->prepare("1 * 2 * 4 + 5 * 5 * 6 + 6");
	result = ast->execute();
	ast->console_log();

	ast->prepare("1 + 2");
	result = ast->execute();
	// ast->console_log();

	ast->prepare("4 - 5");
	result = ast->execute();

	ast->prepare("(3 + 3)*4");
	result = ast->execute();

	ast->prepare("1 + 2 * 2 + 1");
	result = ast->execute();

	delete ast;
}