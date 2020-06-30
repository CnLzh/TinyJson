#include"Allocator.h"

#include<iostream>

void* Allocator::Relloc(const void* _ptr, const size_t& _newsize)
{
	return Relloc(_ptr, _newsize);
}

void Allocator::Free(void* _ptr)
{
	std::free(_ptr);
}
