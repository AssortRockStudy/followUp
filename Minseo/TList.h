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
	int size() { return m_Count; }
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

	public://operator ++ -- == != *
		iterator& operator++()
		{
			// ���� ó��) ���ͷ����Ͱ� �߸� �� �����͸� ����Ű�� ���� ���, �߸��� list��ü�� ����Ű�� ���� ���
			assert(!(m_pOwner == nullptr || m_pTarget == nullptr));
			m_pTarget = m_pTarget->m_pNext;
			return *this;
		}
		iterator operator++(int)
		{
			// ���� ó��) ���ͷ����Ͱ� �߸� �� �����͸� ����Ű�� ���� ���, �߸��� list��ü�� ����Ű�� ���� ���
			iterator Buffer(m_pOwner, m_pTarget);
			assert(!(m_pOwner == nullptr || m_pTarget == nullptr));
			m_pTarget = m_pTarget->m_pNext;
			return Buffer;
		}
		iterator& operator--()
		{
			// ���� ó��) ���ͷ����Ͱ� �߸� �� �����͸� ����Ű�� ���� ���, �߸��� list��ü�� ����Ű�� ���� ���
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
			// ���� ó��) ���ͷ����Ͱ� �߸� �� �����͸� ����Ű�� ���� ���, �߸��� list��ü�� ����Ű�� ���� ���
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
	TNode<T>* Target = iter.m_pTarget;
	TNode<T>* nextNode = Target->m_pNext;
	// ���� ó��) ���� List ��ü�� �������ΰ�?
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

