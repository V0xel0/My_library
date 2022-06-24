#pragma once
#include <cstring>
#include <cassert>
#include "Utils.hpp"

//? Simple implemenation of hash table, values might be actual values ( if valueSize < 32bits) or indices to some value array ( if valueSize > 32 bits)
//? Only hash(key) are stored -> thats for what "keys" name refers to
//? Using open-addresing with "robin hood" and "backward shift" for deletion

//TODO: For now if no key found "-1" is returned for value
//TODO: Add hash function/functions
//TODO: Assertions? Check for possibility of overflows

static constexpr u64 HASH_UNUSED = 0xffffffffffffffffULL;
#define CalcDIB(a, b) ( ( (a) - (b) )  )

struct Hash_View_32
{
	u64 *keys;
	s32 *values;
	u32 buckets;
	u32 elements; // "logical" number of elements

	inline void init(auto *allocator, const u32 count)
	{
		const f32 waste = 0.2f;
		buckets = (u32)((f32)count * (1.0f + waste));
		keys = allocate<u64>(allocator, buckets);
		values = allocate<s32>(allocator, buckets);
		reset();
		elements = 0;
	}
	
	inline void reset()
	{
		memset(keys, 0xff, sizeof(u64) * buckets);
	}

	inline u32 lookup(u64 key)
	{
		u64 i = key % buckets;
		u64 dist = 0;
		while (keys[i] != key && keys[i] != HASH_UNUSED)
		{
			// We can return early thanks to robin hood, we can expect to never 
			// meet an element with shorter distance to initial bucket (DIB)
			if ( dist > CalcDIB(i, keys[i]) )
			{
				return 0;
			}
			i = (i + 1) % buckets;
			++dist;
		}
		return keys[i] == HASH_UNUSED ? -1 : values[i];
	}

	inline void set(u64 key, s32 value)
	{
		u64 i = key % buckets;
		u64 dist = 0;
		u64 currentDist = 0;
		while (keys[i] != key && keys[i] != HASH_UNUSED)
		{
			assert(keys[i] <= i);
			currentDist = CalcDIB(i, keys[i]);
			// The actual robin hood method
			if (currentDist < dist)
			{
				// swap keys
				key = key ^ keys[i];
				keys[i] = key ^ keys[i];
				key = key ^ keys[i];
				// swap values
				value = value ^ values[i];
				values[i] = value ^ values[i];
				value = value ^ values[i];

				dist = currentDist;
			}
			i = (i + 1) % buckets;
			++dist;
		}
		// Increase counter only if new key
		if (keys[i] != key)
		{
			elements++;
		}
		keys[i] = key;
		values[i] = value;
	}

	// Basically same as Lookup only returns index of key
	inline u64 find_hash_ID(u64 key)
	{
		u64 i = key % buckets;
		u64 dist = 0;
		while (keys[i] != key && keys[i] != HASH_UNUSED)
		{
			if ( dist > CalcDIB(i, keys[i]) )
			{
				return 0;
			}
			i = (i + 1) % buckets;
			++dist;
		}
		return keys[i] == HASH_UNUSED ? HASH_UNUSED : i;
	}

	inline void remove(u64 key)
	{
		u64 i = find_hash_ID(key);
		if (i == HASH_UNUSED)
		{
			return;
		}
		keys[i] = HASH_UNUSED;
		++i;
		// Backward shift technique
		while (keys[i] != HASH_UNUSED && CalcDIB(i, keys[i]) > 0)
		{
			keys[i - 1] = keys[i];
			keys[i] = HASH_UNUSED;
			values[i - 1] = values[i];
			++i;
		}
	}
};