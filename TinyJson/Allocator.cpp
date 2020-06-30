#include"Allocator.h"

#include<iostream>

void* Allocator::Realloc(void* _ptr, const size_t& _newsize)
{
	return realloc(_ptr, _newsize);
}

void Allocator::Free(void* _ptr)
{
	std::free(_ptr);
}
