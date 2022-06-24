#pragma once

#include <cassert>
#include "Utils.hpp"
#include "Views.hpp"

struct Slot_Map_Extern_Key
{
	u32 id;
	u32 gen;
};

struct Slot_Map_Slot
{
	u32 gen;
    u32 pos;
	u32 data_key;
};

//? Slot_Map_Extern_Key is provided and managed from the "outside", 
//! gen external generation HAS TO START FROM VALUE >0!, value 0 in this View means empty/invalid slot
//! key id external generation must be from 0 to n where n is max number of elements for Slot_Map_View

//? gen of 0 in the Slot_Map_View is assumed to be the first insert for that id
//? key id is basically a 1:1 mapping for list of slots which keeps track of pos in data
//? data_key is a mapping for data to get to what key id data corresponds to. Data pos/index is a "key" in slots to get data_key
//? pos is a mapping for key id to get to what position/index it corresponds to in data - this is needed to keep data,
//? tightly packed in "data" whereas keys in Slot are 'scattered'

//? "View" means POD is assumed, everything is passed/returned by copy(value), no internal allocation, fixed size

//TODO: Further Bound checking and proper handling of invalid keys!
//TODO: Reset function

template<typename T>
struct Slot_Map_View
{
	Array_View<T>data;
	T *invalid_value;
    Slot_Map_Slot *list;

	constexpr void init(const auto& allocator, const s32 elements)
	{
		assert(elements > 0);
		data.init(allocator, elements);
		list = allocate<Slot_Map_Slot>(allocator, elements);
		invalid_value = nullptr;
	}
	
    constexpr void insert(const T& el, const Slot_Map_Extern_Key key)
    {
		assert((s32)key.id < data.size && "Key id is too big!");
		assert((s32)key.gen > 0 && "Key gen is invalid!");
		
        u32 pos = list[key.id].pos; // accesor function
		const u32 gen = list[key.id].gen;
		
        if( gen == 0)
        {
			pos = data.count;
            data.push(el);
			list[pos].data_key = key.id;
        }
		else
			data[pos] = el;
	
        list[key.id].gen = key.gen; 
        list[key.id].pos = pos;    
    }
	
	constexpr T* get(const Slot_Map_Extern_Key key)
	{
		assert((s32)key.id < data.size && "Key id is too big!");
		
		const u32 pos = list[key.id].pos; // accesor function
		const u32 gen = list[key.id].gen;
		T *out = invalid_value;
		
		if (gen == key.gen)
			out = &data[pos];
		return out;
	}
	
	constexpr void erase(const Slot_Map_Extern_Key key)
	{
		assert(data.count > 0 && "Tried to erase from empty slot map!");
		assert((s32)key.id < data.size && "Key id is too big!");
		
		const u32 gen = list[key.id].gen; // accesor function
		const u32 pos = list[key.id].pos;
		const u32 last_element_key = list[data.count-1].data_key;
		
		if (gen == key.gen)
		{
			list[key.id].gen = 0;
			data.erase_swap(pos);
			list[last_element_key].pos = pos;
			list[last_element_key].gen = gen;
		}
	}
};
