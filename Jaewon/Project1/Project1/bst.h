#pragma once
#include <iostream>
#include "TemplateCList.h"

using std::cout;
using std::endl;


enum {
	PARENT,
	LCHD,
	RCHD,
};

template<typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;
};

template<typename T1, typename T2>
struct TNode{
	Pair<T1, T2> data;
	TNode<T1, T2>* othPtr[3];
public:
	TNode(){}
	TNode(Pair<T1, T2> d):data(d){
		for (int i = 0; i < 3; ++i) {
			othPtr[i] = nullptr;
		}
	}
	~TNode(){}
};

template<typename T1, typename T2>
class BST {
	// ��� ����
	// root ���
	// cnt - �������� ����
	TNode<T1, T2>* root;
	int cnt;


private:
	// ����
	// ��� �̿��Ͽ� ���� �� > ������ �� ������ ��� ����
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

	// �Է�
	// �⺻������ ���� ��ġ���ִ� ������ ������ ������ left
	// �������� right
	// root�� head�� ��� root�� �ٷ� �Է�
	// ���� ++cnt
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
	

	// ���� ��ȸ
	// ���� node�� ������ ���� ����� ��
	// ���ʳ��, ������ ��� ������ ��� ����
	// ��������� �� - �� - �� ������ ��µ� ���̴�.
	void PrintFrontTree(const TNode<T1, T2>* n) {
		cout << n->data.second << endl;
		if (n->othPtr[LCHD] != nullptr) {
			PrintFrontTree(n->othPtr[LCHD]);
		}
		if (n->othPtr[RCHD] != nullptr) {
			PrintFrontTree(n->othPtr[RCHD]);
		}
	}

	// ���� ��ȸ
	// ���� ���� ���� ��� ���� �� 
	// node�� ������ ���� ��� ��
	// ������ ���� ��� ����
	// ��������� �� - �� - �� ������ ��µ� ���̴�.
	void PrintMiddleTree(const TNode<T1, T2>* n) {
		if (n->othPtr[LCHD] != nullptr) {
			PrintMiddleTree(n->othPtr[LCHD]);
		}
		cout << n->data.second << endl;
		if (n->othPtr[RCHD] != nullptr) {
			PrintMiddleTree(n->othPtr[RCHD]);
		}
	}

	// ���� ��ȸ
	// ���� ���� ���� ��� ���� ��
	// ������ ���� ��� ���� �� 
	// ���� ������ �� ���
	// ��������� �� - �� - �� ������ ��µ� ���̴�.
	void PrintRearTree(const TNode<T1, T2>* n) {
		if (n->othPtr[LCHD] != nullptr) {
			PrintRearTree(n->othPtr[LCHD]);
		}
		if (n->othPtr[RCHD] != nullptr) {
			PrintRearTree(n->othPtr[RCHD]);
		}
		cout << n->data.second << endl;
	}

	// ���� ��ȸ
	// dfs���� �̿��ؼ�
	// ������ ����ִ� queue���� ���� ��
	// ����ϰ�
	// ��������(left, right) ���������� ��带 
	// queue�� �ٽ� ����ִ� ������ �Ͽ� queue�� �������� �ݺ�
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
	
	
	
	
	
	// ��� ������ �ܺο��� ������ �� �����Ƿ�
	// int ���� �־� ��ȸ�� ����ϵ��� ��
	void PrintTree(int num) {
		switch (num)
		{
		case 1:
			cout << "���� ��ȸ" << endl;
			PrintFrontTree(root);
			break;
		case 2:
			cout << "���� ��ȸ" << endl;
			PrintMiddleTree(root);
			break;
		case 3:
			cout << "���� ��ȸ" << endl;
			PrintRearTree(root);
			break;
		case 4:
			cout << "���� ��ȸ" << endl;
			PrintLevelTree();
			break;
		default:
			break;
		}
	}

	// �˻�
	// ��ȸ �� ������ �� ��� / �� ������ -1 ���
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
};