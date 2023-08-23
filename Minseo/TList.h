#pragma once
#include <assert.h>

template <typename T>
class TList;

template <typename T>
class TNode
{
public://��� ����
	// ������, ���� ���, ���� ���
	T			m_Data;
	TNode<T>*	m_pPrev;
	TNode<T>*	m_pNext;

public:// ������, �Ҹ���, �����ε�
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
	class iterator; // ���� ����
	iterator begin()
	{
		return iterator(this, m_pHead);// �Լ��� ��ȯ ���� �ڵ����� R-value ó���Ǿ� �̵����Կ����ڰ� ȣ��
	}
	iterator end()
	{
		return iterator(this, nullptr); // end�� ��츦 nullptr�� ���°ɷ� ����
	}
	iterator erase(iterator& iter);

public://iterator
	class iterator
	{
		friend class TList<T>;
	private://��� ����
		//����� �� iterator�� �����ϴ� TList ��ü�� ��� ��� �ϳ�, �׸��� ����Ű�� ������(���)�ϳ��� �ʿ��߾���
		TList<T>* m_pOwner;
		TNode<T>* m_pTarget;
	public://������, �Ҹ���, �����ε�
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
typename TList<T>::iterator TList<T>::erase(iterator& iter)
{
	TNode<T>* NodeBuf = iter.m_pTarget->m_pNext;
	// ���� ó��) ���� List ��ü�� �������ΰ�?
	assert(iter.m_pOwner == this && iter.m_pTarget != nullptr);
	if (iter.m_pTarget == m_pHead)
	{
		iter.m_pTarget->m_pNext->m_pPrev = nullptr;
		m_pHead = m_pHead->m_pNext;
	}
	else
	{
		iter.m_pTarget->m_pNext->m_pPrev = iter.m_pTarget->m_pPrev;
	}
	if (iter.m_pTarget == m_pTail)
	{
		iter.m_pTarget->m_pPrev->m_pNext = nullptr;
		m_pTail = m_pTail->m_pPrev;
	}
	else
	{
		iter.m_pTarget->m_pPrev->m_pNext = iter.m_pTarget->m_pNext;
	}
	delete iter.m_pTarget;
	return iterator(this, NodeBuf);

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

