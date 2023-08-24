#pragma once
#include <assert.h>
#include <iostream>
// CList ���ø�ȭ


// Node ����
// 1. �־�� �ϴ� ������
// 2. ���� ����� �ּ�
// 3. ���� ����� �ּ�
template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
	Node():data(NULL), prev(0), next(0) {}
	Node(T d, Node* p, Node* n):data(d), prev(p), next(n){}
};


// ���ø� ��ũ�� ����Ʈ To Do List
// 1. ��� ����
//    - ����Ʈ�� ù��°, �������� �ּ�
//      head, tail
//    - ����Ʈ ���� ����
//      dCnt
// 2. ��� �Լ�
//    - pushBack
//    - pushFront
//    - size
//    - erase
// 3. ������, �Ҹ���
// 4. iterator Ŭ����
//  - ������ �����ε�
//     ++, !=, ==, --, *
template <typename T>
class TemplateCList{
	int dCnt;
	Node<T>* head;
	Node<T>* tail;

public:
	TemplateCList() {}
	// ���� ������
	// count ����
	// ���ο� �����͸� ������ ����Ʈ�� cnt��ŭ �Ҵ� ��
	// �� �״�� ����
	TemplateCList(const TemplateCList<T>& oth):dCnt(oth.dCnt), head(nullptr), tail(nullptr) {
		if (oth.head != nullptr) {
			Node<T>* hNode = new Node<T>();
			Node<T>* iter = oth.head->next;
			hNode->data = oth.head->data;
			Node<T>* prevIter = hNode;
			for (int i = 1; i < dCnt; ++i) {
				Node<T>* NewNode = new Node<T>(iter->data, nullptr, prevIter);
				prevIter->next = NewNode;
				iter = iter->next;
				prevIter = NewNode;
			}
			head = hNode;
			tail = prevIter;
		}
	}
	// �̵� ������
	// ���������� �� ������ ��
	// ���� ������ �� ����
	TemplateCList(TemplateCList<T>&& oth):dCnt(oth.dCnt), head(oth.head), tail(oth.tail) {
		oth.head = nullptr;
		oth.tail = nullptr;
		oth.dCnt = 0;
	}
	~TemplateCList(){}

public:
	// ù �Է��̸� head�� ����
	// �ƴϸ� tail�� next�� ���� ��
	// tail�� ����
	void pushBack(const T& data) {
		Node<T>* newNode = new Node<T>(data, tail, nullptr);
		if (nullptr == head)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
		++dCnt;
	}
	// ù �Է��̸� tail�� ����
	// �ƴϸ� head�� prev�� ���� ��
	// head�� ����
	void pushFront(const T& data) {
		Node<T>* newNode = new Node<T>(data, nullptr, head);
		if (nullptr == tail)
			tail = newNode;
		else
			head->prev = newNode;
		head = newNode;
		++dCnt;
	}
	int size() { return dCnt; }


	// ���� ������
	// ���� �����Ͱ� �־����� �Ҵ� ���� ��
	// �����Ϸ��� count ��ŭ ������ �Ҵ� ��Ű��
	// ���������� ���� �Ҵ��Ͽ� ������ ���� �ݺ�
	TemplateCList& operator =(const TemplateCList<T>& oth) {
		if (nullptr == head) {
			Node<T>* iter = head;
			for (int i = 0; i < dCnt; ++i) {
				Node<T>* temp = iter->next;
				delete iter;
				iter = temp;
			}
		}
		dCnt = oth.dCnt;
		if (oth.head != nullptr) {
			Node<T>* hNode = new Node<T>();
			Node<T>* iter = oth.head->next;
			hNode->data = oth.head->data;
			Node<T>* prevIter = hNode;
			for (int i = 1; i < dCnt; ++i) {
				Node<T>* NewNode = new Node<T>(iter->data, nullptr, prevIter);
				prevIter->next = NewNode;
				iter = iter->next;
				prevIter = NewNode;
			}
			head = hNode;
			tail = prevIter;
		}
		return *this;
	}

	// �̵� ���� ������
	// ���� �����Ͱ� �־����� �Ҵ� ���� �� 
	// �ּҰ� �Ű��� ��
	// ���� ������ ����
	TemplateCList& operator =(TemplateCList<T>&& oth) {
		if (nullptr == head) {
			Node<T>* iter = head;
			for (int i = 0; i < dCnt; ++i) {
				Node<T>* temp = iter->next();
				delete iter;
				iter = temp;
			}
		}
		dCnt = oth.dCnt;
		head = oth.head;
		tail = oth.tail;
		oth.dCnt = 0;
		oth.head = nullptr;
		oth.tail = nullptr;
		
		return this;
	}


	class iterator;
	iterator begin(){
		return iterator(this, head);
	}

	iterator end(){
		return iterator(this, nullptr);
	}

	// 1. ������ ��尡 ù��° ���� 
	// head�� target�� next�� ����
	// �ƴϸ� target�� prev�� next�� next�� ����
	// 2. ������ ��尡 ������ ����
	// tail�� target�� tail�� ����
	// �ƴϸ� target�� next�� prev�� target�� prev�� ����
	// 3. delete �� ī��Ʈ down
	// 4. target�� next�� ���� iterator return
	iterator erase(const iterator& it)
	{
		Node<T>* p = it.target->prev;
		Node<T>* n = it.target->next;
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
	class iterator {
		TemplateCList<T>* host;
		Node<T>* target;
	
	public:
		// host�� target�� ������ true
		bool operator ==(const iterator& oth){
			if (host == oth.host && target == oth.target)
				return true;
			return false;
		}
		// ==�� �ݴ��� ����
		bool operator !=(const iterator& oth){ return !(*this == oth);}
		// end() ���¸� ����
		// �ƴϸ� next��
		iterator& operator ++(){
			if (nullptr == target)
				assert(nullptr);
			else{
				target = target->next;
			}
			return *this;
		}
		iterator operator ++(int){
			iterator copyiter(*this);
			++(*this);
			return copyiter;
		}
		// prev�� nullptr ���¸� ����
		// �ƴϸ� prev��
		iterator& operator --(){
			if (nullptr == target)
				assert(nullptr);
			else {
				target = target->prev;
			}
			return *this;
		}
		iterator operator--(int){
			iterator copyiter(*this);
			--(*this);
			return copyiter;
		}
		// target�� nullptr�� ����
		// �ƴϸ� ������ �ִ� �� ����
		T& operator*(){
			if (nullptr == target)
				assert(nullptr);
			return target->data;
		}

	public:
		iterator():host(nullptr), target(nullptr){}
		iterator(TemplateCList<T>* l, Node<T>* n):host(l),target(n){}
		~iterator(){}
		friend class TemplateCList;
	};
};