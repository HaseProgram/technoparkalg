/*
Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение
суммы двух чисел равно их сумме.
Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в
зависимости от порядка вычислений.
Требуется написать программу, которая определяет минимальное время, достаточное для
вычисления суммы заданного набора чисел.
*/

#include <iostream>
#include <cassert>

using namespace std;

class Heap
{
public:
	Heap(int);
	~Heap();

	void Add(int);
	int GetMin();
	int GetSize() const;

private:
	int *arr;
	int size;
	void SiftUp(int);
	void SiftDown(int);
};

Heap::Heap(int sz)
{
	arr = new int[sz];
	size = 0;
}

Heap::~Heap()
{
	delete[] arr;
}

void Heap::Add(int item)
{
	arr[size++] = item;
	SiftUp(size - 1);
}

int Heap::GetMin()
{
	int temp = arr[0];
	swap(arr[0], arr[--size]);
	SiftDown(0);
	return temp;
}

int Heap::GetSize() const
{
	return size;
}

void Heap::SiftUp(int index)
{
	while (arr[index] < arr[(index - 1) / 2]) // index == 0 : root
	{
		swap(arr[index], arr[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

void Heap::SiftDown(int index)
{
	while (2 * index + 1 < size)
	{
		int left = 2 * index + 1;	// left child
		int right = 2 * index + 2;	// right child
		int j = left;
		if (right < size && arr[right] < arr[left])
		{
			j = right;
		}
		if (arr[index] <= arr[j])
		{
			return;
		}
		swap(arr[index], arr[j]);
		index = j;
	}
}

int process(Heap& heap)
{
	int time = 0;
	int sum = 0;
	while (heap.GetSize() > 1)
	{
		sum = heap.GetMin() + heap.GetMin();
		heap.Add(sum);
		time += sum;
	}
	return time;
}

int main()
{
	int size = 0;
	cin >> size;
	assert(size >= 0);

	Heap heap(size);

	int item = 0;
	for (int i = 0; i < size; i++)
	{
		cin >> item;
		heap.Add(item);
	}

	cout << process(heap);

    return 0;
}

