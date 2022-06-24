#pragma once

#include <cassert>
#include "Utils.hpp"
#include "Views.hpp"

struct Bulk_List_Key
{
	s32 id;
	u32 gen;
};

template<typename T>
struct Bulk_List_Item
{
	u32 gen;
	s32 freelist_next;
};

//? Bulk_List_Key is owned and managed by Bulk_List_View
//? id is index in data and is managed by free-list
//! gen effective count starts from 1, value 0 means empty/invalid slot

//? This View allows logical 'holes' in data managment
//? The "list" is a lookup free-list into "data"
//? "invalid value" allows to specify what to return in case when not valid key is provided

//? "View" means POD is assumed, everything is passed/returned by copy(value), no internal allocation, fixed size

template<typename T>
struct Bulk_List_View
{
	Array_View<T> data;
	T *invalid_value;
	Bulk_List_Item *list;
	s32 head;

	constexpr void reset()
	{
		assert(data != nullptr && "Bulk List is not initalized!");

		head = data.size; // value for empty
		s32 last_slot = head - 1;

		for (s32 i = last_slot; i >= 0; i--)
		{
			list[i].gen = 0;
			list[i].next = head;
			head = i;
		}
	}

	constexpr void init(const auto& allocator, const s32 elements)
	{
		assert(elements > 0);
		data.init(allocator, elements);
		list = allocate<Bulk_List_Item>(allocator, elements);
		invalid_value = nullptr;

		reset();
	}

	[[nodiscard]]
	constexpr Bulk_List_Key insert(const T& el)
	{
		assert(head != data.size && "No more space!");

		Bulk_List_Key out{};
		out.id = head;
		head = list[head].freelist_next;
		out.gen = ++list[out.id].gen;
		data[out.id] = el;
		data.count++;

		return out;
	}

	constexpr void erase(const Bulk_List_Key key)
	{
		assert(data.count > 0 && "Tried to erase from empty Bulk List!");
		assert(key.id < data.size && "Key id is too big!");
		assert(key.id >= 0 && "Key id is too small!");

		if ( key.gen == list[key.id].gen )
		{
			list[key.id].freelist_next = head;
			head = key.id;
			list[key.id].gen = 0;
			data.count--;
		}
	}

	constexpr T* get(const Bulk_List_Key key)
	{
		assert(key.id < data.size && "Key id is too big!");
		assert(key.id >= 0 && "Key id is too small!");
		assert(data.count > 0 && "No elements in list!");

		T *out = invalid_value;

		if (list[key.id].gen == key.gen)
			out = data[key.id];
		
		return out;
	}
};
