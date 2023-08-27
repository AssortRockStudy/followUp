#pragma once
#include <assert.h>

enum NODETYPE
{
	PARENT = 0,
	LCHILD,
	RCHILD,
	MAX
};

template <typename t1, typename t2>
struct Pair
{
	t1 first;
	t2 second;
};

template <typename t1, typename t2>
struct BSTNode
{
	Pair<t1, t2>		data;
	BSTNode<t1, t2>*	ptr[MAX];
public:
	BSTNode(){}
	BSTNode(Pair<t1, t2> pair = nullptr, BSTNode<t1, t2>* parent = nullptr, BSTNode<t1, t2>* lchild = nullptr, BSTNode<t1, t2>* rchild = nullptr)
		: data(pair)
	{
		ptr[PARENT] = parent;
		ptr[LCHILD] = lchild;
		ptr[RCHILD] = rchild;
	}
	~BSTNode(){}
};

template <typename t1, typename t2>
class BST
{
private:
	BSTNode<t1, t2>*	m_RootNode;
	int					m_Count;

public:
	void insert(Pair<t1, t2> pair);
	void clear();

public:
	BST(){}
	~BST()
	{
		clear();
	}
};

template<typename t1, typename t2>
inline void BST<t1, t2>::insert(Pair<t1, t2> pair)
{
	BSTNode<t1, t2>* newNode = new BSTNode<t1, t2>(pair);
	// ���� ù �������� ���
	if (0 == m_Count)
	{
		m_RootNode = newNode;
		++m_Count;
		return;
	}
	// ù �����Ͱ� �ƴ� ���
	BSTNode<t1, t2>* buf = m_RootNode;
	while (true)
	{
		if (buf->data.first < newNode->data.first) // ���ۺ��� Ŭ ���
		{
			if (buf->ptr[RCHILD] != nullptr)
				buf = buf->ptr[RCHILD];
			else // �ڽ� �ڸ� ã��
			{
				buf->ptr[RCHILD] = newNode;
				break;
			}
		}
		else if (buf->data.first > newNode->data.first) // ���ۺ��� ���� ���
		{
			if (buf->ptr[LCHILD] != nullptr)
				buf = buf->ptr[LCHILD];
			else // �ڽ� �ڸ� ã��
			{
				buf->ptr[LCHILD] = newNode;
				break;
			}
		}
		else // Ű �� �����Ͱ� ���� ���... HashMap�� ��쿡�� �����͸� �����ٰ� �Ѵ�. �غ���?
		{
			buf->data.second = newNode->data.second;
			delete newNode;
			return;
		}
	}
	++m_Count;
}

template<typename t1, typename t2>
inline void BST<t1, t2>::clear()
{
}
