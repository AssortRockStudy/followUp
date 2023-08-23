#pragma once

#include <stdio.h>
#include <assert.h>

template<typename T>
struct tNode
{
	T		Data;
	tNode* pNext;
	tNode* pPrev;

	tNode()
		: Data(0)
		, pNext(nullptr)
		, pPrev(nullptr)
	{}

	tNode(const T& _Data, tNode* _Next = nullptr, tNode* _Prev = nullptr)
		: Data(_Data)
		, pNext(_Next)
		, pPrev(_Prev)
	{}
};

template<typename T>
class CList
{
private:
	tNode<T>* m_pHead;
	tNode<T>* m_pTail;
	int			m_Count;

public:
	int size() { return m_Count; }
	void push_back(const T& _data);
	void push_front(const T& _data);

	class iterator;
	iterator begin() { return iterator(this, m_pHead); }
	iterator end() { return iterator(this, nullptr); }

	iterator erase(const iterator& iter)
	{
		if (iter.m_Target != m_pTail)
		{
			iter.m_Target->pNext->pPrev = iter.m_Target->pPrev;
		}
		else
		{
			m_pTail = iter.m_Target->pPrev;
		}

		if (iter.m_Target != m_pHead)
		{
			iter.m_Target->pPrev->pNext = iter.m_Target->pNext;
		}
		else
		{
			m_pHead = iter.m_Target->pNext;
		}

		iterator nextiter(this, iter.m_Target->pNext);

		delete iter.m_Target;
		--m_Count;

		return nextiter;
	}

public:
	CList()
		: m_pHead(nullptr)
		, m_pTail(nullptr)
		, m_Count(0)
	{}

	~CList();

	class iterator
	{
	private:
		CList<T>* m_pOwner;
		tNode<T>* m_Target;

	public:
		bool operator == (const iterator& _other)
		{
			if (m_pOwner == _other.m_pOwner && m_Target == _other.m_Target)
				return true;
			else
				return false;
		}

		bool operator != (const iterator& _other) { return !(*this == _other); }

		iterator& operator ++ ()
		{
			if (nullptr == m_Target)
				assert(nullptr);
			else
				m_Target = m_Target->pNext;

			return *this;
		}

		iterator operator ++ (int)
		{
			iterator copyiter(*this);
			++(*this);

			return copyiter;
		}

		iterator& operator -- ()
		{
			if (nullptr == m_Target->pPrev)
				assert(nullptr);
			else
				m_Target = m_Target->pPrev;

			return *this;
		}

		iterator operator -- (int)
		{
			iterator copyiter(*this);
			--(*this);

			return copyiter;
		}

		T& operator * ()
		{
			if (nullptr == m_Target)
				assert(nullptr);

			return m_Target->Data;
		}

	public:
		iterator()
			: m_pOwner(nullptr)
			, m_Target(nullptr)
		{}

		iterator(CList* _List, tNode<T>* _pNode)
			: m_pOwner(_List)
			, m_Target(_pNode)
		{}

		~iterator() {}

		friend class CList;
	};
};

template<typename T>
CList<T>::~CList()
{
	tNode<T>* pNode = m_pHead;
	for (int i = 0; i < m_Count; ++i)
	{
		tNode<T>* pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
}

template<typename T>
void CList<T>::push_back(const T& _data)
{
	tNode<T>* pNewNode = new tNode<T>(_data);

	if (nullptr == m_pHead)
		m_pHead = m_pTail = pNewNode;

	else
	{
		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;

		m_pTail = pNewNode;
	}

	++m_Count;
}

template<typename T>
void CList<T>::push_front(const T& _data)
{

}