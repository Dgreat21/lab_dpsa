#pragma once

#ifndef ULONG_TPDF
# define UNLONG_TPDF
typedef unsigned long	ulong;
#endif

// Standart size of block for allocating new memomry for array used in stack
# define STACKARR_BLKSZ	64

template	<typename T>
class		StackAR
{
	private:
	ulong	allocated; // Size of allocated array
	ulong	sp; // Stack top index: [0 - allocated]
	T		*array; // Pointer for stack

	public:
	StackAR(void);
	~StackAR(void);
	
	void	push(T);
	T		pop(void);
	ulong	size(void);
	void	print(void);
	T		top(void);
};
