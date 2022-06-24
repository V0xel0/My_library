#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <chrono>
#include <immintrin.h>

#define CATCH_CONFIG_RUNNER
#include "external/Catch2.hpp"

#include "Utils.hpp"

extern void test_allocators();
extern void test_views();
extern void	test_slot_map();
extern void	test_vm_array();
extern void	test_hash_view();
extern void test_vm_alloc();
extern void test_bulk_view();

int main( int argc, char* argv[]) 
{
	// New tests go through Catch2
	int result = Catch::Session().run( argc, argv );

	// Old tests
	test_allocators();
	test_views();
	test_slot_map();
	test_vm_alloc();
	test_vm_array();
	test_hash_view();
	test_bulk_view();

	system("pause");
}