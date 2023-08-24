#pragma once
#include <assert.h>

template <typename T>
class TList;

template <typename T>
class TNode
{
public://멤버 변수
	// 데이터, 이전 노드, 다음 노드
	T			m_Data;
	TNode<T>*	m_pPrev;
	TNode<T>*	m_pNext;

public:// 생성자, 소멸자, 오버로딩
	TNode()
		: m_Data(0)
		, m_pPrev(nullptr)
		, m_pNext(nullptr)
	{

	}
	
	TNode(const T& data = 0,TNode<T>* pPrev = nullptr, TNode* pNext = nullptr)
		: m_Data(data)
		, m_pPrev(pPrev)
		, m_pNext(pNext)
	{

	}
	~TNode()
	{}


};


template <typename T>
class TList
{
private://멤버 변수
	//들어가야하는 멤버는 일단...
	// 첫 노드, 끝 노드, 데이터 개수
	TNode<T>*	m_pHead;
	TNode<T>*	m_pTail;
	int			m_Count;
public:// 멤버 함수
	void push_back(const T& data);// 인자를 const T&로 해주는 이유는 원본을 수정할 여지가 없게 하면서, 싼 값에 받아오기
	void push_front(const T& data);// 인자를 const T&로 해주는 이유는 원본을 수정할 여지가 없게 하면서, 싼 값에 받아오기
	int size() { return m_Count; }
	class iterator; // 전방 선언
	iterator begin()
	{
		return iterator(this, m_pHead);// 함수의 반환 값은 자동으로 R-value 처리되어 이동대입연산자가 호출
	}
	iterator end()
	{
		return iterator(this, nullptr); // end의 경우를 nullptr로 보는걸로 하자
	}
	iterator erase(iterator& iter);

public://iterator
	class iterator
	{
		friend class TList<T>;
	private://멤버 변수
		//멤버는 이 iterator를 소유하는 TList 객체를 담는 멤버 하나, 그리고 가리키는 데이터(노드)하나가 필요했었음
		TList<T>* m_pOwner;
		TNode<T>* m_pTarget;

	public://operator ++ -- == != *
		iterator& operator++()
		{
			// 예외 처리) 이터레이터가 잘못 된 데이터를 가리키고 있을 경우, 잘못된 list객체를 가리키고 있을 경우
			assert(!(m_pOwner == nullptr || m_pTarget == nullptr));
			m_pTarget = m_pTarget->m_pNext;
			return *this;
		}
		iterator operator++(int)
		{
			// 예외 처리) 이터레이터가 잘못 된 데이터를 가리키고 있을 경우, 잘못된 list객체를 가리키고 있을 경우
			iterator Buffer(m_pOwner, m_pTarget);
			assert(!(m_pOwner == nullptr || m_pTarget == nullptr));
			m_pTarget = m_pTarget->m_pNext;
			return Buffer;
		}
		iterator& operator--()
		{
			// 예외 처리) 이터레이터가 잘못 된 데이터를 가리키고 있을 경우, 잘못된 list객체를 가리키고 있을 경우
			assert(!(m_pOwner == nullptr || m_pTarget == m_pHead));
			if (m_pTarget == nullptr)
			{
				m_pTarget = m_pTail;
			}
			else
			{
				m_pTarget = m_pTarget->m_pPrev;
			}
			return *this;
		}
		iterator& operator--(int)
		{
			iterator Buffer(m_pOwner, m_pTarget);
			// 예외 처리) 이터레이터가 잘못 된 데이터를 가리키고 있을 경우, 잘못된 list객체를 가리키고 있을 경우
			assert(!(m_pOwner == nullptr || m_pTarget == m_pHead));
			if (m_pTarget == nullptr)
			{
				m_pTarget = m_pTail;
			}
			else
			{
				m_pTarget = m_pTarget->m_pPrev;
			}
			return Buffer;
		}
		bool operator ==(const iterator& _other)
		{
			if (_other.m_pOwner == m_pOwner && _other.m_pTarget == m_pTarget)
			{
				return true;
			}
			return false;
		}
		bool operator !=(const iterator& _other)
		{
			return !(this->operator==(_other));
		}
		T& operator *()
		{
			return m_pTarget->m_Data;
		}
	public://생성자, 소멸자, 오버로딩
		iterator()
			:m_pOwner(nullptr)
			,m_pTarget(nullptr)
		{

		}
		iterator(TList<T>* Owner = nullptr, TNode<T>* Target = nullptr)
			:m_pOwner(Owner)
			,m_pTarget(Target)
		{

		}
		~iterator()
		{

		}
	};

public:// 생성자, 소멸자, 오버로딩
	TList()
		:m_pHead(nullptr)
		, m_pTail(nullptr)
		, m_Count(0)
	{
	}
	~TList();

};


template<typename T>
void TList<T>::push_back(const T& data)
{
	TNode<T>* NewNode = new TNode<T>(data);

	// 예외 처리 - 첫 데이터일 경우
	if (m_Count == 0)
	{
		m_pHead = NewNode;
	}
	else // 첫 데이터가 아닐 경우
	{
		m_pTail->m_pNext = NewNode;
		NewNode->m_pPrev = m_pTail;
	}
	m_pTail = NewNode;
	

	++m_Count;
}


template<typename T>
void TList<T>::push_front(const T& data)
{
	TNode<T>* NewNode = new TNode<T>(data);

	// 예외 처리 - 첫 데이터일 경우
	if (m_Count == 0)
	{
		m_pTail = NewNode;
	}
	else // 첫 데이터가 아닐 경우
	{
		m_pHead->m_pPrev = NewNode;
		NewNode->m_pNext = m_pHead;
	}
	m_pHead = NewNode;

	++m_Count;
}

template<typename T>
typename TList<T>::iterator TList<T>::erase(iterator& iter)
{
	TNode<T>* Target = iter.m_pTarget;
	TNode<T>* nextNode = Target->m_pNext;
	// 예외 처리) 같은 List 객체의 데이터인가?
	assert(iter.m_pOwner == this && Target != nullptr);
	if (Target == m_pHead)
	{
		Target->m_pNext->m_pPrev = nullptr;
		m_pHead = m_pHead->m_pNext;
	}
	else if (Target->m_pNext != nullptr)
	{
		Target->m_pNext->m_pPrev = Target->m_pPrev;
	}
	if (Target == m_pTail)
	{
		Target->m_pPrev->m_pNext = nullptr;
		m_pTail = m_pTail->m_pPrev;
	}
	else if (Target->m_pPrev != nullptr)
	{
		Target->m_pPrev->m_pNext = Target->m_pNext;
	}
	delete iter.m_pTarget;
	
	--m_Count;

	return iterator(this, nextNode);

}


template<typename T>
inline TList<T>::~TList()
{
	TNode<T>* DNode = m_pHead;
	for (int i = 0; i < m_Count; ++i)
	{
		TNode<T>* BNode = DNode->m_pNext;
		delete DNode;
		DNode = BNode;
	}
}

