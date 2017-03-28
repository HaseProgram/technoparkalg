/*
​Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью
динамического буфера.
*/

#include <cassert>
#include <iostream>

using namespace std;

class Stack
{
public:
	int *item;
	int itemCount;

	Stack();
	Stack(size_t size);
	~Stack();

	void Push(int newItem);
	int Pop();
	int Count();

private:
	size_t size;
};

Stack::Stack()
{
	this->size = 1;
	this->itemCount = 0;
	this->item = new int[size];
	assert(this->item != NULL);
}

Stack::Stack(size_t size)
{
	this->size = size;
	assert(size > 0);
	this->itemCount = 0;
	this->item = new int[size];
	assert(this->item != NULL);
}

Stack::~Stack()
{
	delete[] this->item;
}

void Stack::Push(int newItem)
{
	if (this->itemCount == this->size)
	{
		this->size *= 2;
		this->item = (int*)realloc(this->item, this->size * sizeof(*this->item));
		assert(this->item != NULL);
	}
	this->item[this->itemCount] = newItem;
	this->itemCount++;
}

int Stack::Pop()
{
	this->itemCount--;
	return this->item[this->itemCount];
}

int Stack::Count()
{
	return this->itemCount;
}

class Queue
{
public:
	Stack *head;
	Stack *tail;
	int itemCount;

	Queue();
	~Queue();

	void Push(int newItem);
	int Pop();
};

Queue::Queue()
{
	this->head = new Stack();
	assert(this->head != NULL);
	this->tail = new Stack();
	assert(this->tail != NULL);
}

Queue::~Queue()
{
	delete this->head;
	delete this->tail;
}

void Queue::Push(int newItem)
{
	this->tail->Push(newItem);
}

int Queue::Pop()
{
	if (this->head->Count() == 0)
	{
		if (this->tail->Count() == 0)
		{
			return -1;
		}
		while (this->tail->Count() > 0)
		{
			this->head->Push(this->tail->Pop());
		}
	}
	return this->head->Pop();
}

bool handler(Queue &queue, int com, int val)
{
	switch (com)
	{
	case 2:
		return queue.Pop() == val;
		break;
	case 3:
		queue.Push(val);
		return true;
		break;
	}
}

int main()
{
	Queue queue;

	int commandCount = 0;
	cin >> commandCount;
	bool flag = true;
	for (int i = 0; i < commandCount; i++)
	{
		int com = 0;
		cin >> com;
		int val = 0;
		cin >> val;
		flag = flag && handler(queue, com, val);
	}
	if (flag)
	{
		cout << "YES";
	}
	else
	{
		cout << "NO";
	}

    return 0;
}
