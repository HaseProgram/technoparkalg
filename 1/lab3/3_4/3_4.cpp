/*
3_4. ​Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для
каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по
значению к B[i]. Время работы поиска для каждого элемента B[i]: O(log(k)).
n ≤ 110000, m ≤ 1000.
*/

#include <cassert>
#include <iostream>
using namespace std;

int search(int *A, int sizeA, int bI)
{
	int left = 0;
	int right = 0;
	int tA = A[0]; // temporary value from A array to check if left border is new element
	int t = 1;
	while (t < sizeA)
	{
		if (A[t] > tA+1 && A[t] < bI)
		{
			left = t;
		}
		t *= 2;
		right = t;
		if (t < sizeA && A[t] >= bI)
		{
			break;
		}
	}

	// Binary search
	if (left > sizeA - 1)
	{
		left = sizeA - 1;
	}
	if (right > sizeA - 1)
	{
		right = sizeA - 1;
	}


	if (bI <= A[left])
	{
		return left;
	}
	if (bI >= A[right])
	{
		return right;
	}

	while (left <= right)
	{
		int middle = left + (right - left) / 2;
		if (A[middle] < bI)
		{
			left = middle + 1;
		}
		if (A[middle] > bI)
		{
			right = middle - 1;
		}
		if (A[middle] == bI)
		{
			return middle;
		}
	}
	if (abs(bI - A[left]) >= abs(bI - A[right]))
	{
		return right;
	}
	return left;
}

int main()
{
	int sizeA = 0;
	cin >> sizeA;
	assert(sizeA > 0);
	
	int* A = new int[sizeA];
	assert(A != NULL);

	for (int i = 0; i < sizeA; i++)
	{
		cin >> A[i];
	}

	int sizeB = 0;
	cin >> sizeB;
	assert(sizeB > 0);
	
	int* B = new int[sizeB];
	assert(B != NULL);

	for (int i = 0; i < sizeB; i++)
	{
		cin >> B[i];
	}

	for (int i = 0; i < sizeB; i++)
	{
		cout << search(A, sizeA, B[i]) << " ";
	}

	delete[] A;
	delete[] B;

	getchar();
	getchar();
	return 0;
}

