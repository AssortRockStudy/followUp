#pragma once

template <typename T>
class TNode
{
public:
	// ���� �ϴ� ���
	// ������, ���� ���, ���� ���
	T			m_Data;
	TNode<T>*	m_pPrev;
	TNode<T>*	m_pNext;

public:
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
private://��� ����
	//�����ϴ� ����� �ϴ�...
	// ù ���, �� ���, ������ ����
	TNode<T>*	m_pHead;
	TNode<T>*	m_pTail;
	int			m_Count;
public:// ��� �Լ�
	void push_back(const T& data);// ���ڸ� const T&�� ���ִ� ������ ������ ������ ������ ���� �ϸ鼭, �� ���� �޾ƿ���
	void push_front(const T& data);// ���ڸ� const T&�� ���ִ� ������ ������ ������ ������ ���� �ϸ鼭, �� ���� �޾ƿ���



public:// ������, �Ҹ���, �����ε�
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

	// ���� ó�� - ù �������� ���
	if (m_Count == 0)
	{
		m_pHead = NewNode;
	}
	else // ù �����Ͱ� �ƴ� ���
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

	// ���� ó�� - ù �������� ���
	if (m_Count == 0)
	{
		m_pTail = NewNode;
	}
	else // ù �����Ͱ� �ƴ� ���
	{
		m_pHead->m_pPrev = NewNode;
		NewNode->m_pNext = m_pHead;
	}
	m_pHead = NewNode;

	++m_Count;
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

