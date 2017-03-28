/*
В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел
башню максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на
плечах, третий стоит на плечах у второго и т.д.
Каждый атлет характеризуется силой si(kg) и массой mi(kg). Сила — это максимальная масса, которую
атлет способен держать у себя на плечах.
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической
подготовкой, и у них не было времени на изучение языков программирования. Помогите им, напишите
программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее:
если mi>mj, то si> sj.

Атлеты равной массы могут иметь различную силу.
*/
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Man
{
	int weight;
	int strength;
};

class ManArr
{
public:
	ManArr();
	~ManArr();
	void Push(const Man& data);
	int Count() const;
	void Sort(Man* arr = NULL, int n = -1);
	const Man & operator[] (int i) const;

	Man* ptr;
	int allocatedSize;
	int count;
};

ManArr::ManArr()
{
	this->allocatedSize = 1;
	this->count = 0;
	this->ptr = new Man;
	assert(this->ptr != NULL);
}

ManArr::~ManArr()
{
	delete[] this->ptr;
}

void ManArr::Push(const Man& data)
{
	if (this->count == this->allocatedSize)
	{
		int newSize = this->allocatedSize * 2;
		Man *tPtr = this->ptr;
		Man *newPtr = new Man[newSize];
		assert(newPtr != NULL);
		memcpy(newPtr, tPtr, this->allocatedSize * sizeof(Man));
		delete tPtr;
		this->ptr = newPtr;
		allocatedSize = newSize;
	}
	this->ptr[this->count++] = data;
}

int ManArr::Count() const
{
	return this->count;
}

void ManArr::Sort(Man* arr, int n)
{
	if (arr == NULL)
	{
		arr = this->ptr;
	}
	if (n < 0)
	{
		n = this->Count() - 1;
	}

	int i = 0;
	int j = n;
	Man half = arr[n / 2];
	do 
	{
		while (arr[i].weight < half.weight)
		{
			i++;
		}
		while (arr[j].weight > half.weight)
		{
			j--;
		}
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0)
	{
		this->Sort(arr, j);
	}
	if (n > i)
	{
		this->Sort(arr + i, n - i);
	}
}

const Man & ManArr::operator[](int i) const
{
	return this->ptr[i];
}

int GetHeight(ManArr &mans)
{
	mans.Sort();
	int height = 1;
	int totalWeight = mans[0].weight;
	for (int i = 1; i < mans.Count(); i++)
	{
		if (totalWeight <= mans[i].strength)
		{
			totalWeight += mans[i].weight;
			height++;
		}
	}
	return height;
}


int main()
{
	ManArr mans;
	Man m;
	while (scanf("%d %d", &m.weight, &m.strength) == 2)
	{
		assert(m.weight >= 0);
		assert(m.strength >= 0);
		mans.Push(m);
	}

	cout << GetHeight(mans);

	return 0;
}
