#pragma once

#define HS_STD_SIZE	4 // Minimum begins size

#define HS_FNV1A_64_OFFSET 0xcbf29ce484222325
#define HS_FNV1A_64_PRIME 0x00000100000001b3

#include <memory>
#include <string.h>
#include <iostream>

typedef unsigned long long	u64;

template <typename DATA>
struct		cell
{
	char	*key;
	DATA	data;
};

template <typename DATA>
void		fakefree(DATA *cont)
{
	cont = NULL;
}

template <typename DATA>
class				HashTable
{
	protected:
		u64 		_count; // amount of values
		u64			_size; // amout of allocated space for 1 cell
		cell<DATA>	*_heap; // heap
		void		(*_delf)(DATA *cont); // free func for deletes content of cells

		void		_grow_the_heap(void); // reallocate heap for more cells
		u64			_get_index(const char *key); // get index by key, returns tables size if no space left
		u64			_hash2(const char *key); // second function for hash
		u64			_hash1(const char *key); // first function for hash
		bool		_is_free_index(u64 hi); // is this index free
		bool		_grow_trigger(void); // if true, we need to grow the heap
		u64			_power2round(u64 num); // Rounds the number to nearest bigger power of 2
	
	public:
		HashTable(u64 size =HS_STD_SIZE, void (*del_callback)(DATA *cont) =fakefree);
		~HashTable(void);
		DATA		*get(const char *key); // get DATA by key
		void		del(const char *key); // del cell by key
		void		set(const char *key, DATA data); // set or add cell with DATA and key
		u64			getcount(void); // get amount of elements
		void		print(void);
};

template <typename DATA>
inline bool	HashTable<DATA>::_grow_trigger(void)
{
	return ((this->_count * 4) / 3 > this->_size);
}

u64			fake(const char *key, u64 fake)
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

// Prints out information about hash table
// Size and amount of elemnets, and information about each item.
// Prints a real index, "first try" index, key and value.
template <typename DATA>
void		HashTable<DATA>::print(void)
{
	size_t	i = 0;

	if (this->_count == 0)
		return ;
	std::cout << "\nHASH TABLE INFO:";
	std::cout << "\nsize: " << this->_size << "\ncount: " << this->_count;
	std::cout << "\n\nELEMENTS:";
	for (;i<this->_size; ++i)
	{
		if (this->_is_free_index(i))
			continue ;
		std::cout << "\n===================";
		std::cout << "\nhi/fi: " << i << "/" << fake((this->_heap[i]).key, this->_size);
		std::cout << "\nkey: " << (this->_heap[i]).key;
		std::cout << "\nval: " << (this->_heap[i]).data;
	}
	std::cout << "\n===================\n";
}

template <typename DATA>
inline u64	HashTable<DATA>::_power2round(u64 num)
{
	u64 i;

	for (i = 0; num != 0; ++i)
		num >>= 1;
	return (1 << i);
}

template <typename DATA>
inline bool	HashTable<DATA>::_is_free_index(u64 hi)
{
	return((this->_heap[hi]).key == nullptr);
}

template <typename DATA>
u64			HashTable<DATA>::_get_index(const char *key)
{
	u64		i; // try
	u64		hi; // index

	for (i = 0; i < this->_size; ++i)
	{
		hi = (this->_hash1(key) + i * this->_hash2(key)) % this->_size;
		if (this->_is_free_index(hi))
			return (hi);
		if (!strcmp((this->_heap[hi]).key, key))
			return (hi);
	}
	return (this->_size);
}

template <typename DATA>
u64			HashTable<DATA>::_hash2(const char *key)
{
	u64 	hash = 0;

	while (*key)
	{
		hash = ((hash << 4) + hash) + u64(*key);
		key += 1;
	}
	if (this->_size < 2)
		return (1);
	hash = ((hash << 1) + 1) % this->_size;
	return (hash);
}

template <typename DATA>
u64			HashTable<DATA>::_hash1(const char *key)
{
	// fnv1a
	u64 	hash = HS_FNV1A_64_OFFSET;

	while (*key)
	{
		hash ^= u64(*key);
		hash *= HS_FNV1A_64_PRIME;
		key += 1;
	}
	return (hash);
}

template <typename DATA>
void		HashTable<DATA>::_grow_the_heap(void)
{
	cell<DATA>	*old_heap = this->_heap;
	u64			old_size = this->_size;
	u64			i;
	u64			hi;

	this->_size *= 2;
	this->_heap = new cell<DATA>[this->_size];
	bzero(this->_heap, this->_size * sizeof(cell<DATA>));
	for (i = 0; i < old_size; ++i)
	{
		if (old_heap[i].key == nullptr)
			continue ;
		hi = this->_get_index(old_heap[i].key);
		this->_heap[hi] = old_heap[i];
	}
	delete[] old_heap;
}

template <typename DATA>
HashTable<DATA>::HashTable(u64 size, void (*del_callback)(DATA *cont))
{
	if (size < HS_STD_SIZE)
		this->_size = HS_STD_SIZE;
	else
		this->_size = this->_power2round(size - 1);
	this->_delf = del_callback;
	this->_count = 0;
	this->_heap = new cell<DATA>[this->_size];
	bzero(this->_heap, sizeof(cell<DATA>) * this->_size);
}

template <typename DATA>
HashTable<DATA>::~HashTable(void)
{
	u64			i;
	cell<DATA>	*ptr;

	for (i = 0; i < this->_size; ++i)
	{
		ptr = this->_heap + i;
		delete ptr->key;
		ptr->key = nullptr;
		this->_delf(&ptr->data);
	}
	delete[] this->_heap;
}

template <typename DATA>
void	HashTable<DATA>::set(const char *key, DATA data)
{
	u64			hi;
	cell<DATA>	*ptr;

	if (this->_grow_trigger())
		_grow_the_heap();
	hi = this->_get_index(key);
	ptr = this->_heap + hi;
	if (this->_is_free_index(hi))
	{
		this->_count += 1;
		ptr->key = strdup(key);
		ptr->data = data;
		return ;
	}
	this->_delf(&ptr->data);
	ptr->data = data;
}

template <typename DATA>
DATA*	HashTable<DATA>::get(const char *key)
{
	u64			hi;
	cell<DATA>	*ptr;
	DATA		*dt_ptr;

	hi = this->_get_index(key);
	if (hi == this->_size || this->_is_free_index(hi))
		return nullptr;
	ptr = this->_heap + hi;
	dt_ptr = &(ptr->data);
	return (dt_ptr);
}

template <typename DATA>
void	HashTable<DATA>::del(const char *key)
{
	u64			hi;
	cell<DATA>	*ptr;

	hi = this->_get_index(key);
	if (hi == this->_size || this->_is_free_index(hi))
		return ;
	ptr = this->_heap + hi;
	delete ptr->key;
	ptr->key = nullptr;
	this->_count -= 1;
	this->_delf(&ptr->data);
}

template <typename DATA>
inline u64		HashTable<DATA>::getcount(void)
{
	return (this->_count);
}
