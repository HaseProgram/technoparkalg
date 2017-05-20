// Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#define HASH_1 37
#define HASH_2 59
#define REHASH_K 3.0 /4.0

using std::vector;
using std::string;
using std::cin;
using std::cout;

int Hash(string s, int mod, int hashArg)
{
	int result = 0;
	for (int i = 0; i < s.size(); i++)
	{
		result += result * hashArg + s[i];
		result %= mod;
	}
	return result;
}

int Hash1(string s, int mod)
{
	return Hash(s, mod, HASH_1);
}

int Hash2(string s, int mod)
{
	return (2 * Hash(s, mod, HASH_2) % mod) + 1;
}

struct Node
{
	string Data;
	bool isDeleted;
};

class HashTable
{
public:
	HashTable(int initSize);
	~HashTable();

	bool Exists(string s);
	bool Add(string s);
	bool Delete(string s);

private:
	vector<Node*> HashNodes;
	int allocated;
	int size;

	void Rehash();
};

HashTable::HashTable(int initSize)
{
	size = 0;
	allocated = initSize;
	HashNodes.resize(initSize);
}

HashTable::~HashTable()
{
}

bool HashTable::Exists(string s)
{
	int hash1 = Hash1(s, allocated);
	int hash2 = Hash2(s, allocated);

	int i = 0;
	while (HashNodes[hash1] != NULL && i < allocated)
	{
		if (HashNodes[hash1]->Data == s && !HashNodes[hash1]->isDeleted)
		{
			return true;
		}
		hash1 += hash2;
		hash1 %= allocated;
		i++;
	}
	return false;
}

bool HashTable::Add(string s)
{
	if ((double)size / allocated >= REHASH_K)
	{
		Rehash();
	}

	int hash1 = Hash1(s, allocated);
	int hash2 = Hash2(s, allocated);

	int i = 0;
	int deletedIndex = -1;
	while (HashNodes[hash1] != NULL && i < allocated)
	{
		if (HashNodes[hash1]->Data == s && !HashNodes[hash1]->isDeleted)
		{
			return false;
		}

		if (HashNodes[hash1]->isDeleted)
		{
			if (deletedIndex < 0) deletedIndex = hash1;
		}

		hash1 += hash2;
		hash1 %= allocated;
		i++;
	}

	if (deletedIndex >= 0)
	{
		HashNodes[deletedIndex]->Data = s;
		HashNodes[deletedIndex]->isDeleted = false;
	}
	else
	{
		Node* t = new Node;
		assert(t != NULL);
		t->Data = s;
		t->isDeleted = false;
		HashNodes[hash1] = t;
	}

	size++;
	return true;
}

bool HashTable::Delete(string s)
{
	int hash1 = Hash1(s, allocated);
	int hash2 = Hash2(s, allocated);

	int i = 0;
	while (HashNodes[hash1] != NULL && i < allocated)
	{
		if (HashNodes[hash1]->Data == s && !HashNodes[hash1]->isDeleted)
		{
			HashNodes[hash1]->isDeleted = true;
			size--;
			return true;
		}
		hash1 += hash2;
		hash1 %= allocated;
		i++;
	}
	return false;
}

void HashTable::Rehash()
{
	int newSize = allocated * 2;
	vector<Node*> newHashNodes;
	newHashNodes.resize(newSize);
	for (int i = 0; i < allocated; ++i)
	{
		if (HashNodes[i] != NULL && !HashNodes[i]->isDeleted)
		{
			string data = HashNodes[i]->Data;
			int cHash = Hash1(data, newSize);
			int nHash = Hash2(data, newSize);

			for (int k = 0; k < newSize && newHashNodes[cHash] != NULL; k++)
			{
				cHash += nHash;
				cHash %= newSize;
			}
			Node* t = new Node;
			t->Data = data;
			t->isDeleted = false;
			newHashNodes[cHash] = t;
		}
	}

	HashNodes = newHashNodes;
	allocated = newSize;
}

int main()
{
	char command;
	string str;

	HashTable* hTable = new HashTable(8);

	while (cin >> command >> str)
	{
		bool result;

		switch (command)
		{
		case '+' :
			result = hTable->Add(str);
			break;
		case '-':
			result = hTable->Delete(str);
			break;
		case '?':
			result = hTable->Exists(str);
			break;
		default:
			result = false;
			break;
		}
		
		if (result)
		{
			cout << "OK\n";
		}
		else
		{
			cout << "FAIL\n";
		}
	}
	delete hTable;
    return 0;
}
