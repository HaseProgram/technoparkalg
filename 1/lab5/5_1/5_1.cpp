/*
5_1. Скобочная последовательность.
Дан фрагмент последовательности скобок, состоящей из символов (){}[].
Требуется определить, возможно ли продолжить фрагмент в обе стороны, получив корректную
последовательность.
Длина исходной последовательности ≤ 200000.
Формат входных данных. Строка, содержащая символы (){}[] и, возможно, перевод строки.
Формат выходных данных. Если возможно - вывести минимальную корректную последовательность, иначе -
напечатать "IMPOSSIBLE​".
*/

#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

class Stack
{
public:
	Stack();
	Stack(size_t size);
	~Stack();

	void Push(int newItem);
	int Pop();
	int Count();

private:
	int *item;
	size_t itemCount;
	size_t size;
};

Stack::Stack()
{
	size = 1;
	itemCount = 0;
	item = new int[size];
	assert(item != NULL);
}

Stack::Stack(size_t size)
{
	assert(size > 0);
	this->size = size;
	itemCount = 0;
	item = new int[size];
	assert(item != NULL);
}

Stack::~Stack()
{
	delete[] item;
}

void Stack::Push(int newItem)
{
	if (itemCount == size)
	{
		size *= 2;
		item = (int*)realloc(item, size * sizeof(*item));
		assert(item != NULL);
	}
	item[itemCount] = newItem;
	itemCount++;
}

int Stack::Pop()
{
	itemCount--;
	return item[itemCount];
}

int Stack::Count()
{
	return itemCount;
}

char GetRel(char openedBracket)
{
	switch (openedBracket)
	{
	case '{':
		return '}';
		break;
	case '[':
		return ']';
		break;
	case '(':
		return ')';
		break;
	case '}':
		return '{';
		break;
	case ']':
		return '[';
		break;
	case ')':
		return '(';
		break;
	}
}

bool CheckCloseBracket(char bracket, Stack &opened, Stack &toAdd)
{
	if (opened.Count() > 0)
	{
		if (opened.Pop() != GetRel(bracket))
		{
			return false;
		}
	}
	else
	{
		toAdd.Push(GetRel(bracket));
	}
	return true;
}

void BuildOutput(Stack &opened, Stack &toAdd, char *input, char *output)
{
	int count = 0;
	count = toAdd.Count();
	int j = 0;
	for (; j < count; j++)
	{
		output[j] = toAdd.Pop();
	}
	output[count] = '\0';

	strcat(output, input);

	int i = strlen(input) + j;
	count = opened.Count() + i;
	for (int k = i; k < count; k++)
	{
		output[k] = GetRel(opened.Pop());
	}
	output[count] = '\0';
}

bool CheckPossibility(char *input, int inputLength, char *output)
{
	Stack opened(inputLength);
	Stack toAdd(inputLength);

	int count = strlen(input);

	for (int i = 0; i < count; i++)
	{
		switch (input[i])
		{
		case '{':
			opened.Push('{');
			break;
		case '[':
			opened.Push('[');
			break;
		case '(':
			opened.Push('(');
			break;
		case '}':
			if (!CheckCloseBracket('}', opened, toAdd))
			{
				return false;
			}
			break;
		case ']':
			if (!CheckCloseBracket(']', opened, toAdd))
			{
				return false;
			}
			break;
		case ')':
			if (!CheckCloseBracket(')', opened, toAdd))
			{
				return false;
			}
			break;
		}
	}

	BuildOutput(opened, toAdd, input, output);

	return true;
}

int main()
{
	int inputLength = 200000; // dynamic realocation is slow, ejudje time fails
	char* input = new char[inputLength];
	assert(input != nullptr);
	cin >> input;

	char *output = new char[inputLength * 2];
	assert(output != nullptr);

	if (CheckPossibility(input, inputLength, output))
	{
		cout << output;
	}
	else
	{
		cout << "IMPOSSIBLE";
	}

	delete[] input;
	delete[] output;

	return 0;
}

