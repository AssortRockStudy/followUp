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
};

template <typename t1, typename t2>
class BST
{
private:
	BSTNode<t1, t2>* m_RootNode;
	int						m_Count;

public:
	void insert(Pair<t1, t2> pair);
	void clear();
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



	public: // 연산자 오버로딩
		iterator& operator ++()
		{
			assert(m_Target); // end iterator에 ++했을 경우

			// 중위 순회 기준 다음으로 가야한다.
			// => 중위 후속자를 찾아서 가리킨다.

			BSTNode<t1, t2>* pSuccessor = nullptr;

			// 만약 오른 쪽 자식이 있을 경우 부모를 확인 할 필요 없다. 
			// 내 오른 쪽 자식에서 맨 왼 쪽 자식이 있을 때 까지 가면 중위 후속자이다.
			if (m_Target->HasRCHILD()) // 오른 쪽 자식이 있네?
			{
				pSuccessor = m_Target->ptr[RCHILD];
				while (nullptr != pSuccessor->ptr[LCHILD])
				{
					pSuccessor = pSuccessor->ptr[LCHILD];
				}

				m_Target = pSuccessor;

				return *this;
			}
			else
			{
				pSuccessor = m_Target;
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


			m_Target = pSuccessor;

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
			return m_Target->data;
		}		
		Pair<t1, t2>& operator *()
		{
			return *(m_Target->data);
		}
	public:
		iterator()
		{

		}
		~iterator()
		{

		}
	};

};

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
				buf->ptr[RCHILD] = newNode;
				newNode->ptr[PARENT] = buf->ptr[RCHILD];
				break;
			}
		}
		else if (buf->data.first > newNode->data.first) // 버퍼보다 작을 경우
		{
			if (buf->ptr[LCHILD] != nullptr)
				buf = buf->ptr[LCHILD];
			else // 자신 자리 찾음
			{
				buf->ptr[LCHILD] = newNode;
				newNode->ptr[PARENT] = buf->ptr[LCHILD];
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
