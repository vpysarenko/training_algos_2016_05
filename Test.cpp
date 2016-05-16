// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>
#include <string>

using namespace std;

typedef std::function<int(int*, int, int)> SearchFunc;

int linear_sort(int* A, int size, int key)
{
	assert(size >= 0);
	for (int i = 0; i < size; ++i)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}


int linear_sort_optimized(int* A, int size, int key)
{
	assert(size >= 0);
	A[size] = key;
	int i = 0;

	while (A[i] != key)
	{
		++i;
	}

	if (i == size)
		return -1;

	return i;
}

int linear_sort_tricky(int* A, int size, int key)
{
	assert(size >= 0);

	if (size == 0)
		return -1;

	int back = size - 1;

	if (A[back] == key)
		return back;

	int lastElement = A[back];
	A[back] = key;

	int i = 0;

	while (A[i] != key)
	{
		++i;
	}

	A[back] = lastElement;

	if (i == back)
		return -1;

	return i;
}


bool checkSort( SearchFunc sort, int A[], int size, int targetIndex )
{
	return (targetIndex == sort(A, size, 1));

	int test1[10];
	int size1 = 0;
	int key = 5;

	int test2[10] = { 2 };
	int size2 = 1;

	int test3[10] = { 5 };
	int size3 = 1;

	int test4[10] = { 5 };

	return false;
}

struct TestData
{
	int input[10];
	int size;
	int answer;
	std::string description;
};

struct FunctionWrapper
{
	SearchFunc func;
	std::string description;
};

int main()
{
	std::vector<FunctionWrapper> functions =
	{ 
		{ linear_sort, "linear_sort"}, 
		{ linear_sort_optimized, "linear_sort_optimized" },
		{ linear_sort_tricky, "linear_sort_tricky" }
	};

	std::vector<TestData> testData = {
		{
			{}, 0, -1, "Trivial empty"
		},
		{
			{2}, 1, -1, "Trivial one element, no key"
		},
		{
			{1}, 1, 0, "Trivial one element, key exists"
		},
		{
			{1, 2}, 2, 0, "Two elements, has key"
		},
		{
			{ 3, 4 }, 2, -1, "Two elements, no key"
		},
		{
			{ 3, 8, 1, 10 }, 4, 2, "Four elements, has key"
		},
		{
			{ 3, 8, 2, 10 }, 4, -1, "Four elements, has key"
		}
	};

	for (FunctionWrapper wrapper : functions)
	{
		for (TestData test : testData)
		{
			if (!checkSort(wrapper.func, test.input, test.size, test.answer))
			{
				cout << "Test failed: " << wrapper.description << " - " << test.description << endl;
			}
		}
	}

	system("pause");
    return 0;
}


