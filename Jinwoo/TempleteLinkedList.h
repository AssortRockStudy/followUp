#pragma once

// pseudo code
// 템플릿이기에 헤더에 구현
// 양방향 리스트 템플릿화
// 1. 노드 구조체 생성
// 노드에는 노드에 저장되어 있는 데이터를 저장할 멤버변수와
// 양방향이므로 자신의 다음, 이전 노드를 가리킬 포인터가 필요
// 노드를 생성할 때 한번에 초기화 할 수 있도록
// 기본생성자 뿐만아니라 복사 생성자도 필요함
// 2. 리스트 클래스 생성
// 리스트에는 리스트 크기를 저장할 멤버변수와
// 첫번째 노드를 가리키는 m_pHead, 마지막 노드를 가리키는 m_pTail 포인터가 필요
// 노드와 똑같이 기본 생성자, 소멸자
// 리스트에 복사생성자는 굳이?
// push_back 함수가 필요하고, 가장 처음 노드를 가리키게 하는 함수 begin과
// 마지막 노드 그 다음을 가리키게 하는 함수 end 구현
// 3. iterator 클래스 생성
// 순회가 필요하므로 반복자를 생성해야함
// 포함 클래스로 생성하고 어떤 리스트를 가리키는지 저장할 멤버와
// 그 리스트 중 어느 노드를 가리키는지 저장할 멤버가 필요
// 순회를 위해 ==, !=, ++, --연산자 오퍼레이터 오버로딩 해줘야함
// 생성자, 소멸자, 복사 생성자 필요

#include <assert.h>

template <typename T>
struct TNode
{
	T data;
	TNode* pNext;
	TNode* pPrev;

	TNode() : data(0), pNext(nullptr), pPrev(nullptr)
	{

	}

	TNode(T _data, TNode* _pNext = nullptr, TNode* _pPrev = nullptr)
		: data(_data), pNext(_pNext), pPrev(_pPrev)
	{

	}

	~TNode() {}
};

template <typename T>
class TList
{
private:
	int m_Count;
	TNode<T>* m_pHead;
	TNode<T>* m_pTail;

public:
	void push_back(const T& _data);

	class iterator;
	iterator begin()
	{
		return iterator(this, m_pHead);
	}

	iterator end()
	{
		return iterator(this, nullptr);
	}

public:
	TList() : m_Count(0), m_pHead(nullptr), m_pTail(nullptr)
	{
	
	}

	~TList()
	{
		TNode<T>* NewNode = m_pHead;

		for (int i = 0; i < m_Count; ++i)
		{
			TNode<T>* pNext = NewNode->pNext;
			delete NewNode;
			NewNode = pNext;
		}
	}

	class iterator
	{
	private:
		TList<T>* m_pOwner;
		TNode<T>* m_Target;

	public:
		bool operator == (const iterator& _other)
		{
			return (m_pOwner == _other.m_pOwner) && (m_Target == _other.m_Target);
		}

		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

		iterator& operator ++()
		{
			assert(m_Target);

			m_Target = m_Target->pNext;
			
			return *this;
		}

		iterator& operator ++(int)
		{
			iterator Temp(*this);

			++(*this);

			return Temp;
		}

		iterator& operator --()
		{
			assert(m_Target);

			m_Target = m_Target->pPrev;

			return *this;
		}

		iterator& operator --(int)
		{
			iterator Temp(*this);

			--(*this);

			return Temp;
		}

		// *는 원본에 접근하는 것이므로 데이터를 리턴해야한다
		T& operator *()
		{
			assert(m_Target);

			return m_Target->data;
		}



	public:
		iterator() : m_pOwner(nullptr), m_Target(nullptr)
		{

		}

		iterator(TList<T>* _pOwner, TNode<T>* _Target) : m_pOwner(_pOwner), m_Target(_Target)
		{

		}

		~iterator()
		{

		}

		friend class TList<T>;
	};

};

template<typename T>
void TList<T>::push_back(const T& _data)
{
	TNode<T>* NewNode = new TNode<T>(_data);

	if (nullptr == m_pHead)
	{
		m_pHead = m_pTail =  NewNode;
	}
	else
	{
		m_pTail->pNext = NewNode;
		NewNode->pPrev = m_pTail;
		m_pTail = NewNode;
	}

	++m_Count; 
}
