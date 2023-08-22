#pragma once

#include <iostream>
#include <assert.h>

using std::cout;

#define END_ITER -842150451;

template<typename T>
struct Node
{
	T			data;
	Node<T>* next;
	Node<T>* prev;

public:

	Node()
		: data(-1)
		, next(nullptr)
		, prev(nullptr)
	{}

	Node(T _data)
		: data(_data)
		, next(nullptr)
		, prev(nullptr)
	{}

	~Node()
	{
	}

};


template<typename T>
class myList
{
public:
	class iterator;

private:
	Node<T>* m_head;
	Node<T>* m_tail;

public:
	void	push_back(T _Val);
	void	push_front(T _Val);


	iterator	begin();
	iterator	end();
	iterator	insert(const iterator& _where, T _val);
	iterator	erase(const iterator& _where);

	void	traval();

public:
	myList();
	~myList();

};

template<typename T>
class myList<T>::iterator
{

private:
	myList* m_Owner;
	Node<T>* m_Node;

public:
	iterator& operator++()
	{
		if (m_Node->next == nullptr)
			assert(nullptr);

		m_Node = m_Node->next;

		return *this;
	}

	iterator& operator--()
	{
		if (m_Node->prev == nullptr)
			assert(nullptr);

		m_Node = m_Node->prev;

		return m_Node->prev;
	}

	bool operator==(const iterator& _Other)
	{
		if (_Other.m_Node == m_Node && m_Owner == _Other.m_Owner)
			return true;

		return false;
	}

	bool operator!=(const iterator& _Other)
	{
		if (_Other.m_Node == m_Node && m_Owner == _Other.m_Owner)
			return false;

		return true;
	}


public:
	iterator()
		: m_Owner(nullptr)
		, m_Node(nullptr)
	{
	}

	iterator(myList<T>* _Owner, Node<T>* _target)
		: m_Owner(_Owner)
		, m_Node(_target)
	{
	}

	~iterator()
	{
	}

	friend class myList;
};



template<typename T>
inline void myList<T>::push_back(T _Val)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = _Val;
	newNode->next = nullptr;
	newNode->prev = nullptr;

	if (m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;

		Node<T>* endNode = new Node<T>;
		endNode->data = END_ITER;
		endNode->next = nullptr;
		endNode->prev = newNode;

		m_tail->next = endNode;

	}
	else
	{
		Node<T>* endNode = m_tail->next;
		m_tail->next = newNode;
		newNode->prev = m_tail;
		m_tail = newNode;
		newNode->next = endNode;
	}

}

template<typename T>
inline void myList<T>::push_front(T _Val)
{
	Node<T>* newNode = new Node<T>;
	newNode->data = _Val;
	newNode->next = nullptr;

	if (m_head == nullptr)
	{
		m_head = newNode;
		m_tail = newNode;

		Node<T>* endNode = new Node<T>;
		endNode->data = END_ITER;
		endNode->next = nullptr;
		endNode->prev = newNode;

		m_tail->next = endNode;
	}
	else
	{
		newNode->next = m_head;
		m_head->prev = newNode;
		m_head = newNode;
	}
}

template<typename T>
inline typename myList<T>::iterator myList<T>::begin()
{
	return iterator(this, m_head);
}

template<typename T>
inline typename myList<T>::iterator myList<T>::end()
{
	return iterator(this, m_tail->next);
}

template<typename T>
inline typename myList<T>::iterator myList<T>::insert(const iterator& _where, T _val)
{
	if (this != _where.m_Owner || _where.m_Node == nullptr || _where.m_Node->data == -842150451)
		assert(nullptr);

	Node<T>* curNode = _where.m_Node;
	Node<T>* newNode = new Node<T>(_val);
	Node<T>* nextNode = curNode->next;

	curNode->next = newNode;
	newNode->next = nextNode;

	nextNode->prev = newNode;
	newNode->prev = curNode;


	return iterator(this, newNode);
}

template<typename T>
inline typename myList<T>::iterator myList<T>::erase(const iterator& _where)
{
	if (this != _where.m_Owner || _where.m_Node == nullptr || _where.m_Node->data == -842150451)
		assert(nullptr);

	Node<T>* curNode = _where.m_Node;
	Node<T>* prevNode = curNode->prev;
	Node<T>* nextNode = curNode->next;

	if (curNode == m_head)
	{
		nextNode->prev = nullptr;
		m_head = nextNode;
	}
	else
	{
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
	}


	delete curNode;

	return iterator(this, nextNode);
}


template<typename T>
inline void myList<T>::traval()
{
	Node<T>* head = m_head;

	while (head->data != -842150451)
	{
		cout << head->data << " - ";

		head = head->next;
	}

	cout << std::endl;
}



template<typename T>
inline myList<T>::myList()
	: m_head(nullptr)
	, m_tail(nullptr)
{
}

template<typename T>
inline myList<T>::~myList()
{
	Node<T>* CurNode = m_head;

	while (CurNode != nullptr)
	{
		Node<T>* tmp = CurNode->next;
		delete CurNode;
		CurNode = tmp;
	}
}
