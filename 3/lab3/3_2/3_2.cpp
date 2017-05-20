// 2_3.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <cassert>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

struct Node
{
	int Data;
	Node *left;
	Node *right;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	void Add(int data);

	void Postorder();
	void Postorder(Node *node);
	int GetMaxWidth();
private:
	Node *root;
};

BinaryTree::BinaryTree()
{
	root = NULL;
}

BinaryTree::~BinaryTree()
{
	if (root == NULL)
	{
		return;
	}

	vector<Node*> st1;
	vector<Node*> st2;

	st1.push_back(root);
	while (!st1.empty())
	{
		Node *temp = st1.back();
		st1.pop_back();
		st2.push_back(temp);
		if (temp->left != NULL)
		{
			st1.push_back(temp->left);
		}
		if (temp->right != NULL)
		{
			st1.push_back(temp->right);
		}
	}

	while (!st2.empty())
	{
		delete st2.back();
		st2.pop_back();
	}
}

void BinaryTree::Postorder()
{
	Postorder(root);
}

void BinaryTree::Postorder(Node *node)
{
	if (node == NULL)
	{
		return;
	}

	vector<Node*> st1;
	vector<Node*> st2;

	st1.push_back(node);
	while (!st1.empty())
	{
		Node *temp = st1.back();
		st1.pop_back();
		st2.push_back(temp);
		if (temp->left != NULL)
		{
			st1.push_back(temp->left);
		}
		if (temp->right != NULL)
		{
			st1.push_back(temp->right);
		}
	}

	while (!st2.empty())
	{
		cout << st2.back()->Data << " ";
		st2.pop_back();
	}

}

int BinaryTree::GetMaxWidth()
{
	vector<Node*> st;
	st.push_back(root);
	int max = 0;
	while (!st.empty())
	{
		int count = st.size();
		if (count > max)
		{
			max = count;
		}
	}
}

void BinaryTree::Add(int data)
{
	Node *newNode = new Node;
	assert(newNode != NULL);
	newNode->Data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if (root == NULL)
	{
		root = newNode;
		return;
	}

	Node *nextNode = root;
	while (1)
	{
		if (data > nextNode->Data)
		{
			if (nextNode->right == NULL)
			{
				nextNode->right = newNode;
				return;
			}
			else
			{
				nextNode = nextNode->right;
			}
		}
		else
		{
			if (nextNode->left == NULL)
			{
				nextNode->left = newNode;
				return;
			}
			else
			{
				nextNode = nextNode->left;
			}
		}
	}
}

int main()
{
	
}

