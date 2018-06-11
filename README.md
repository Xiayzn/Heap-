# Heap-
关于堆的相关操作，堆的初始化、对堆进行判空、堆的创建、堆的调整、堆的插入、堆的删除、堆的元素个数、取堆顶元素

//Heap.h
#ifndef __HEAP_H__
#define __HEAP_H__

#pragma once
typedef int Datatype;
//动态顺序表
typedef struct Heap
{
	Datatype* _array;
	int _size;
	int _capacity;
}Heap;


//堆的初始化
void InitHeap(Heap* hp);
//对堆进行判空
int EmptyHeap(Heap* hp);
//堆的创建
void CreatHeap(Heap* hp, Datatype* array, int size);
//堆的调整
void AdjustDown(Heap* hp, int parent);
//堆的插入
void InsertHeap(Heap* hp, Datatype data);
//堆的删除
void DeleteHeap(Heap* hp);
//堆的元素个数
int SizeHeap(Heap* hp);
//取堆顶元素
Datatype TopHeap(Heap* hp);

//优先级队列

#endif //__HEAP_H__
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

//Heap.c
#include "Heap.h"
#include<stdio.h>
#include<malloc.h>
#include<assert.h>

void InitHeap(Heap* hp)
{
	Datatype* temp = NULL;
	if (NULL == hp)
		return;

	//给堆申请空间
	temp = (Datatype*)malloc(sizeof(Datatype)*2);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	hp->_array = temp;
	hp->_capacity = 0;
	hp->_size = 0;
}

int EmptyHeap(Heap* hp)
{
	return NULL == hp;
}
void Swap(Datatype* Left, Datatype* Right)
{
	assert(Left);
	assert(Right);
	Datatype temp;
	temp = *Left;
	*Left = *Right;
	*Right = temp;
}
void AdjustDown(Heap* hp, int parent)
{
	int size = hp->_size;
	int child = parent*2 +1;

	if (NULL == hp)
		return;

	while (child < size)
	{
		//找到左右孩子中的较小值
		if (hp->_array[child] > hp->_array[child + 1])
		{
			child += 1;
		}

		//如果孩子比size大说明该孩子不存在 循环不进入
		if (child < size && hp->_array[parent] > hp->_array[child])
		{
			Swap(&hp->_array[parent], &hp->_array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}
void CreatHeap(Heap* hp, Datatype* array, int size)
{
	Datatype* temp = NULL;
	int i = 0;
	int last = ((size-2)>>1);
	if (NULL == hp)
		return;

	//给堆申请空间
	temp = (Datatype*)malloc(sizeof(Datatype)*size);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	hp->_array = temp;
	hp->_capacity = size;
	hp->_size = size;

    //元素搬移
	for (int i = 0; i < size; ++i)
	{
		hp->_array[i] = array[i];
	}

	//堆调整（从最后一个非叶子结点开始调整）
	for (; last >= 0; --last)
	{
		AdjustDown(hp, last);
	}
}
void CheckCapacity(Heap* hp)
{
	int i = 0;
	Datatype* temp = NULL;
	assert(hp);
	if (hp->_size >= hp->_capacity)
	{
		//重新申请空间
		int NewCapacity = hp->_capacity * 2;

		temp = (Datatype* )malloc(sizeof(Datatype)*NewCapacity);
		if( NULL == temp)
		{
			assert(0);
			return;
		}
		//搬移元素
		for (i = 0; i < hp->_size; ++i)
		{
			temp[i] = hp->_array[i];
		}
		//释放原空间
		free(hp->_array);
		hp->_array = NULL;
		hp->_capacity = NewCapacity;
		hp->_array = temp;
	}
}

void AdjustUp(Heap* hp, int child)
{
	int parent = ((child - 1) >> 1);
	assert(hp);
	while (child)
	{
		if (child < hp->_size && hp->_array[child] < hp->_array[parent])
		{
			Swap(&hp->_array[child], &hp->_array[parent]);
			child = parent;
			parent = ((child - 1) >> 1);
		}
		else
			return;
	}
}

void InsertHeap(Heap* hp, Datatype data)
{
	int child = 0;
	if (NULL == hp)
		return;
	
	CheckCapacity(hp);
	hp->_array[hp->_size++] = data;//为什么不用创建结点？顺序表已经给定空间不需要再创建
	child = hp->_size - 1;
	AdjustUp(hp, child);
}

void _AdjustDown(Heap* hp, int parent)
{
	int child = parent * 2 + 1;
	assert(hp);

	while (child < hp->_size)
	{
		//找到左右孩子中的较小值
		if (hp->_array[child] > hp->_array[child + 1])
			child += 1;
		if (child < hp->_size && hp->_array[parent] > hp->_array[child])
		{
			Swap(&hp->_array[parent], &hp->_array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}

}
void DeleteHeap(Heap* hp)
{
	if (NULL == hp)
		return;

	hp->_array[0] = hp->_array[--hp->_size];//顺序表 删除元素只需要将 size-- 最后面一个元素就取不到了
	_AdjustDown(hp, 0);

}

int SizeHeap(Heap* hp)
{
	assert(hp);
	/*if (NULL == hp)
		return 0;*/

	return hp->_size;
}

Datatype TopHeap(Heap* hp)
{
	assert(!EmptyHeap(hp));//断言当条件为假时触发 

	return hp->_array[0];
}

////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//test.c
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
