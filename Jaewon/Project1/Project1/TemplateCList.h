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
	~TemplateCList(){}

public:
	void pushBack(const T& data) {
		Node<T>* newNode = new Node<T>(d, nullptr, tail);
		if (nullptr == head)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
		++dCnt;
	}
	void pushFront(const T& data) {
		Node<T>* newNode = new Node<T>(d, nullptr, tail);
		if (nullptr == tail)
			tail = newNode;
		else
			head->prev = newNode;
		head = newNode;
		++dCnt;
	}
	int size() { return dCnt; }

	class iterator;
	iterator begin(){
		return iterator(this, head);
	}

	iterator end(){
		return iterator(this, nullptr);
	}

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
		bool operator ==(const iterator& oth){
			if (host == oth.host && target == oth.target)
				return true;
			return false;
		}
		bool operator !=(const iterator& oth){ return !(*this == oth);}
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