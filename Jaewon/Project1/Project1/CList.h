#pragma once
#include <assert.h>
#include <iostream>

using std::cout;
using std::endl;

struct Node {
	int data;
	Node* next;
	Node* prev;

	Node():data(0), next(nullptr), prev(nullptr){}
	Node(int d, Node* n = nullptr, Node* p = nullptr):data(d), next(n), prev(p){}
	~Node(){}
};

class CList
{
private:
	int dCnt;
	Node* head;
	Node* tail;
	
public:
	void pushFront(int d);
	void pushBack(int d);
	int size() { return dCnt; }
	
	
	// ���� ������
	// 1. ���� �����Ͱ� ���� ��� ����
	// 2. count �Ҵ� ��
	// 3. ���������� ���� �Ҵ� �� ������ ���� �ݺ�
	CList& operator =(const CList& oth) {
		cout << "���翬" << endl;
		if (nullptr == head) {
			Node* iter = head;
			for (int i = 0; i < dCnt; i++) {
				Node* temp = iter->next;
				delete iter;
				iter = temp;
			}
		}
		dCnt = oth.dCnt;
		if (oth.head != nullptr) {
			Node* hNode = new Node();
			Node* iter = oth.head->next;
			hNode->data = oth.head->data;
			Node* prevIter = hNode;
			for (int i = 1; i < dCnt; ++i) {
				Node* newNode = new Node();
				newNode->data = iter->data;
				newNode->prev = prevIter;
				prevIter->next = newNode;
				iter = iter->next;
				prevIter = prevIter->next;
			}
			head = hNode;
			tail = prevIter;
		}
		return *this;
	}
	// �̵� ������
	// 1. ���� �����Ͱ� ���� ��� ����
	// 2. count �Ҵ� ��
	// 3. head, tail �ּҰ� �Ű��� ��
	// 4. ���� count = 0, head, tail = nullptr
	CList& operator =(CList&& oth) {
		cout << "�̵���" << endl;
		if (nullptr == head) {
			Node* iter = head;
			for (int i = 0; i < dCnt; i++) {
				Node* temp = iter->next;
				delete iter;
				iter = temp;
			}
		}
		if (oth.head != nullptr) {
			head = oth.head;
			tail = oth.tail;
		}
		oth.head = nullptr;
		oth.tail = nullptr;
		oth.dCnt = 0;
		return *this;
	}

	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& it);

public:
	CList():dCnt(0), head(nullptr), tail(nullptr){}
	// ���� ������
	// 1. count ����
	// 2. ���ο� ������ ��ŭ �Ҵ��ϸ鼭
	//    ������ �Űܿ���
	CList(const CList& oth) :dCnt(oth.dCnt), head(nullptr), tail(nullptr) {
		cout << "�����" << endl;
		if (oth.head != nullptr) {
			Node* hNode = new Node();
			Node* iter = oth.head->next;
			hNode->data = oth.head->data;
			Node* prevIter = hNode;
			for (int i = 1; i < dCnt; ++i) {
				Node* newNode = new Node();
				newNode->data = iter->data;
				newNode->prev = prevIter;
				prevIter->next = newNode;
				iter = iter->next;
				prevIter = prevIter->next;
			}
		}
	}
	// �̵� ������
	// 1. ���������� ������ ��������
	//   - count, maxcount, pData �ּ�
	// 2. ���� ������ �� ����
	//   - count, maxcount 0����
	//   - pData �ּ� nullptr��
	CList(CList&& oth) :dCnt(oth.dCnt), head(nullptr), tail(nullptr) {
		cout << "�̵���" << endl;
		if (oth.head != nullptr) {
			head = oth.head;
			tail = oth.tail;
		}
		oth.head = nullptr;
		oth.tail = nullptr;
		oth.dCnt = 0;
	}
	~CList();

	class iterator {
	private:
		CList* host;
		Node* target;
	public:
		bool operator == (const iterator& oth) {
			if (host == oth.host && target == oth.target)
				return true;
			return false;
		}
		bool operator != (const iterator& oth) {
			return !(*this == oth);
		}

		
		iterator& operator ++() {
			if (target == nullptr) {
				assert(nullptr);
			}
			else {
				target = target->next;
			}
			return *this;
		}
		iterator& operator ++(int) {
			iterator copyiter(*this);
			if (target == nullptr) {
				assert(nullptr);
			}
			else {
				target = target->next;
			}
			return copyiter;
		}
		iterator& operator --() {
			if (target == nullptr) {
				assert(nullptr);
			}
			else {
				target = target->prev;
			}
			return *this;
		}
		iterator& operator --(int) {
			iterator copyiter(*this);
			if (target == nullptr) {
				assert(nullptr);
			}
			else {
				target = target->prev;
			}
			return copyiter;
		}
		int& operator *() {
			return target->data;
		}
		
	public:
		iterator():host(nullptr), target(nullptr){}
		iterator(CList* c, Node* n = nullptr) :host(c), target(n) {}
		~iterator(){}

		friend class CList;
	};
};

