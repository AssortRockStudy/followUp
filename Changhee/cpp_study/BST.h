#pragma once

#include <queue>

//	1. Pair 구조체 만들기 -> make_Pair 함수 구현
//	2. BSTnode 만들기
//	3. 포인터 종류 enum 만들기
//	4. BST class 구현 -> insert, clear 함수
//	5. DFS, BFS 구현
//	6. Depth, find, erase 구현 


template<typename T1, typename T2>
struct Pair{


	T1 first;
	T2 second;

	Pair(const T1& _first, const T2& _second) 
		: first(_first)
		, second(_second)
	{
	}
	
	~Pair()
	{
	}
};

template<typename T1, typename T2>
Pair<T1, T2>* make_Pair(const T1& _first, const T2& _second)
{
	return new Pair<T1, T2>(_first, _second);
}

enum PTR_TYPE
{
	PARENT,
	LCHILD,
	RCHILD,
	END,
};

template<typename T1, typename T2>
struct BSTNode
{
	Pair<T1, T2>*		data;
	BSTNode<T1, T2>*	ptr[PTR_TYPE::END];
	
	BSTNode()
		: data(nullptr)
		, ptr{}
	{
	}

	BSTNode(Pair<T1,T2>* _data , BSTNode<T1, T2>* _parent = nullptr , BSTNode<T1, T2>* _lchild = nullptr, BSTNode<T1, T2>* rchild = nullptr)
		: data(_data)
		, ptr{_parent, _lchild, rchild}
	{
	}

	~BSTNode()
	{
		delete data;
	}

};

template<typename T1, typename T2>
class BST
{
private:
	BSTNode<T1, T2>* m_pRoot;

public:
	void insert(Pair<T1,T2>* _data)
	{
		BSTNode<T1, T2>* newNode = new BSTNode<T1, T2>(_data);

		if (m_pRoot == nullptr)
		{
			m_pRoot = newNode;
		}
		else
		{
			BSTNode<T1, T2>* CurNode = m_pRoot;
			BSTNode<T1, T2>* PrevNode = nullptr;
			bool flag = false;


			while (CurNode != nullptr)
			{
				PrevNode = CurNode;

				if (CurNode->data->first > _data->first)
				{
					CurNode = CurNode->ptr[LCHILD];
					flag = true;
				}
				else
				{
					CurNode = CurNode->ptr[RCHILD];
					flag = false;
				}
			}

			if (flag)
			{
				PrevNode->ptr[LCHILD] = newNode;
				newNode->ptr[PARENT] = PrevNode;
			}
			else
			{
				PrevNode->ptr[RCHILD] = newNode;
				newNode->ptr[PARENT] = PrevNode;
			}
		}
	}

	void clear()
	{
		std::queue<BSTNode<T1, T2>*> q;
		q.push(m_pRoot);

		while (!q.empty())
		{
			BSTNode<T1, T2>* tmp = q.front();
			q.pop();

			if (tmp->ptr[LCHILD])
				q.push(tmp->ptr[LCHILD]);

			if (tmp->ptr[RCHILD])
				q.push(tmp->ptr[RCHILD]);

			delete tmp;
		}

		m_pRoot = nullptr;
	}


public:
	BST()
		: m_pRoot(nullptr)
	{
	}

	~BST()
	{
		clear();
	}
};