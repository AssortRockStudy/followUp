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
	// 복사 생성자
	// count 유지
	// 새로운 데이터를 복사할 리스트의 cnt만큼 할당 후
	// 값 그대로 복사
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
	// 이동 생성자
	// 원본값에서 다 가져온 후
	// 원본 데이터 값 제거
	TemplateCList(TemplateCList<T>&& oth):dCnt(oth.dCnt), head(oth.head), tail(oth.tail) {
		oth.head = nullptr;
		oth.tail = nullptr;
		oth.dCnt = 0;
	}
	~TemplateCList(){}

public:
	// 첫 입력이면 head로 설정
	// 아니면 tail의 next에 설정 후
	// tail에 연결
	void pushBack(const T& data) {
		Node<T>* newNode = new Node<T>(data, tail, nullptr);
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
		Node<T>* newNode = new Node<T>(data, nullptr, head);
		if (nullptr == tail)
			tail = newNode;
		else
			head->prev = newNode;
		head = newNode;
		++dCnt;
	}
	int size() { return dCnt; }


	// 대입 연산자
	// 원래 데이터가 있었으면 할당 해제 후
	// 복사하려는 count 만큼 데이터 할당 시키고
	// 원본데이터 공간 할당하여 데이터 복사 반복
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

	// 이동 대입 연산자
	// 원래 데이터가 있었으면 할당 해제 후 
	// 주소값 옮겨준 후
	// 원본 데이터 제거
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