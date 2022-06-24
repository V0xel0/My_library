#include "VM_Array.hpp"

struct SomeData
{
	int a;
	char c;
};

//TODO: Do proper tests!
void test_vm_array()
{
	VM_Array<SomeData> data ( GiB(1), 18400);
	data.add_elements_0(18400);
	for (auto& el : data)
	{
		el.a = 30;
		el.c = 'b';
	}
}