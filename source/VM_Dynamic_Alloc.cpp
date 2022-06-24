
#include<chrono>
#include <omp.h>

#include "VM_Dynamic_Alloc.hpp"

using namespace std::chrono;

//TODO: The below is an old first iteration code

struct SomeData
{
	int a;
	char c;
};

void test_vm_alloc()
{
	SYSTEM_INFO sysInfo = {};
	GetSystemInfo(&sysInfo);
	u64 pageSize = sysInfo.dwPageSize;
	u64 gran = sysInfo.dwAllocationGranularity;

	MEMORYSTATUSEX memStatus = {};
	memStatus.dwLength = sizeof(memStatus);
	GlobalMemoryStatusEx(&memStatus);
	u64 availPhysicalMemory = memStatus.ullAvailPhys;

	u64 desiredSpace = GiB(1);
	u64 requiredPages = desiredSpace / pageSize;

	time_point<high_resolution_clock> start, end;
	duration<long long, std::micro>spent;

	LPVOID baseAdress = nullptr;
	omp_set_num_threads(12);

	

//TODO: MAKE UNIT TESTS!
//TODO: MAKE EXAMPLES
#if 1
	// Example with pre-reservation of address space and then commiting
	SomeData* example = (SomeData*)VirtualAlloc(nullptr, desiredSpace, MEM_RESERVE, PAGE_READWRITE);
	//! This will commit minimum 4KB anyway - pagesize
	example = (SomeData*)VirtualAlloc(example, 512 * sizeof(SomeData), MEM_COMMIT, PAGE_READWRITE);
	example[0].a = 3;
	example[0].c = 's';
	// We either move base to next page boundry or increase the commit size accordingly (in ex it would be 1024)
	example = (SomeData*)VirtualAlloc(example, 1024 * sizeof(SomeData), MEM_COMMIT, PAGE_READWRITE);
	//-example -= 512;
	example[299].a = 299;
	example[299].c = 'd';
	int wtf = example[0].a;
	// This will properly free from the first commit
	VirtualFree(example, 0, MEM_RELEASE);

	//? --------------------------------------TESTS---------------------------------------------------------------------------------------
	// vrarray example
	SomeData* bulk = nullptr;
	start = high_resolution_clock::now();
	vm_alloc_reserve(&bulk, GiB(1), 18400);
	vm_alloc_add(&bulk, 1850);
	vm_alloc_add(&bulk, 9850);
	vm_alloc_add(&bulk, 3850);
	vm_alloc_add(&bulk, 2850);
	end = high_resolution_clock::now();
	//vm_array_free(bulk);
	spent = duration_cast<microseconds> (end - start);

	start = high_resolution_clock::now();
	std::vector<SomeData>otherBulk(18400);
	end = high_resolution_clock::now();
	spent = duration_cast<microseconds> (end - start);

	//? ----------------------------------------------------------------------------------------------------------------------------------
#endif
}