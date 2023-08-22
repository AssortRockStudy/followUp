#include "CList.h"

void CList::pushFront(int d)
{
	Node* newNode = new Node(d, head);
	if (nullptr == head)
		tail = newNode;
	else
		head->prev = newNode;
	head = newNode;
	++dCnt;
}

void CList::pushBack(int d)
{
	Node* newNode = new Node(d, nullptr, tail);
	if (nullptr == head)
		head = newNode;
	else
		tail->next = newNode;
	tail = newNode;
	++dCnt;
}

// begin 수정
// 아무것도 없을 때(end와 begin이 같으면)
typename CList::iterator CList::begin()
{
	if (nullptr == head) {
		return iterator(this, nullptr);
	}
	return iterator(this, head);
}

// end 수정
// 조건 : nullptr
// tail의 next는 nullptr이기 때문
typename CList::iterator CList::end()
{
	return iterator(this, nullptr);
}

typename CList::iterator CList::erase(iterator& it)
{
	Node* p = it.target->prev;
	Node* n = it.target->next;
	if (p == nullptr) {
		head = n;
	}
	else {
		p->next = n;
	}
	if (n == nullptr) {
		tail = p;
	}
	else {
		n->prev = p;
	}
	delete it.target;
	--dCnt;
	return iterator(this, n);
	
}

CList::~CList()
{
	Node* delNode = head;
	for (int i = 0; i < dCnt; ++i) {
		Node* next = delNode->next;
		delete delNode;
		delNode = next;
	}
}
