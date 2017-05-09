/*
4_2. ​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>
#include <cassert>
#include <utility>

using std::cin;
using std::cout;
using std::swap;

int findPivot(int *arr, int left, int right)
{
	int mid = (right + left) / 2;
	if (arr[left] > arr[right]) swap(right, left);
	if (arr[left] > arr[mid]) swap(left, mid);
	if (arr[mid] > arr[right]) swap(mid, right);
	return mid;
}

int partition(int *arr, int left, int right)
{
	int pivPos = findPivot(arr, left, right-1);

	swap(arr[left], arr[pivPos]);

	int i = right - 1;
	int j = right - 1;
	int pivot = arr[left];
	while (i > left && arr[i] >= pivot)
	{
		i--;
	}
	if (i <= left)
	{
		return left;
	}
	j = i - 1;
	while (j > left)
	{
		if (arr[j] <= pivot)
		{
			j--;
		}
		else
		{
			swap(arr[j], arr[i]);
			i--;
			j--;
		}
	}
	swap(arr[i], arr[left]);
	return i;
}

int findKStatistic(int *arr, int n, int k)
{
	int pivPos = 0;
	int	left = 0;
	int	right = n;
	while (left < right) 
	{
		if ((pivPos = partition(arr, left, right)) == k) 
		{
			return arr[pivPos];
		}
		else if (pivPos > k) 
		{
			right = pivPos;
		}
		else
		{
			left = pivPos + 1;
		}
	}
	return arr[pivPos];
}


int main()
{
	int n = 0;
	cin >> n;
	assert(n >= 0);
	int *arr = new int[n];

	int k = 0;
	cin >> k;
	assert(k >= 0);

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	cout << findKStatistic(arr, n, k);

	delete[] arr;

    return 0;
}

