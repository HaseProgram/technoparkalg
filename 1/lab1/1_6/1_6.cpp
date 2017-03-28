#include <iostream>
using namespace std;

void inv(int **numberArray, int numberArraySize)
{
	int *nA = *numberArray;
	for (int i = 0; i < numberArraySize / 2; i++)
	{
		int temp = nA[i];
		nA[i] = nA[numberArraySize - i - 1];
		nA[numberArraySize - i - 1] = temp;
	}
}

int main()
{
	int numberArraySize = 0;

	cin >> numberArraySize;

	if (numberArraySize <= 0)
	{
		return 0;
	}

	int* numberArray = new int[numberArraySize];

	for (int i = 0; i < numberArraySize; i++)
	{
		cin >> numberArray[i];
	}

	inv(&numberArray, numberArraySize);

	for (int i = 0; i < numberArraySize; i++)
	{
		cout << numberArray[i] << " ";
	}

	delete[] numberArray;
    return 0;
}

