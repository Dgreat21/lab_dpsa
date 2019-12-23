#include "hash_table.h"
#include <iostream>

using namespace std;

#define UT_HS_SZ 16

#define UT_TEST(str) (cout << str << ": " << hash1(str, UT_HS_SZ) << "\n")

u64			hash1(const char *key, u64 fake)
{
	// fnv1a
	u64 	hash = HS_FNV1A_64_OFFSET;

	while (*key)
	{
		hash ^= u64(*key);
		hash *= HS_FNV1A_64_PRIME;
		key += 1;
	}
	return (hash % fake);
}

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
		"hacker"
	};
	HashTable<int>	*hs = new HashTable<int>(16);
	int				*ptr;

	for (u64 i = 0; i < (sizeof(strs)/sizeof(char *)); ++i)
		hs->set(strs[i], i);
	delete hs;
	return (0);
}