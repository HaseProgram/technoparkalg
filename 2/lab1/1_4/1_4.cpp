/*
1_4. Строки.
Напишите программу, печатающую набор строк в лексикографическом порядке.
Строки разделяются символом перевода строки '\n'. Если последний символ в потоке ввода '\n',
считать, что после него нет пустой строки. Максимальная длина строки 255 символов. Написать
свою функцию сравнения строк.
*/
#include "stdio.h"
#include <cassert>

using namespace std;

template <typename T>
int StrCmp(const T a1, const T b1)
{
	T a = a1;
	T b = b1;
	while (*a && *b && *a == *b)
	{
		++a, ++b;
	}
	return *b - *a;
}

template <typename T>
void InsertationSort(T * arr, int len, int(*cmp)(const T, const T))
{
	for (int i = 1; i < len; i++)
	{
		T temp = arr[i];
		int j;
		for (j = i; j > 0 && StrCmp(temp, arr[j - 1]) > 0; j--)
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

int main()
{
	int amount = 0;
	scanf("%d\n", &amount);
	assert(amount >= 0);	

	char** stringArr = new char*[amount];
	assert(stringArr != NULL);
	for (int i = 0; i < amount; i++)
	{
		stringArr[i] = new char[255];
		assert(stringArr[i] != NULL);
		int j = 0;
		while ((stringArr[i][j++] = fgetc(stdin)) != '\n');
		stringArr[i][j-1] = '\0';
	}

	InsertationSort<char*>(stringArr, amount, StrCmp);

	for (int i = 0; i < amount; i++)
	{
		printf("%s\n", stringArr[i]);
	}
	
	for(int i = 0; i < amount; i++)
	{
		delete[] stringArr[i];
	}
	delete[] stringArr;

    return 0;
}

