#include <immintrin.h>

#include "Allocators.hpp"
#include "Views.hpp"

void test_allocators()
{
	byte *memBuffer = (byte *)_aligned_malloc(MiB(128), 32);
	Alloc_Arena global_arena { MiB(128), memBuffer };
	auto d = defer([&] { _aligned_free(memBuffer); });
	
	// Arena tests
	{
		struct Som_Data
		{
			s32 a;
			char b;
		};

		Alloc_Arena arena = arena_from_allocator(&global_arena, MiB(32));
		auto d1 = defer([&] { arena_reset(&global_arena); });

		auto g = allocate<Som_Data>(&arena);
		// Array_View<SomData>arr = { 3, 0, allocate<SomData>(&arena, 3)};
		Array_View<Som_Data>arr{};
		arr.init(&arena, 3);

		arr.push({2, 'a'});
		arr.push({-5, 'b'});
		arr.push({12, 'c'});
		
		{
			arena_start_temp(&arena);
			auto d2 = defer([&] { arena_end_temp(&arena); });
			auto&&[str, size] = arena_push_string(&arena, "Nice funny ");
			String_View view {str, size};
		}

		arr = { 9, arr.count, arena_resize_last(&arena, arr.data, 9) };
		arr.push({5, 'd'});
		arr.push({7, 'e'});
	}

	// Stack tests
	{
		struct Som_Data
		{
			s32 a;
			char b;
		};

		Alloc_Stack stack = stack_from_allocator(&global_arena, MiB(32));
		auto d3 = defer([&] { arena_reset(&global_arena); });

		auto alignmentH = alignof(Alloc_Stack_Header);

		auto el = allocate<Som_Data>(&stack);
		assert(stack.curr_offset == 24 && stack.last_header_offset == 0 && "FAILED");
		auto el1 = allocate<byte>(&stack, 11);
		assert(stack.curr_offset == 51 && stack.last_header_offset == 24 && "FAILED");
		auto el2 = allocate<Som_Data>(&stack);
		assert(stack.curr_offset == 80 && stack.last_header_offset == 56 && "FAILED");

		stack_pop(&stack);
		assert(stack.curr_offset == 51 && stack.last_header_offset == 24 && "FAILED");
		stack_pop(&stack);
		assert(stack.curr_offset == 24 && stack.last_header_offset == 0 && "FAILED");
		stack_pop(&stack);
		assert(stack.curr_offset == 0 && stack.last_header_offset == 0 && "FAILED");

		el1 = allocate<byte>(&stack, 11);
		assert(stack.curr_offset == 27 && stack.last_header_offset == 0 && "FAILED");
		el = allocate<Som_Data>(&stack);
		assert(stack.curr_offset == 56 && stack.last_header_offset == 32 && "FAILED");
		auto el3 = allocate<byte>(&stack, 11);
		assert(stack.curr_offset == 83 && stack.last_header_offset == 56 && "FAILED");
		el = allocate<Som_Data>(&stack);
		assert(stack.curr_offset == 112 && stack.last_header_offset == 88 && "FAILED");

		stack_pop(&stack);
		assert(stack.curr_offset == 83 && stack.last_header_offset == 56 && "FAILED");
		stack_pop(&stack);
		assert(stack.curr_offset == 56 && stack.last_header_offset == 32 && "FAILED");
		stack_pop(&stack);
		assert(stack.curr_offset == 27 && stack.last_header_offset == 0 && "FAILED");
		stack_pop(&stack);
		assert(stack.curr_offset == 0 && stack.last_header_offset == 0 && "FAILED");

		el1 = allocate<byte>(&stack, 11);
		stack_pop(&stack);
		el = allocate<Som_Data>(&stack);
		el3 = allocate<byte>(&stack, 11);
		stack_pop(&stack);
		el = allocate<Som_Data>(&stack);
		stack_pop(&stack);
		stack_pop(&stack);
		assert(stack.curr_offset == 0 && stack.last_header_offset == 0 && "FAILED");
	}
	
	// Pool tests
	{
		struct Som_Data
		{
			s32 a;
			char b;
		};

		Alloc_Pool pool = pool_from_allocator( &global_arena, KiB(1), sizeof(Som_Data), alignof(Som_Data) );

		{
			Som_Data *el  = allocate<Som_Data>(&pool);
			Som_Data *el1 = allocate<Som_Data>(&pool);
			Som_Data *el2 = allocate<Som_Data>(&pool);
			Som_Data *el3 = allocate<Som_Data>(&pool);
			Som_Data *el4 = allocate<Som_Data>(&pool);

			// Allocate, free and allocate again to same block, ver.1
			{
				free_block(&pool, el2);
				Som_Data *el_new = allocate<Som_Data>(&pool);
				assert(el_new == el2 && "FAILED - it should be in the same block!");
			}
			// Allocate, free and allocate again to same block, ver.2
			{
				free_block(&pool, el);
				Som_Data *el_new = allocate<Som_Data>(&pool);
				assert(el_new == el && "FAILED - it should be in the same block!");
			}
			// Allocate, free and allocate again to same block, ver.3
			{
				free_block(&pool, el4);
				Som_Data *el_new = allocate<Som_Data>(&pool);
				assert(el_new == el4 && "FAILED - it should be in the same block!");
			}

			// Reset all and allocate again
			{
				reset_list(&pool);
				Som_Data *el_new  = allocate<Som_Data>(&pool);
				Som_Data *el_new1 = allocate<Som_Data>(&pool);
				Som_Data *el_new2 = allocate<Som_Data>(&pool);
				Som_Data *el_new3 = allocate<Som_Data>(&pool);
				Som_Data *el_new4 = allocate<Som_Data>(&pool);
				assert(el_new  == el  && "FAILED - it should be in the same block!");
				assert(el_new1 == el1 && "FAILED - it should be in the same block!");
				assert(el_new2 == el2 && "FAILED - it should be in the same block!");
				assert(el_new3 == el3 && "FAILED - it should be in the same block!");
				assert(el_new4 == el4 && "FAILED - it should be in the same block!");
			}
		}

		// Different size, gap check (4 byte data in 8 byte block)
		{
			reset_list(&pool);
			s32 *smol  = allocate<s32>(&pool);
			s32 *smol1 = allocate<s32>(&pool);
			s32 *smol2 = allocate<s32>(&pool);
			s32 *smol3 = allocate<s32>(&pool);
			byte *end = pool.base + pool.max_size;
			assert( (byte *)smol  == end - 1 * sizeof(Som_Data) && "FAILED - there should be padding gap between blocks!");
			assert( (byte *)smol1 == end - 2 * sizeof(Som_Data) && "FAILED - there should be padding gap between blocks!");
			assert( (byte *)smol2 == end - 3 * sizeof(Som_Data) && "FAILED - there should be padding gap between blocks!");
			assert( (byte *)smol3 == end - 4 * sizeof(Som_Data) && "FAILED - there should be padding gap between blocks!");
		}

		// Offset free - failure check (offseted 2 byte data in 8 byte block)
		#if 0
		{
			reset_list(&pool);
			s16 *smol  = allocate<s16>(&pool);
			free_block(&pool, (smol + 1) );
		}
		#endif
	}
}