#ifndef ALLOCATOR_H__
#define ALLOCATOR_H__

class Allocator
{
public:
	static void* Relloc(const void* _ptr, const size_t& _newsize);
	static void Free(void* _ptr);
};


#endif // !ALLOCATOR_H__
