#pragma once
#include <assert.h>
#include <iostream>
// CList 탬플릿화


// Node 생성
// 1. 넣어야 하는 데이터
// 2. 이전 노드의 주소
// 3. 다음 노드의 주소
template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
	Node():data(NULL), prev(0), next(0) {}
	Node(T d, Node* p, Node* n):data(d), prev(p), next(n){}
};


// 템플릿 링크드 리스트 To Do List
// 1. 멤버 변수
//    - 리스트의 첫번째, 마지막의 주소
//      head, tail
//    - 리스트 원소 개수
//      dCnt
// 2. 멤버 함수
//    - pushBack
//    - pushFront
//    - size
//    - erase
// 3. 생성자, 소멸자
// 4. iterator 클래스
//  - 연산자 오버로딩
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
	// 첫 입력이면 head로 설정
	// 아니면 tail의 next에 설정 후
	// tail에 연결
	void pushBack(const T& data) {
		Node<T>* newNode = new Node<T>(d, nullptr, tail);
		if (nullptr == head)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
		++dCnt;
	}
	// 첫 입력이면 tail로 설정
	// 아니면 head의 prev에 설정 후
	// head에 연결
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

	// 1. 삭제할 노드가 첫번째 노드면 
	// head를 target의 next로 설정
	// 아니면 target의 prev의 next를 next로 설정
	// 2. 삭제할 노드가 마지막 노드면
	// tail을 target의 tail로 설정
	// 아니면 target의 next의 prev를 target의 prev로 설정
	// 3. delete 후 카운트 down
	// 4. target의 next를 가진 iterator return
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
		// host와 target이 같으면 true
		bool operator ==(const iterator& oth){
			if (host == oth.host && target == oth.target)
				return true;
			return false;
		}
		// ==와 반대결과 리턴
		bool operator !=(const iterator& oth){ return !(*this == oth);}
		// end() 상태면 에러
		// 아니면 next로
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
		// prev가 nullptr 상태면 에러
		// 아니면 prev로
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
		// target이 nullptr면 에러
		// 아니면 가지고 있는 값 리턴
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