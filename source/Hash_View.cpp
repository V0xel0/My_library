#include<cstdlib>

#include "Hash_View.hpp"
#include "Allocators.hpp"

//TODO: Extend tests:
	//TODO: Assertion based tests
	//TODO: External data 
	//TODO: Overflow, corner cases checking
	
void test_hash_view()
{
	constexpr u32 max_elements = 100;
	byte *buffer = (byte *)malloc(KiB(64));
	Alloc_Arena arena { KiB(64), buffer };

	Hash_View_32 simple = {};
	simple.init(&arena, 100);

	// inserting check
	simple.set(3, 23);
	simple.set(4, 22);
	simple.set(1253, 65);
	simple.set(6, 27);
	simple.set(3, 77);
	simple.set(5, 79);
	simple.set(8, 188);

	// check early return
	simple.lookup(2503); 

	// lookup check
	u32 wtf = 
			simple.lookup(3);
	wtf = 	simple.lookup(4);
	wtf = 	simple.lookup(6);
	wtf = 	simple.lookup(1253);

	// removal check
	simple.remove(999); // non existent key
	simple.remove(1253);

	// lookup after removal check
	wtf = simple.lookup(4);
	wtf = simple.lookup(6);
	wtf = simple.lookup(1253);
}