#include "Heap.h"
#include<stdio.h>

void TestInitHeap()
{
	Heap heap;
	InitHeap(&heap);
}

void TestCreatHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size);
}
void TestInsertHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size);
	InsertHeap(&heap, 16);
}

void TestDeleteHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size);
	InsertHeap(&heap, 16);
	DeleteHeap(&heap);
	DeleteHeap(&heap);
}

void TestSizeHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size);
	printf("堆中元素的个数 %d \n",SizeHeap(&heap));
}

void TestTopHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size);
	printf("堆顶元素为 %d \n", TopHeap(&heap));
}
int main()
{
	//TestInitHeap();
	TestCreatHeap();
	//TestInsertHeap();
	//TestDeleteHeap();
	//TestSizeHeap();
	//TestTopHeap();
	return 0;
}
