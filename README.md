# Heap-
关于堆的相关操作，堆的初始化、对堆进行判空、堆的创建、堆的调整、堆的插入、堆的删除、堆的元素个数、取堆顶元素
//优先级队列


#ifndef __HEAP_H__
#define __HEAP_H__

#pragma once
typedef int Datatype;
typedef enum{less, greater}Compare;
//动态顺序表
typedef struct Heap
{
	Datatype* _array;
	int _size;
	int _capacity;
}Heap;

//堆的应用之优先级队列，用堆封装优先级队列 
typedef struct PriorityQueue
{
	Heap hp;
}PriorityQueue;

//堆的初始化
void InitHeap(Heap* hp);
//对堆进行判空
int EmptyHeap(Heap* hp);
//堆的创建  GLDM 排序方法
void CreatHeap(Heap* hp, Datatype* array, int size,Compare GLDM);
//堆的调整
void AdjustDown(Heap* hp, int parent,Compare GLDM);
//堆的插入
void InsertHeap(Heap* hp, Datatype data, Compare GLDM);
//堆的删除
void DeleteHeap(Heap* hp, Compare GLDM);
//堆的元素个数
int SizeHeap(Heap* hp);
//取堆顶元素
Datatype TopHeap(Heap* hp);


//优先级队列的初始化
void PriorityQueueInit(PriorityQueue* q);
//优先级队列的插入
void PriorityQueuePush(PriorityQueue* q, Datatype data, Compare GLDM);
//优先级队列的删除
void PriorityQueuePop(PriorityQueue* q, Compare GLDM);
//求优先级队列的元素个数
int PriorityQueueSize(PriorityQueue* q);
//求优先级队列中优先级最高的元素
int PriorityQueueTop(PriorityQueue* q);
//判定优先级队列是否为空
int PriorityQueueEmpty(PriorityQueue* q);

//用堆的思想实现堆排序
void Heapsort(int array[], int size, Compare GLDM);
//用堆解决top - K问题
void HeapTopK(int array[], int size, int k, Compare GLDM);
#endif //__HEAP_H__


#include "Heap_L_G.h"

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

int Less(Datatype Left, Datatype Right)
{
	return Left < Right;
}

int Greater(Datatype Left, Datatype Right)
{
	return Left > Right;
}
void InitHeap(Heap* hp)
{
	Datatype* temp = NULL;
	if (NULL == hp)
		return;

	//给堆申请空间
	temp = (Datatype*)malloc(sizeof(Datatype)* 2);
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
void AdjustDown(Heap* hp, int parent, Compare GLDM)
{
	int size = hp->_size;
	int child = parent * 2 + 1;

	if (NULL == hp)
		return;

	while (child < size)
	{
		if (GLDM == less)
		{
			//小堆   找到左右孩子中的较小值
			if (Less(hp->_array[child + 1], hp->_array[child]))
			{
				child += 1;
			}

			//如果孩子比size大说明该孩子不存在 循环不进入
			if (child < size && Less(hp->_array[child], hp->_array[parent]))
			{
				Swap(&hp->_array[parent], &hp->_array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				return;
		}
		else
		{
			//大堆   找到左右孩子中的较大值
			if (Greater(hp->_array[child + 1], hp->_array[child]))
			{
				child += 1;
			}

			//如果孩子比size大说明该孩子不存在 循环不进入
			if (child < size && Greater(hp->_array[child], hp->_array[parent]))
			{
				Swap(&hp->_array[parent], &hp->_array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				return;
		}

	
	}
}
void CreatHeap(Heap* hp, Datatype* array, int size, Compare GLDM)
{
	Datatype* temp = NULL;
	int i = 0;
	int last = ((size - 2) >> 1);
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
		AdjustDown(hp, last, GLDM);
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

		temp = (Datatype*)malloc(sizeof(Datatype)*NewCapacity);
		if (NULL == temp)
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

void AdjustUp(Heap* hp, int child, int GLDM)
{
	int parent = ((child-1)>>1);
	assert(hp);
	while (child)
	{
		if (GLDM == less)
		{
			if (child < hp->_size && Less(hp->_array[child] , hp->_array[parent]))
			{
				Swap(&hp->_array[child], &hp->_array[parent]);
				child = parent;
				parent = ((child - 1) >> 1);
			}
			else
				return;
		}
		else
		{
			if (child < hp->_size && Greater(hp->_array[child], hp->_array[parent]))
			{
				Swap(&hp->_array[child], &hp->_array[parent]);
				child = parent;
				parent = ((child - 1) >> 1);
			}
			else
				return;
		}

	}
}

void InsertHeap(Heap* hp, Datatype data, Compare GLDM)
{
	int child = 0;
	if (NULL == hp)
		return;

	CheckCapacity(hp);
	hp->_array[hp->_size++] = data;//为什么不用创建结点？顺序表已经给定空间不需要再创建
	child = hp->_size - 1;
	AdjustUp(hp, child, GLDM);
}

void _AdjustDown(Heap* hp, int parent, int GLDM)
{
	int child = parent * 2 + 1;
	assert(hp);

	while (child < hp->_size)
	{
		if (GLDM == less)
		{
			//找到左右孩子中的较小值
			if (Less(hp->_array[child + 1], hp->_array[child]))
				child += 1;
			if (child < hp->_size && Less(hp->_array[child], hp->_array[parent]))
			{
				Swap(&hp->_array[parent], &hp->_array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				return;
		}
		else
		{
			//找到左右孩子中的较大值
			if (Greater(hp->_array[child + 1], hp->_array[child]))
				child += 1;
			if (child < hp->_size && Greater(hp->_array[child], hp->_array[parent]))
			{
				Swap(&hp->_array[parent], &hp->_array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				return;
		}
	}

}
void DeleteHeap(Heap* hp, Compare GLDM)
{
	if (NULL == hp)
		return;

	if (GLDM == less)
	{
		hp->_array[0] = hp->_array[--hp->_size];//顺序表 删除元素只需要将 size-- 最后面一个元素就取不到了
		_AdjustDown(hp, 0, GLDM);
	}
	else
	{
		hp->_array[0] = hp->_array[--hp->_size];//顺序表 删除元素只需要将 size-- 最后面一个元素就取不到了
		_AdjustDown(hp, 0, GLDM);

	}

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

void PriorityQueueInit(PriorityQueue* q)
{
	assert(q);
	InitHeap(&q->hp);
	q->hp._capacity = 2;
}

void PriorityQueuePush(PriorityQueue* q, Datatype data, Compare GLDM)
{
	assert(q);
	InsertHeap(&q->hp, data, GLDM);
}

void PriorityQueuePop(PriorityQueue* q, Compare GLDM)
{
	assert(q);
	DeleteHeap(&q->hp, GLDM);
}

int PriorityQueueSize(PriorityQueue* q)
{
	assert(q);
	return SizeHeap(&q->hp);
}

int PriorityQueueTop(PriorityQueue* q)
{
	assert(q);
	return TopHeap(&q->hp);
}

int PriorityQueueEmpty(PriorityQueue* q)
{
	assert(q);
	return EmptyHeap(&q->hp);
}

void HeapAjust(int array[], int size, int root, Compare GLDM)
{
	
	int child = root * 2 + 1;


	while (child < size)
	{
		if (GLDM == less)
		{
			//小堆   找到左右孩子中的较小值
			if (array[child + 1] < array[child])
			{
				child += 1;
			}

			//如果孩子比size大说明该孩子不存在 循环不进入
			if (child < size && array[child]< array[root])
			{
				Swap(&array[root], &array[child]);
				root = child;
				child = root * 2 + 1;
			}
			else
				return;
		}
		else
		{
			//大堆   找到左右孩子中的较大值
			if (array[child + 1] > array[child])
			{
				child += 1;
			}

			//如果孩子比size大说明该孩子不存在 循环不进入
			if (child < size && array[child] > array[root])
			{
				Swap(&array[root], &array[child]);
				root = child;
				child = root * 2 + 1;
			}
			else
				return;
		}

	}
}

void Heapsort(int array[], int size, Compare GLDM)
{
	//1、建堆
	Heap hp;
	CreatHeap(&hp, array, size, GLDM);
	
	//从倒数第一个非叶子结点一直调整到根结点
	int root = ((size - 2) >> 1);
	int end = size - 1;

	for (; root >= 0; --root)
	{
		HeapAjust(array, size, root, GLDM);
	}

	//堆排序——堆删除
	while (end)
	{
		Swap(&array[end],&array[0]);
		HeapAjust(array, end, 0, GLDM);
		--end;
	}

}

void HeapTopK(int array[], int size, int k, Compare GLDM)
{
	Heap hp;
	int i = 0;
	CreatHeap(&hp, array, k, GLDM);

	if (GLDM == greater)
	{
		for (i = k; i < size; ++i)
		{
			if (Greater(array[i], TopHeap(&hp)))
			{
				hp._array[0] = array[i];
				AdjustDown(&hp, 0, GLDM);
			}
		}

	}
	else
	{
		for (i = k; i < size; ++i)
		{
			if (Less(array[i], TopHeap(&hp)))
			{
				hp._array[0] = array[i];
				AdjustDown(&hp, 0, GLDM);
			}
		}
	}
	
}


#include "Heap_L_G.h"
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
	CreatHeap(&heap, array, size, greater);
}
void TestInsertHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size, less);
	InsertHeap(&heap, 16, less);
}

void TestDeleteHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size, less);
	InsertHeap(&heap, 16, less);
	DeleteHeap(&heap, less);
	DeleteHeap(&heap, less);
}

void TestSizeHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size, less);
	printf("堆中元素的个数 %d \n", SizeHeap(&heap));
}

void TestTopHeap()
{
	Heap heap;
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23, 31 };
	int size = sizeof(array) / sizeof(array[0]);
	InitHeap(&heap);
	CreatHeap(&heap, array, size, less);
	printf("堆顶元素为 %d \n", TopHeap(&heap));
}

void TestPriorityQueueInit()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
}

void TestPriorityQueuePush()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5, greater);
	PriorityQueuePush(&q, 6, greater);
	PriorityQueuePush(&q, 1, greater);
	PriorityQueuePush(&q, 7, greater);
}

void TestPriorityQueuePop()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5, greater);
	PriorityQueuePush(&q, 6, greater);
	PriorityQueuePush(&q, 1, greater);
	PriorityQueuePush(&q, 7, greater);

	PriorityQueuePop(&q, greater);
	PriorityQueuePop(&q, greater);

}

void TestPriorityQueueSize()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5, greater);
	PriorityQueuePush(&q, 6, greater);
	PriorityQueuePush(&q, 1, greater);
	PriorityQueuePush(&q, 7, greater);

	printf("%d ",PriorityQueueSize(&q));
}

void TestPriorityQueueTop()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5, greater);
	PriorityQueuePush(&q, 6, greater);
	PriorityQueuePush(&q, 1, greater);
	PriorityQueuePush(&q, 7, greater);

	printf("%d ", PriorityQueueTop(&q));
}
void TestPriorityQueueEmpty()
{
	PriorityQueue q;
	PriorityQueueInit(&q);
	PriorityQueuePush(&q, 5, greater);
	PriorityQueuePush(&q, 6, greater);
	PriorityQueuePush(&q, 1, greater);
	PriorityQueuePush(&q, 7, greater);

	if (PriorityQueueEmpty(&q))
	{
		printf("优先队列为空\n");
	}
	else
	{
		printf("优先队列不为空\n");
	}
}
void TestHeapsort()
{
	int array[] = {9,6,3,8,7,10,4,5,0,2,1};
	int size = sizeof(array) / sizeof(array[0]);
	Heapsort(array,size,greater);
}
void TestHeapTopK()
{
	int array[] = { 9, 6, 3, 8, 7, 10, 4, 5, 0, 2, 1, 11, 12, 13, 14, 15, 56, 23, 12, 45, 46 };
	int size = sizeof(array) / sizeof(array[0]);
	HeapTopK(array, size, 10, greater);
}
int main()
{
	//TestInitHeap();
	//TestCreatHeap();
	//TestInsertHeap();
	//TestDeleteHeap();
	//TestSizeHeap();
	//TestTopHeap();
	//TestPriorityQueueInit();
	//TestPriorityQueuePush();
	//TestPriorityQueuePop();
	//TestPriorityQueueSize();
	//TestPriorityQueueTop();
	//TestPriorityQueueEmpty();
	//TestHeapsort();
	TestHeapTopK();
	return 0;
}
