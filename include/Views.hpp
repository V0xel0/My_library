#pragma once

#include <cassert>
#include <cstring>

#include "Utils.hpp"

//TODO: Extend String_View implementation

template<typename T>
struct Array_View
{
	s32 size;
	s32 count;
	T *data;

	constexpr T& operator[] (s32 i)
	{
		assert(i < count && i >= 0); return data[i];
	}

	constexpr const T& operator[] (s32 i) const
	{
		assert(i < count && i >= 0); return data[i];
	}

	constexpr void set_count(const s32 count_to_set)
	{
		assert(count_to_set <= size && count_to_set >= 0);
		count = count_to_set;
	}

	constexpr void push(const T& el)
	{
		assert(count+1 <= size);
		data[count++] = el;
	}

	constexpr void pop()
	{
		assert(count > 0);
		--count;
	}

	constexpr void erase_swap(const s32 i)
	{
		assert(i < count && i >= 0);
		data[i] = data[--count];
	}

	constexpr T* begin()
	{
		return data;
	}

	constexpr const T* begin() const
	{
		return data;
	}

	constexpr T* end()
	{
		return data + count;
	}

	constexpr const T* end() const
	{
		return data + count;
	}

	inline void init(const auto& allocator, const s32 elements)
	{
		assert(elements > 0);
		data = allocate<T>(&allocator, elements);
		size = elements;
		count = 0;
	}

	void reset()
	{
		assert(data != nullptr);
		memset(data, 0, sizeof(T) * size);
	}
};

struct String_View
{
	char *str;
	s32 size;

	constexpr char& operator[] (const s32 i)
	{
		assert(i < size); return str[i];
	}

	constexpr const char& operator[] (const s32 i) const
	{
		assert(i < size); return str[i];
	}

	constexpr char* begin()
	{
		return str;
	}

	constexpr const char* begin() const
	{
		return str;
	}

	constexpr char* end()
	{
		return str + size;
	}

	constexpr const char* end() const
	{
		return str + size;
	}

	inline void init(const auto& allocator, const s32 elements)
	{
		str = allocate<char>(allocator, elements);
		size = elements;
	}
};