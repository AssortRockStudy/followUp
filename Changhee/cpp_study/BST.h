#pragma once

#include <queue>
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

//	1. Pair 구조체 만들기 -> make_Pair 함수 구현
//	2. BSTnode 만들기
//	3. 포인터 종류 enum 만들기
//	4. BST class 구현 -> insert, clear 함수
//	5. DFS, BFS 구현
//	6. Depth, find, erase 구현 


template<typename T1, typename T2>
struct Pair {


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
	Pair<T1, T2>* data;
	BSTNode<T1, T2>* ptr[PTR_TYPE::END];

	BSTNode()
		: data(nullptr)
		, ptr{}
	{
	}

	BSTNode(Pair<T1, T2>* _data, BSTNode<T1, T2>* _parent = nullptr, BSTNode<T1, T2>* _lchild = nullptr, BSTNode<T1, T2>* rchild = nullptr)
		: data(_data)
		, ptr{ _parent, _lchild, rchild }
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
public:
	class iterator
	{
	private:
		BST<T1, T2>* m_pOwner;
		BSTNode<T1, T2>* m_pTarget;

	public:
		iterator& operator++()
		{
			assert(m_pTarget);

			BSTNode<T1, T2>* retNode = nullptr;


			// 오른쪽 자식이 있다면 오른쪽 자식중 제일 작은 노드 (RCHILD 1번 -> LCHILD가 nullptr 일때까지 이동)
			// 오른쪽 자식이 없다면 부모중 자기보다 큰 노드중 가장 작은 노드( 자기보다 큰 부모노드가 나올때까지 위로), nullptr이 나올경우 마지막 노드임

			if (m_pTarget->ptr[RCHILD] == nullptr)
			{
				retNode = m_pTarget->ptr[PARENT];

				while (nullptr != retNode && m_pTarget->data->first > retNode->data->first)
				{
					retNode = retNode->ptr[PARENT];
				}
			}
			else
			{
				retNode = m_pTarget->ptr[RCHILD];

				while (retNode->ptr[LCHILD] != nullptr)
				{
					retNode = retNode->ptr[LCHILD];
				}
			}

			m_pTarget = retNode;

			return *this;
		}

		iterator& operator--()
		{
			BSTNode<T1, T2>* retNode = nullptr;

			// nullptr가 end노드이므로 m_pTarget이 nullptr인 경우 예외처리
			if (m_pTarget == nullptr)
			{
				retNode = m_pOwner->m_pRoot;

				while (retNode->ptr[RCHILD] != nullptr)
				{
					retNode = retNode->ptr[RCHILD];
				}

				m_pTarget = retNode;

				return *this;
			}


			// 맨 앞의 데이터에서 -- 를 하는 경우 오류
			if ((*this) == m_pOwner->begin())
			{
				assert(nullptr);
			}

			// 왼쪽 자식이 있다면 왼쪽 자식중 제일 큰 노드 (LCHILD 1번 -> RCHILD가 nullptr 일때까지 이동)
			// 왼쪽 자식이 없다면 부모중 자기보다 작은 노드중 가장 큰은 노드(자기보다 큰 부모노드가 나올때까지 위로), nullptr이 나올경우 마지막 노드임

			if (m_pTarget->ptr[LCHILD] == nullptr)
			{
				retNode = m_pTarget->ptr[PARENT];

				while (nullptr != retNode && m_pTarget->data->first < retNode->data->first)
				{
					retNode = retNode->ptr[PARENT];
				}
			}
			else
			{
				retNode = m_pTarget->ptr[LCHILD];

				while (retNode->ptr[RCHILD] != nullptr)
				{
					retNode = retNode->ptr[RCHILD];
				}
			}

			m_pTarget = retNode;

			return *this;
		}

		T1& operator*()
		{
			return m_pTarget->data->first;
		}

		bool operator==(const iterator& _Other)
		{
			if (m_pOwner == _Other.m_pOwner && m_pTarget == _Other.m_pTarget)
				return true;

			return false;
		}

		bool operator!=(const iterator& _Other)
		{
			return !((*this) == _Other);
		}

	public:
		iterator()
			: m_pOwner(nullptr)
			, m_pTarget(nullptr)
		{
		}

		iterator(BST<T1, T2>* _Owner, BSTNode<T1, T2>* _Target)
			: m_pOwner(_Owner)
			, m_pTarget(_Target)
		{
		}


		~iterator()
		{
		}

		friend class BST;
	};


public:
	BSTNode<T1, T2>* m_pRoot;

public:
	iterator begin()
	{
		if (m_pRoot == nullptr)
		{
			return iterator(this, nullptr);
		}

		BSTNode<T1, T2>* CurNode = m_pRoot;

		while (CurNode->ptr[LCHILD] != nullptr)
		{
			CurNode = CurNode->ptr[LCHILD];
		}

		return iterator(this, CurNode);

	}

	iterator end()
	{
		return iterator(this, nullptr);
	}


	void insert(Pair<T1, T2>* _data)
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

	void preOrder(BSTNode<T1, T2>* _Node)
	{
		assert(_Node);

		cout << _Node->data->first << endl;

		if (_Node->ptr[LCHILD] != nullptr)
			preOrder(_Node->ptr[LCHILD]);

		if (_Node->ptr[RCHILD] != nullptr)
			preOrder(_Node->ptr[RCHILD]);

	}

	void inOrder(BSTNode<T1, T2>* _Node)
	{
		assert(_Node);



		if (_Node->ptr[LCHILD] != nullptr)
			inOrder(_Node->ptr[LCHILD]);

		cout << _Node->data->first << endl;

		if (_Node->ptr[RCHILD] != nullptr)
			inOrder(_Node->ptr[RCHILD]);
	}

	void postOrder(BSTNode<T1, T2>* _Node)
	{
		assert(_Node);

		if (_Node->ptr[LCHILD] != nullptr)
			postOrder(_Node->ptr[LCHILD]);

		if (_Node->ptr[RCHILD] != nullptr)
			postOrder(_Node->ptr[RCHILD]);

		cout << _Node->data->first << endl;
	}

	void DFS(BSTNode<T1, T2>* _Node)
	{
		assert(_Node);

		cout << _Node->data->first << endl;

		if (_Node->ptr[LCHILD] != nullptr)
			preOrder(_Node->ptr[LCHILD]);

		if (_Node->ptr[RCHILD] != nullptr)
			preOrder(_Node->ptr[RCHILD]);
	}

	void BFS(BSTNode<T1, T2>* _Node)
	{
		std::queue<BSTNode<T1, T2>*> q;
		q.push(m_pRoot);

		while (!q.empty())
		{
			BSTNode<T1, T2>* tmp = q.front();

			cout << tmp->data->first << endl;
			q.pop();

			if (tmp->ptr[LCHILD])
				q.push(tmp->ptr[LCHILD]);

			if (tmp->ptr[RCHILD])
				q.push(tmp->ptr[RCHILD]);

			delete tmp;
		}

		m_pRoot = nullptr;
	}

	int get_depth()
	{
		int depth = -1;

		std::queue < std::pair<BSTNode<T1, T2>*, int> > q;

		if (m_pRoot != nullptr)
			q.push(std::make_pair(m_pRoot, 0));

		while (!q.empty())
		{
			BSTNode<T1, T2>* CurNode = q.front().first;
			int CurDepth = q.front().second;
			q.pop();

			if (CurDepth > depth)
			{
				depth = CurDepth;
			}

			if (CurNode->ptr[LCHILD])
			{
				q.push(std::make_pair(CurNode->ptr[LCHILD], CurDepth + 1));
			}

			if (CurNode->ptr[RCHILD])
			{
				q.push(std::make_pair(CurNode->ptr[RCHILD], CurDepth + 1));
			}

		}

		return depth;
	}

	iterator find(const T1& _key)
	{
		if (m_pRoot == nullptr)
			return nullptr;

		BSTNode<T1, T2>* CurNode = m_pRoot;

		while (CurNode != nullptr && CurNode->data->first != _key)
		{
			if (CurNode->data->first < _key)
				CurNode = CurNode->ptr[RCHILD];
			else
				CurNode = CurNode->ptr[LCHILD];
		}

		return iterator(this, CurNode);
	}

	iterator erase(const T1& _key)
	{
		BSTNode<T1, T2>* Target = find(_key).m_pTarget;

		// 자식이 없는 경우
		if (Target->ptr[RCHILD] == nullptr && Target->ptr[LCHILD] == nullptr)
		{
			BSTNode<T1, T2>* parent = Target->ptr[PARENT];

			if (parent->ptr[RCHILD] == Target)
				parent->ptr[RCHILD] = nullptr;

			if (parent->ptr[LCHILD] == Target)
				parent->ptr[LCHILD] = nullptr;

			delete Target;
		}
		else if (Target->ptr[RCHILD] != nullptr && Target->ptr[LCHILD] != nullptr)
		{
			// 자식이 두개 있는 경우
			
			//iterator iter = iterator(this, Target);
			//++iter;

			//BSTNode<T1, T2>* swapNode = iter.m_pTarget;




			


		}
		else
		{
			// 자식이 1개 있는 경우

			// 오른쪽 자식만 있는 경우
			if (Target->ptr[RCHILD] != nullptr)
			{
				BSTNode<T1, T2>* parent = Target->ptr[PARENT];

				// 해당 노드가 부모의 오른쪽 자식이었던 경우
				if (parent->ptr[RCHILD] == Target)
				{
					parent->ptr[RCHILD] = Target->ptr[RCHILD];
					Target->ptr[RCHILD]->ptr[PARENT] = parent;
				}

				// 해당 노드가 부모의 왼쪽 자식이었던 경우
				if (parent->ptr[LCHILD] == Target)
				{
					parent->ptr[LCHILD] = Target->ptr[LCHILD];
					Target->ptr[LCHILD]->ptr[PARENT] = parent;
				}

				delete Target;
			}



			// 왼쪽 자식만 있는 경우
			if (Target->ptr[RCHILD] != nullptr)
			{
				BSTNode<T1, T2>* parent = Target->ptr[PARENT];

				// 해당 노드가 부모의 오른쪽 자식이었던 경우
				if (parent->ptr[RCHILD] == Target)
				{
					parent->ptr[RCHILD] = Target->ptr[LCHILD];
					Target->ptr[LCHILD]->ptr[PARENT] = parent;
				}

				// 해당 노드가 부모의 왼쪽 자식이었던 경우
				if (parent->ptr[LCHILD] == Target)
				{
					parent->ptr[LCHILD] = Target->ptr[LCHILD];
					Target->ptr[LCHILD]->ptr[PARENT] = parent;
				}

				delete Target;
			}

		}

	}

	void clear()
	{
		if (m_pRoot == nullptr)
			return;

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