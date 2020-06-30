#ifndef STACK_H__
#define STACK_H__

#include"Allocator.h"

class Stack
{
private:
	char* _stack;
	char* _stack_top;
	char* _stack_end;

	template<typename T>
	void Expand(const size_t& count);

	void Resize(const size_t& new_size);

public:
	Stack();
	~Stack();

	template<typename T>
	T* Push(const size_t& count = 1);

	template<typename T>
	T* Pop(const size_t& count);

	size_t GetSize() const;

};

Stack::Stack()
	:_stack(0), _stack_top(0), _stack_end(0)
{

}
Stack::~Stack()
{
	Allocator::Free(this->_stack);
}

template<typename T>
void Stack::Expand(const size_t& count)
{
	size_t new_size = 0;
	if (this->_stack)
	{
		new_size = static_cast<size_t>(this->_stack_end - this->_stack);
		new_size += new_size / 2;
	}
	size_t tmp_new_size = GetSize() + sizeof(T) * count;
	if (new_size < tmp_new_size)
		new_size = tmp_new_size;

	Resize(new_size);
}

void Stack::Resize(const size_t& new_size)
{
	const size_t size = GetSize();
	this->_stack = (char*)Allocator::Realloc(this->_stack, new_size);
	this->_stack_top = this->_stack + size;
	this->_stack_end = this->_stack + new_size;
}

template<typename T>
T* Stack::Push(const size_t& count)
{
	if (this->_stack_top + sizeof(T) * count >= this->_stack_end)
		this->Expand<T>(count);

	T* ret = reinterpret_cast<T*>(this->_stack_top);
	this->_stack_top += sizeof(T) * count;
	return ret;
}

template<typename T>
T* Stack::Pop(const size_t& count)
{
	this->_stack_top -= count * sizeof(T);
	return reinterpret_cast<T*>(this->_stack_top);

}

size_t Stack::GetSize() const
{
	return static_cast<size_t>(this->_stack_top - this->_stack);
}
#endif // !STACK_H__
