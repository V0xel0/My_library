#include <cstdlib>

#include "Views.hpp"
#include "Allocators.hpp"

struct Som_Data
{
	int a;
	float b;
	char c;
};

void test_views()
{
	Alloc_Arena arena { KiB(64), (byte *)malloc( KiB(64) ) };
	Array_View<Som_Data> array;
	array.init(&arena, 10);
	array.set_count(array.size);

	for(int i = 0; i < array.size; ++i)
	{
		array[i] = { i, i + 1.69f, (i + 141) % 173 };
	}

	for(int i = 0; i < array.size; ++i)
	{
		array.pop();
	}
	
	for(int i = 0; i < array.size; ++i)
	{
		array.push( { i, i + 1.69f, (i + 141) % 173 } );
	}

	// Overflow check
	#if 0
		array.push({});
	#endif		
}