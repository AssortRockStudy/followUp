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
	
	
	// 복사 연산자
	// 1. 원래 데이터가 있을 경우 해제
	// 2. count 할당 후
	// 3. 원본데이터 공간 할당 후 데이터 복사 반복
	CList& operator =(const CList& oth) {
		cout << "복사연" << endl;
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
	// 이동 연산자
	// 1. 원래 데이터가 있을 경우 해제
	// 2. count 할당 후
	// 3. head, tail 주소값 옮겨준 후
	// 4. 원본 count = 0, head, tail = nullptr
	CList& operator =(CList&& oth) {
		cout << "이동연" << endl;
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
	// 복사 생성자
	// 1. count 유지
	// 2. 새로운 데이터 만큼 할당하면서
	//    데이터 옮겨오기
	CList(const CList& oth) :dCnt(oth.dCnt), head(nullptr), tail(nullptr) {
		cout << "복사생" << endl;
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
	// 이동 생성자
	// 1. 원본값에서 데이터 가져오기
	//   - count, maxcount, pData 주소
	// 2. 원본 데이터 값 제거
	//   - count, maxcount 0으로
	//   - pData 주소 nullptr로
	CList(CList&& oth) :dCnt(oth.dCnt), head(nullptr), tail(nullptr) {
		cout << "이동생" << endl;
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

