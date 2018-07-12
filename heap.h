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
