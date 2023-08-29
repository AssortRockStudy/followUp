#pragma once
#include "TemplateCList.h"


enum {
	PARENT,
	LCHD,
	RCHD,
};

template<typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;
public:
	Pair():first(), second(){}
	Pair(T1 t1, T2 t2):first(t1), second(t2){}
};

template<typename T1, typename T2>
struct TNode{
	Pair<T1, T2> data;
	TNode<T1, T2>* othPtr[3];


public:
	TNode() :data(), othPtr{} {}
	TNode(Pair<T1, T2> d, TNode<T1, T2>* p = nullptr, TNode<T1, T2>* l = nullptr, TNode<T1, T2>* r = nullptr) :data(d), othPtr{ p, l, r } {}
	~TNode(){}
};

template<typename T1, typename T2>
class BST {
	// 멤버 변수
	// root 노드
	// cnt - 데이터의 개수
	TNode<T1, T2>* root;
	int cnt;


private:
	// 비우기
	// 재귀 이용하여 왼쪽 끝 > 오른쪽 끝 순서로 노드 삭제
	void clear(TNode<T1, T2>* n) {
		if (n->othPtr[LCHD] != nullptr) {
			clear(n->othPtr[LCHD]);
		}
		if (n->othPtr[RCHD] != nullptr) {
			clear(n->othPtr[RCHD]);
		}
		delete n;
	}
public:
	BST():root(nullptr), cnt(0){}
	~BST() { 
		clear(root);
		root = nullptr;
	}

public:
	class iterator;

	// head가 nullptr일 경우(아무것도 안들어 있을 경우)
	// end()를 가리키도록
	// 아니라면 제일 왼쪽 노드를 가리키도록 한다.
	iterator begin() {
		if (nullptr == root)
			return end();

		TNode<T1, T2>* iter = root;
		while (nullptr != iter->othPtr[LCHD])
			iter = iter->othPtr[LCHD];
		return iterator(this, iter);
	}

	iterator end() {
		return iterator(this, nullptr);
	}

	// 입력
	// 기본적으로 현재 위치해있는 데이터 값보다 작으면 left
	// 나머지는 right
	// root가 head일 경우 root에 바로 입력
	// 이후 ++cnt
	void push(const Pair<T1, T2>& d) {
		TNode<T1, T2>* newNode = new TNode<T1, T2>(d);
		if (nullptr == root) {
			root = newNode;
		}
		else {
			TNode<T1, T2>* iter = root;
			TNode<T1, T2>* prev = nullptr;
			int pos = -1;
			while (iter != nullptr) {
				if (iter->data.first > d.first) {
					prev = iter;
					iter = iter->othPtr[LCHD];
					pos = LCHD;
				}
				else {
					prev = iter;
					iter = iter->othPtr[RCHD];
					pos = RCHD;
				}
			}
			newNode->othPtr[PARENT] = prev;
			prev->othPtr[pos] = newNode;
		}
		++cnt;
	}
	

	// 전위 순회
	// 먼저 node의 데이터 값을 출력한 뒤
	// 왼쪽노드, 오른쪽 노드 순서로 재귀 진행
	// 결과적으로 부 - 좌 - 우 순서로 출력될 것이다.
	void PrintFrontTree(const TNode<T1, T2>* n) {
		cout << n->data.second << endl;
		if (n->othPtr[LCHD] != nullptr) {
			PrintFrontTree(n->othPtr[LCHD]);
		}
		if (n->othPtr[RCHD] != nullptr) {
			PrintFrontTree(n->othPtr[RCHD]);
		}
	}

	// 중위 순회
	// 먼저 왼쪽 노드로 재귀 진행 후 
	// node의 데이터 값을 출력 후
	// 오른쪽 노드로 재귀 진행
	// 결과적으로 좌 - 부 - 우 순서로 출력될 것이다.
	void PrintMiddleTree(const TNode<T1, T2>* n) {
		if (n->othPtr[LCHD] != nullptr) {
			PrintMiddleTree(n->othPtr[LCHD]);
		}
		cout << n->data.second << endl;
		if (n->othPtr[RCHD] != nullptr) {
			PrintMiddleTree(n->othPtr[RCHD]);
		}
	}

	// 후위 순회
	// 먼저 왼쪽 노드로 재귀 진행 후
	// 오른쪽 노드로 재귀 진행 후 
	// 현재 데이터 값 출력
	// 결과적으로 좌 - 우 - 중 순서로 출력될 것이다.
	void PrintRearTree(const TNode<T1, T2>* n) {
		if (n->othPtr[LCHD] != nullptr) {
			PrintRearTree(n->othPtr[LCHD]);
		}
		if (n->othPtr[RCHD] != nullptr) {
			PrintRearTree(n->othPtr[RCHD]);
		}
		cout << n->data.second << endl;
	}

	// 층별 순회
	// dfs원리 이용해서
	// 노드들이 들어있는 queue에서 팝한 후
	// 출력하고
	// 다음방향(left, right) 방향으로의 노드를 
	// queue에 다시 집어넣는 식으로 하여 queue가 빌때까지 반복
	void PrintLevelTree() {
		if (nullptr != root) {
			TemplateCList<TNode<T1, T2>*> temp;
			temp.pushBack(root);

			while(temp.size() != 0){
				TNode<T1, T2>* lvP = temp.getFront();
				temp.popFront();
				cout << lvP->data.second << endl;

				if (nullptr != lvP->othPtr[LCHD])
					temp.pushBack(lvP->othPtr[LCHD]);
				if (nullptr != lvP->othPtr[RCHD])
					temp.pushBack(lvP->othPtr[RCHD]);
			}
		}
	}
	
	
	
	
	
	// 멤버 변수를 외부에서 접근할 수 없으므로
	// int 값을 주어 순회를 출력하도록 함
	void PrintTree(int num) {
		switch (num)
		{
		case 1:
			cout << "전위 순회" << endl;
			PrintFrontTree(root);
			break;
		case 2:
			cout << "중위 순회" << endl;
			PrintMiddleTree(root);
			break;
		case 3:
			cout << "후위 순회" << endl;
			PrintRearTree(root);
			break;
		case 4:
			cout << "층별 순회" << endl;
			PrintLevelTree();
			break;
		default:
			break;
		}
	}

	// 검색
	// 순회 후 나오면 값 출력 / 안 나오면 -1 출력
	T2 search(const Pair<T1, T2>& d) {
		TNode<T1, T2>* iter = root;
		TNode<T1, T2>* prev = nullptr;
		while (iter != nullptr) {
			if (iter->data.second == d.second) {
				return d.second;
			}
			if (iter->data.first > d.first) {
				prev = iter;
				iter = iter->othPtr[LCHD];
			}
			else {
				prev = iter;
				iter = iter->othPtr[RCHD];
			}
		}
		return -1;
		
	}

	class iterator {
		BST<T1, T2>* host;
		TNode<T1, T2>* target;

	public:
		Pair<T1, T2>& operator *() {
			return target->data;
		}

		Pair<T1, T2>* operator ->() {
			return &target->data;
		}
		bool operator == (const iterator& oth) {
			return host == oth.host && target == oth.target;
		}
		bool operator != (const iterator& oth) {
			return !((*this) == oth);
		}


		// 중위 후속자 찾기
		// 현재 노드가 nullptr이면 경고
		// 1. 오른쪽 자식이 있는지 확인
		//    > 있으면 오른쪽 자식으로 내려간 후 왼쪽 자식쪽으로 쭉 내려가기
		// 2. 자신이 왼쪽 자식 노드인지를 확인
		//    > 아니라면 왼쪽 자식이 될 때까지 위로 올라가기
		iterator& operator ++() {
			assert(target);
			TNode<T1, T2>* successor = nullptr;
			if (target->othPtr[RCHD] != nullptr) {
				successor = target->othPtr[RCHD];
				while (nullptr != successor->othPtr[LCHD])
					successor = successor->othPtr[LCHD];
			}
			else {
				successor = target;
				while (true) {
					if (nullptr == successor->othPtr[PARENT]) {
						successor = nullptr;
						break;
					}
					else if (successor->othPtr[PARENT]->othPtr[LCHD] == successor) {
						successor = successor->othPtr[PARENT];
						break;
					}
					successor = successor->othPtr[PARENT];
				}
			}
			target = successor;
			return *this;
		}
		iterator operator ++(int) {
			iterator copyiter(*this);
			++(*this);
			return copyiter;
		}
		// ++와 반대로 생각
		// 현재 노드가 nullptr이면 경고
		// 1. 왼쪽 자식이 있는지 확인
		//    > 있으면 왼쪽 자식으로 내려간 후 오른쪽 자식쪽으로 쭉 내려가기
		// 2. 자신이 오른쪽 자식 노드인지를 확인
		//    > 아니라면 오른쪽 자식이 될 때까지 위로 올라가기
		iterator& operator --() {
			assert(target);
			TNode<T1, T2>* predecessor = nullptr;
			if (target->othPtr[LCHD] != nullptr) {
				predecessor = target->othPtr[LCHD];
				while (nullptr != predecessor->othPtr[RCHD])
					predecessor = predecessor->othPtr[RCHD];
			}
			else {
				predecessor = target;
				while (true) {
					if (nullptr == predecessor->othPtr[PARENT]) {
						predecessor = nullptr;
						break;
					}
					else if (predecessor->othPtr[PARENT]->othPtr[RCHD] == predecessor) {
						predecessor = predecessor->othPtr[PARENT];
						break;
					}
					predecessor = predecessor->othPtr[PARENT];
				}
			}
			target = predecessor;
			return *this;
		}

		iterator operator --(int) {
			iterator copyiter(*this);
			--(*this);
			return copyiter;
		}
	public:
		iterator():host(nullptr), target(nullptr){}
		iterator(BST<T1, T2>* h, TNode<T1, T2>* t) :host(h), target(t) {}
		~iterator(){}
		friend class BST<T1, T2>;

	};


};