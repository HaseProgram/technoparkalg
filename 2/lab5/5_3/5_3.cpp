/*
ƒана последовательность целых чисел из диапазона (-10^9 .. 10^9). ƒлина последовательности не
больше 10^6. „исла записаны по одному в строке.  оличество чисел не указано.
ѕусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
“ребуетс€ напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
*/

#include "stdlib.h"
#include "string.h"
#include <cassert>
#include <iostream>

using namespace std;

int64_t Merge(int *arr, int left, int mid, int right)
{
	int iter1 = 0;
	int iter2 = 0;
	int *buf = new int[right - left];
	int64_t result = 0;
	int64_t med = (right - left) / 2;
	while ((left + iter1 < mid) && (mid + iter2 < right))
	{
		if (arr[left + iter1] <= arr[mid + iter2])
		{
			buf[iter1 + iter2] = arr[left + iter1];
			iter1++;
		}
		else
		{
			result += med - iter1;
			buf[iter1 + iter2] = arr[mid + iter2];
			iter2++;
		}
	}
	while (left + iter1 < mid)
	{
		buf[iter1 + iter2] = arr[left + iter1];
		iter1++;
	}
	while (left + iter1 < mid)
	{
		buf[iter1 + iter2] = arr[mid + iter2];
		iter2++;
	}
	for (int i = 0; i < iter1 + iter2; i++)
	{
		arr[left + i] = buf[i];
	}
	delete[] buf;
	return result;
}

int64_t MergeSort(int *arr, int left, int right)
{
	if (left + 1 >= right) return 0;
	int64_t result = 0;
	int mid = (left + right) / 2;
	result += MergeSort(arr, left, mid);
	result += MergeSort(arr, mid, right);
	result += Merge(arr, left, mid, right);
	return result;
}

int64_t GetNumber(int *arr, int size)
{
	return MergeSort(arr, 0, size);
}


int main()
{
	int alloc = 10;
	int *arr = new int[alloc];

	int i = 0;
	while (cin >> arr[i])
	{
		i++;
		if (i >= alloc)
		{
			int newAlloc = alloc * 2;
			int *tArr = arr;
			int *newArr = new int[newAlloc];
			assert(newArr != NULL);
			memcpy(newArr, tArr, alloc * sizeof(int));
			delete[] tArr;
			arr = newArr;
			alloc = newAlloc;
		}
	}

	/*for (int j = 0; j < i; j++)
	{
		cout << arr[j] << " ";
	}*/

	cout << GetNumber(arr, i);

	delete[] arr;

    return 0;
}

