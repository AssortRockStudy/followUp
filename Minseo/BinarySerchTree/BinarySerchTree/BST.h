﻿#pragma once
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

	Pair<t1, t2> Create_Pair(const t1& _first, const t2& _second)
	{
		Pair<t1, t2> data; 
		data.first = _first;
		data.second = _second;

		return data;
	}

	Pair()
	{}
	~Pair()
	{

	}

};

template <typename t1, typename t2>
struct BSTNode
{
	Pair<t1, t2>		data;
	BSTNode<t1, t2>* ptr[MAX];
public:
	BSTNode()
		:data(0)
		, ptr{nullptr, nullptr, nullptr}
	{}
	BSTNode(Pair<t1, t2> pair = nullptr, BSTNode<t1, t2>* parent = nullptr, BSTNode<t1, t2>* lchild = nullptr, BSTNode<t1, t2>* rchild = nullptr)
		: data(pair)
		, ptr{ parent,lchild,rchild }
	{	
		ptr[PARENT] = parent;
		ptr[LCHILD] = lchild;
		ptr[RCHILD] = rchild;
	}
	~BSTNode(){}	
	
	// 본인이 왼 쪽 자식이 있는지 없는지, 오른 쪽 자식이 있는지 없는지 bool 값을 반환해주는 함수
	bool HasLCHILD() { return ptr[LCHILD]; } // 왼 쪽 자식이 있나요
	bool HasRCHILD() { return ptr[RCHILD]; } // 오른 쪽 자식이 있나요
	bool IsROOT() { return !ptr[PARENT]; } // 부모가 있나요

	bool isLCHILD() { return ptr[PARENT]->ptr[LCHILD] == this; } //부모가 있다는 가정 하에 나는 왼 쪽 자식인가요
	bool isRCHILD() { return ptr[PARENT]->ptr[RCHILD] == this; }

	bool isFULL() { return ptr[LCHILD] && ptr[RCHILD]; } // 자식이 둘 다 있는 경우
	bool isLEAF() { return !ptr[LCHILD] && !ptr[RCHILD]; } // 자식이 둘 다 없는 경우

};

template <typename t1, typename t2>
class BST
{
private:
	BSTNode<t1, t2>* m_RootNode;
	int						m_Count;
	BSTNode<t1, t2>* preordersuccesseor(BSTNode<t1, t2>* _Node);
public:
	void insert(Pair<t1, t2> pair);
	void clear();
	class iterator;
	iterator find(const t1& _first);
	iterator erase(iterator& _iter);
	BST();
	~BST() { clear(); }

private:
	void nodeDelete(BSTNode<t1, t2>* target);

public:
	class iterator
	{
	private:
		BST<t1, t2>* m_pOwner;
		BSTNode<t1, t2>* m_Target;
		friend class BST;


	public: // 연산자 오버로딩
		iterator& operator ++()
		{
			assert(m_Target); // end iterator에 ++했을 경우

			// 중위 순회 기준 다음으로 가야한다.
			// => 중위 후속자를 찾아서 가리킨다.
			m_Target = m_pOwner->preordersuccesseor(m_Target);
			return *this;
		}
		iterator operator ++(int)
		{
			iterator iter = this;
			++(*this);
			return iter;
		}
		iterator& operator --()
		{
			// 중위 순회 기준 이전으로 가야한다.
			// 중위 선행자를 찾아서 가리킨다.
			// 왼 쪽 자식이 있을 경우 그 노드가 현재 노드의 중위선행자이다.
			BSTNode<t1, t2>* suc = nullptr;

			// 만약 end iterator라면 마지막 데이터를 반환해준다.
			if (m_Target == nullptr)
			{
				m_Target = m_RootNode;
				// 가장 오른 쪽 자식으로 이동할 때 까지 반복
				while (m_Target[RCHILD])
					m_Target = m_Target[RCHILD];
			}
			else if (m_Target->HasLCHILD())
			{
				m_Target = m_Target->ptr[LCHILD];
			}
			else
			{
				// 왼 쪽 자식이 없을 경우 부모 노드가 나를 오른 쪽 자식으로 가리키고 있다면 그 부모가 현재 노드의 중위선행자이다.
				// 만약 끝까지 없을 경우 첫 데이터에서 -- 하려고 하였기에 assert 처리해주자.
				while (true)
				{
					suc = m_Target->ptr[PARENT];
					assert(suc != nullptr);
					if (m_Target->isRCHILD())
					{
						m_Target = suc;
						break;
					}
					else
					{
						m_Target = suc;
					}
				}
			}

			return *this;
		}
		iterator operator --(int)
		{
			iterator iter = this;
			--(*this);
			return iter;
		}
		bool operator ==(const iterator& _other)
		{
			if (this->m_pOwner == _other.m_pOwner && this->m_Target == _other.m_Target)
				return true;
			return false;

		}
		bool operator !=(const iterator& _other)
		{
			return !(*this == _other);
		}
		Pair<t1, t2>* operator ->()
		{
			return &m_Target->data;
		}		
		Pair<t1, t2>& operator *()
		{
			return *m_Target->data;
		}
	public:
		iterator()
		{

		}
		iterator(BST<t1, t2>* ow, BSTNode<t1, t2>* ta)
			:m_pOwner(ow)
			,m_Target(ta)
		{

		}
		~iterator()
		{

		}
	};

public:
	iterator begin() // 보유하고 있는 데이터 중 시작을 가리켜야 함
	{
		// m_Root가 nullptr이라면(데이터가 1개도 입력되지 않은 상황) end iterator를 돌려줌
		if (nullptr == m_RootNode)
			return end();

		///////////////////////////
		BSTNode<t1, t2>* pNode = m_RootNode;

		while (nullptr != pNode->ptr[LCHILD])
		{
			pNode = pNode->ptr[LCHILD]; // 가장 왼 쪽 자식(중위 순회 기준 가장 첫 데이터)로 점점 이동
		}
		return iterator(this, pNode);

	}
	iterator end()// 가장 만만한건 nullptr래요.
	{
		return iterator(this, nullptr);
	}

};

template<typename t1, typename t2>
BSTNode<t1, t2>* BST<t1, t2>::preordersuccesseor(BSTNode<t1, t2>* _Node)
{
	BSTNode<t1, t2>* pSuccessor = nullptr;

	// 만약 오른 쪽 자식이 있을 경우 부모를 확인 할 필요 없다. 
	// 내 오른 쪽 자식에서 맨 왼 쪽 자식이 있을 때 까지 가면 중위 후속자이다.
	if (_Node->HasRCHILD()) // 오른 쪽 자식이 있네?
	{
		pSuccessor = _Node->ptr[RCHILD];
		while (nullptr != pSuccessor->ptr[LCHILD])
		{
			pSuccessor = pSuccessor->ptr[LCHILD];
		}
	}
	else
	{
		pSuccessor = _Node;
		while (true)
		{
			if (pSuccessor->IsROOT()) // 만약 끝내 왼 쪽 자식이었던 경우가 없었고 결국 루트 노드에 도착했을 경우
			{
				pSuccessor = nullptr; // m_Target은 마지막 데이터였으니까 end iterator가 되어라
				break; // 탈출
			}
			else if (pSuccessor->isLCHILD()) // 만약 계속 부모로 이동 중에 현재 왼 쪽 자식일 경우
			{
				pSuccessor = pSuccessor->ptr[PARENT]; // 부모가 내 중위 후속자 
				break;// 탈출
			}

			// 나의 부모로 다시 테스트하기 위해서 부모 포인터를 가리키게 함
			pSuccessor = pSuccessor->ptr[PARENT]; // 계속 부모로 이동
		}
		// 부모의 왼 쪽 자식인 경우, 그 부모가 중위 후속자이다.
		// 부모의 오른 쪽 자식인 경우, 부모의 왼 쪽 자식이 될 때 까지 위로 올라간다.
	}


	return pSuccessor;
}

template<typename t1, typename t2>
inline void BST<t1, t2>::insert(Pair<t1, t2> pair)
{
	BSTNode<t1, t2>* newNode = new BSTNode<t1, t2>(pair);
	// 만약 첫 데이터일 경우
	if (0 == m_Count)
	{
		m_RootNode = newNode;
		++m_Count;
		return;
	}
	// 첫 데이터가 아닐 경우
	BSTNode<t1, t2>* buf = m_RootNode;
	while (true)
	{
		if (buf->data.first < newNode->data.first) // 버퍼보다 클 경우
		{
			if (buf->ptr[RCHILD] != nullptr)
				buf = buf->ptr[RCHILD];
			else // 자신 자리 찾음
			{
				newNode->ptr[PARENT] = buf->ptr[RCHILD];
				buf->ptr[RCHILD] = newNode;
				break;
			}
		}
		else if (buf->data.first > newNode->data.first) // 버퍼보다 작을 경우
		{
			if (buf->ptr[LCHILD] != nullptr)
				buf = buf->ptr[LCHILD];
			else // 자신 자리 찾음
			{
				newNode->ptr[PARENT] = buf->ptr[LCHILD];
				buf->ptr[LCHILD] = newNode;
				break;
			}
		}
		else // 키 값 데이터가 같은 경우... HashMap의 경우에는 데이터를 덮어씌운다고 한다. 해볼까?
		{
			buf->data.second = newNode->data.second;
			delete newNode;
			return;
		}
	}
	++m_Count;
}

template<typename t1, typename t2>
void BST<t1, t2>::clear()
{
	// 반복문 버전

	// 재귀 버전
	nodeDelete(m_RootNode);
	m_Count = 0;
}

template<typename t1, typename t2>
typename BST<t1, t2>::iterator BST<t1, t2>::find(const t1& _first)
{
	BSTNode<t1, t2>* _Node(this, m_RootNode);
	while (_Node)
	{
		if (_Node->data.first > _first) // 왼 쪽 노드로 이동
		{
			_Node = _Node->ptr[LCHILD];
		}
		else if (_Node->data.first < _first) // 오른 쪽 노드로 이동
		{
			_Node = _Node->ptr[RCHILD];
		}
		else // 데이터를 찾음
		{
			break;
		}
	}
	return iterator(this, _Node);
}

template<typename t1, typename t2>
typename BST<t1, t2>::iterator BST<t1, t2>::erase(iterator& _iter)
{
	BSTNode<t1, t2>* node = _iter.m_Target;
	if (node->isLEAF())
	{
		if (node->IsROOT())
		{
			delete node;
			m_RootNode = nullptr;
			--m_Count;
			return end();
		}
		else
		{
			BSTNode<t1, t2>* pSuccessor = preordersuccesseor(node);
			if(node->isLCHILD())
				node->ptr[PARENT]->ptr[LCHILD] = nullptr;
			if (node->isRCHILD())
				node->ptr[PARENT]->ptr[RCHILD] = nullptr;
		}

	}
	else if (node->isFULL()) // 노드가 2개
	{
		BSTNode<t1, t2>* pDelete = preordersuccesseor(node); // 여기선 중위 후속자를 지워야했어
		node->data = pDelete->data;
		erase(iterator(this, pDelete)); // 안에서 데이터 지워지니까 따로 --를 하지 않고 바로 반환해줌.
		return iterator(this, node);
	}
	else // 노드가 하나
	{
		BSTNode<t1, t2>* pSuccessor = preordersuccesseor(node);
		BSTNode<t1, t2>* pChild = nullptr;
		BSTNode<t1, t2>* pParent = node->ptr[PARENT];
		if (node->HasLCHILD())
			pChild = node->ptr[LCHILD];
		else
			pChild = node->ptr[RCHILD];
		if (node->IsROOT)
		{
			pChild->ptr[PARENT] = nullptr;
			m_RootNode = pChild;
		}
		else
		{
			if (node->isLCHILD())
				pParent->ptr[LCHILD] = pChild;
			else
				pParent->ptr[RCHILD] = pChild;
			pChild->ptr[PARENT] = pParent;
		}
	}


	delete node;
	--m_Count;
	return iterator(this, pSuccessor);

}

template<typename t1, typename t2>
inline void BST<t1, t2>::nodeDelete(BSTNode<t1, t2>* target)
{
	if (target->ptr[LCHILD] != nullptr)
		nodeDelete(target->ptr[LCHILD]);

	if (target->ptr[RCHILD] != nullptr)
		nodeDelete(target->ptr[RCHILD]);
	
	delete target;

	return;
}

template<typename t1, typename t2>
inline BST<t1, t2>::BST()
{
}
