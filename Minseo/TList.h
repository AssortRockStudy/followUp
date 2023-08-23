#pragma once

template <typename T>
class TNode
{
public:
	// 들어가야 하는 멤버
	// 데이터, 이전 노드, 다음 노드
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
private://멤버 변수
	//들어가야하는 멤버는 일단...
	// 첫 노드, 끝 노드, 데이터 개수
	TNode<T>*	m_pHead;
	TNode<T>*	m_pTail;
	int			m_Count;
public:// 멤버 함수
	void push_back(const T& data);// 인자를 const T&로 해주는 이유는 원본을 수정할 여지가 없게 하면서, 싼 값에 받아오기
	void push_front(const T& data);// 인자를 const T&로 해주는 이유는 원본을 수정할 여지가 없게 하면서, 싼 값에 받아오기



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

