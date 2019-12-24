#include "hash_table.h"
#include <iostream>

using namespace std;

#define UT_HS_SZ 16

#define UT_TEST(str) (cout << str << ": " << fake(str, UT_HS_SZ) << "\n")

int			main(void)
{
	const char	*strs[] = {
		"ok",
		"ko",
		"ai",
		"php",
		"sql",
		"b-52",
		"design",
		"burner",
		"hoop",
		"bash",
		"python2",
		"heap",
		"apple",
		"stack",
		"hacker",
	};
	HashTable<int>	*hs = new HashTable<int>(16);
	int				*ptr;

	for (u64 i = 0; i < (sizeof(strs)/sizeof(char *)); ++i)
		hs->set(strs[i], i);
	hs->print();
	delete hs;
	return (0);
}