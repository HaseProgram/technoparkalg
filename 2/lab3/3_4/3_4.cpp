/*
Ќа числовой пр€мой окрасили N отрезков. »звестны координаты левого и правого концов каждого
отрезка (Li и Ri). Ќайти сумму длин частей числовой пр€мой, окрашенных ровно в один слой.
*/

#include <iostream>
#include <cassert>

using namespace std;

typedef struct
{
	int coord;
	bool start;
} line;

bool operator > (const line &l1, const line &l2)
{
	return (l1.coord == l2.coord) ? (l1.start > l2.start) : (l1.coord > l2.coord);
}


template <typename T>
void SiftDown(T *arr, int index, int size)
{
	while (2 * index + 1 < size)
	{
		int left = 2 * index + 1;	// left child
		int right = 2 * index + 2;	// right child
		int j = left;
		if (right < size && arr[right] > arr[left])
		{
			j = right;
		}
		if (arr[index] > arr[j])
		{
			return;
		}
		swap(arr[index], arr[j]);
		index = j;
	}
}

template <typename T>
void BuildHeap(T *arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; --i)
	{
		SiftDown(arr, i, size);
	}
}

template <typename T>
T GetExt(T *arr, int &size)
{
	T ext = arr[0];
	arr[0] = arr[--size];
	SiftDown(arr, 0, size);
	return ext;
}

template <typename T>
void HeapSort(T *arr, int size)
{
	BuildHeap(arr, size);
	int tSize = size;
	while(size > 0)
	{
		T ext = GetExt(arr, size);
		arr[size] = ext;
	}
}

int FindSum(line *arr, int size)
{
	int layer = 0;
	int start = 0;
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i].start)
		{
			layer++;
			if (layer == 1)
			{
				start = arr[i].coord;
			}
			else if (layer == 2)
			{
				sum += (arr[i].coord - start);
			}
		}
		else
		{
			layer--;
			if (layer == 0)
			{
				sum += (arr[i].coord - start);
			}
			else if (layer == 1)
			{
				start = arr[i].coord;
			}
		}
	}
	return sum;
}

int main()
{
	int amount = 0;
	cin >> amount;
	assert(amount >= 0);

	line *larr = new line[amount*2];
	assert(larr != NULL);
	line item;
	for (int i = 0; i < amount*2; i+=2)
	{
		cin >> item.coord;
		item.start = true;
		larr[i] = item;
		cin >> item.coord;
		item.start = false;
		larr[i + 1] = item;
	}

	HeapSort<line>(larr, 2*amount);
	cout << FindSum(larr, 2 * amount);

	delete[] line;

    return 0;
}

