#pragma once

#include <assert.h>

/*

	1. node struct, list class, iterator 구현 (template)
	2. push_back, push_front, begin, end, erase 구현

*/


template<typename T>
struct tNode
{
	T			data;
	tNode<T>*	next;
	tNode<T>*	prev;

public:

	tNode()
		: data(-1)
		, next(nullptr)
		, prev(nullptr)
	{}

	tNode(const T& _data, tNode<T>* _next = nullptr, tNode<T>* _prev = nullptr)
		: data(_data)
		, next(_next)
		, prev(_prev)
	{}

	~tNode()
	{
	}

};


template<typename T>
class CList
{
public:
	class iterator;

private:
	tNode<T>*	m_pHead;
	tNode<T>*	m_pTail;

public:
	void push_back(const T& _data)
	{
		tNode<T>* newNode = new tNode<T>(_data);

		if (nullptr == m_pHead)
		{
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else
		{
			m_pTail->next = newNode;
			newNode->prev = m_pTail;
			m_pTail = newNode;
		}
	}
	void push_front(const T& _data)
	{
		tNode<T>* newNode = new tNode<T>(_data);

		if (nullptr == m_pHead)
		{
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else
		{
			m_pHead->prev = newNode;
			newNode->next = m_pHead;
			m_pHead = newNode;
		}
	}

	iterator erase(const iterator& _where)
	{
		tNode<T>* CurNode = _where.m_pTarget;

		if (CurNode != m_pTail)
		{
			CurNode->next->prev = CurNode->prev;
		}
		else
		{
			m_pTail = CurNode->prev;
		}


		if (CurNode != m_pHead)
		{
			CurNode->prev->next = CurNode->next;
		}
		else
		{
			m_pHead = CurNode->next;
		}

		iterator retNode(this, CurNode->next);

		delete CurNode;

		return retNode;
	}

	iterator begin()
	{
		return iterator(this, m_pHead);
	}
	iterator end()
	{
		return iterator(this, nullptr);
	}

public:
	CList()
		: m_pHead(nullptr)
		, m_pTail(nullptr)
	{
	}
	~CList()
	{
		tNode<T>* CurNode = m_pHead;

		while (CurNode != nullptr)
		{
			tNode<T>* next = CurNode->next;
			delete CurNode;
			CurNode = next;
		}

	}
};


template<typename T>
class CList<T>::iterator
{
private:
	CList<T>* m_pOwner;
	tNode<T>* m_pTarget;

public:

	iterator& operator++()
	{
		assert(m_pTarget);

		m_pTarget = m_pTarget->next;

		return *this;
	}

	iterator& operator--()
	{
		assert(m_pTarget);

		m_pTarget = m_pTarget->prev;
		
		return *this;
	}

	T& operator*()
	{
		assert(m_pTarget);

		return m_pTarget->data;
	}

	bool operator==(const iterator& _Ohter)
	{
		if (m_pOwner == _Ohter.m_pOwner && m_pTarget == _Ohter.m_pTarget)
			return true;
		else
			return false;
	}

	bool operator!=(const iterator& _Ohter)
	{
		return (*this == _Ohter);
	}

public:
	iterator()
		: m_pOwner(nullptr)
		, m_pTarget(nullptr)
	{
	}

	iterator(CList* _Owner, tNode<T>* _pTarget)
		: m_pOwner(_Owner)
		, m_pTarget(_pTarget)
	{
	}

	~iterator()
	{
	}

	friend class CList;
};

