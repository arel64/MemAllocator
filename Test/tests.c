#include "../Mem/allocator.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>


void setArray(char *arr, unsigned length, char value)
{
	for (int i = 0; i < length; ++i)
	{
		arr[i] = value;
		if (i == length - 1)
			arr[i] = '\0';
	}
}
void testAllocationAndFree(void **state)
{
	char *arrays[100];
	srand(time(NULL));

	unsigned long arrMemSize;
	for (int i = 0; i < 100; ++i)
	{
		arrMemSize = sizeof(char) * rand() % 20;
		arrays[i] = malloc(arrMemSize);
		setArray(arrays[i], arrMemSize, 'a' + rand() % 26);
	}
	for (int i = 0; i < 100; i++)
	{
		free(arrays[i]);
		arrays[i] = NULL;
	}
}
void testGeneralDefrag(void **state)
{
	int len = 100;
	int array[len];
	for (int i = 0; i < len; ++i)
	{
		array[len] = malloc(sizeof(int));
	}
	for (int i = 0; i < len; i += 2)
	{
		free(array[len]);
	}

	while
}


/* These functions will be used to initialize
   and clean resources up after each test run */
int setup(void **state)
{
	initDefragger(&freeList);
	return 0;
}

int teardown(void **state)
{
	defragKill();
	return 0;
}


int test(void)
{

	const struct CMUnitTest tests[] =
	        {
	                cmocka_unit_test_setup_teardown(testAllocationAndFree, setup, teardown),
	        };

	/* If setup and teardown functions are not
       needed, then NULL may be passed instead */

	int count_fail_tests =
	        cmocka_run_group_tests(tests, setup, teardown);

	return count_fail_tests;
}