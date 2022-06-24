#include <cstdlib>

#include "Slot_Map_View.hpp"
#include "Allocators.hpp"

global_variable u32 g_id = 0;
global_variable u32 g_gen_id = 1;

//TODO: Finish tests!
void test_slot_map()
{
	byte *memBuffer = (byte *)malloc(MiB(128));
	Alloc_Arena arena = { MiB(64), memBuffer };

	//Array_View<s32>arr = { 11, 0, arenaPush<s32>(&arena, 3)};
	Slot_Map_View<s32>slots;
	slots.init(&arena, 11);

	slots.insert(-12, {g_id++, g_gen_id++});
	slots.insert(12, {g_id++, g_gen_id++});
	slots.insert(-64, {g_id++, g_gen_id++});
	slots.insert(32, {g_id++, g_gen_id++});
}
