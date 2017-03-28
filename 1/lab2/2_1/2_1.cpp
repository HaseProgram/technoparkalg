#include <iostream>
using namespace std;

void search(int *A, int *B, int arrSize, int *i0, int *j0)
{
	int maxA = A[0];
	int maxAPos = 0;


	for (int i = 0; i < arrSize; i++)
	{
		if (A[i] > maxA)
		{
			maxAPos = i;
			maxA = A[i];
		}

		
		if (A[maxAPos] + B[i] > A[*i0] + B[*j0])
		{
			*i0 = maxAPos;
			*j0 = i;
		}
	}
}

int main()
{
	int* A;
	int* B;
	int arrSize;

	cin >> arrSize;

	if (arrSize <= 0)
	{
		cout << "[error]";
		return 0;
	}

	A = new int[arrSize];
	if (!A)
	{
		cout << "[error]";
		return 0;
	}
	B = new int[arrSize];
	if (!B)
	{
		cout << "[error]";
		delete[] A;
		return 0;
	}

	for (int i = 0; i < arrSize; i++)
	{
		cin >> A[i];
	}

	for (int i = 0; i < arrSize; i++)
	{
		cin >> B[i];
	}

	int i0 = 0;
	int j0 = 0;

	search(A, B, arrSize, &i0, &j0);
	
	cout << i0 << " " << j0;

	delete[] A;
	delete[] B;
	return 0;
}
