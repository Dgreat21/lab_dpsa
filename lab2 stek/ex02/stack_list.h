#pragma once

#include "list.h"

#ifndef ULONG_TPDF
# define UNLONG_TPDF
typedef unsigned long	ulong;
#endif

template 	<typename T>
class		StackL
{
	private:
	List<T>		*node;
	ulong		size_;
	void		(*del)(T);

	public:
	StackL(void);
	StackL(void (*del)(T));
	~StackL(void);

	void		push(T);
	T			pop(void);
	ulong		size(void);
	void		print(void);
	T			top(void);
};
