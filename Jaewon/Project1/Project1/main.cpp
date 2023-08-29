#include <stdlib.h>
#include <stdio.h>
#include "CList.h"

using std::cout;
using std::endl;


// ToDoList
// 1. CopyShallow�� CopyDeep�� ���� ������ ��ü ����
// 2. ����, �̵� ������ ����
// 3. ����, �̵� ������ ����
class arr {
private:
	int dCnt;
	int mCnt;
	int* pData;

public:
	arr(int t) :dCnt(0), mCnt(t), pData(nullptr) {
		pData = new int[mCnt];
	}
	// ���� ������
	arr(const arr& oth) {
		cout << "���� ������ ȣ��" << endl;
		if (nullptr != pData) {
			delete[] pData;
		}
		dCnt = oth.dCnt;
		mCnt = oth.mCnt;
		pData = new int[mCnt];
		for (int i = 0; i < dCnt; ++i) {
			pData[i] = oth.pData[i];
		}
	}
	// �̵� ������
	arr(arr&& oth) {
		cout << "�̵� ������ ȣ��" << endl;
		if (nullptr != pData) {
			delete[] pData;
		}
		dCnt = oth.dCnt;
		mCnt = oth.mCnt;
		pData = oth.pData;
		oth.dCnt = 0;
		oth.mCnt = 0;
		oth.pData = nullptr;
	}
	// ����(����) ������
	arr& operator =(const arr& oth) {
		cout << "���� ������ ȣ��" << endl;
		if (nullptr != pData) {
			delete[] pData;
		}
		dCnt = oth.dCnt;
		mCnt = oth.mCnt;
		pData = new int[mCnt];
		for (int i = 0; i < dCnt; ++i) {
			pData[i] = oth.pData[i];
		}
		return *this;
	}
	arr& operator =(arr&& oth) {
		cout << "�̵� ���� ������ ȣ��" << endl;
		if (nullptr != pData) {
			delete[] pData;
		}
		dCnt = oth.dCnt;
		mCnt = oth.mCnt;
		pData = oth.pData;
		oth.dCnt = 0;
		oth.mCnt = 0;
		oth.pData = nullptr;
		return *this;
	}
	void push(int data) {
		pData[dCnt++] = data;
	}

};


void swap(CList& a, CList& b) {
	CList temp = std::move(a); // �̵� ������ ���
	a = std::move(b); // �̵� ������ ���
	b = std::move(temp); // �̵� ������ ���
}



void CopyShallow(arr& a, arr& b) {
	a = std::move(b);
}

void CopyDeep(arr& a, arr& b) {
	a = b;
}

int main() {
	CList a;
	a.pushFront(5);
	a.pushFront(8);
	a.pushFront(2);
	a.pushFront(9);
	a.pushFront(40);
	a.pushFront(30);
	CList::iterator iter = a.begin();
	for (iter = a.begin(); iter != a.end(); ++iter) {
		cout << *iter << endl; 
	}
	iter = a.begin();
	iter++;
	iter++;
	iter++;
	--iter;
	cout << "���� ������" << endl;
	cout << *iter-- << endl; // 9 >> 257??
	cout << *iter << endl; // 40 >> Ȯ��
	cout << *(--iter) << endl; // 30 >> Ȯ��

	CList b;
	b.pushFront(100);
	swap(a, b); // �̵� ������ > �̵� ������ > �̵� ������ ���
	cout << "Array 1" << endl;
	for (iter = a.begin(); iter != a.end(); ++iter) {
		cout << *iter << endl;
	}
	cout << "Array 2" << endl;
	for (iter = b.begin(); iter != b.end(); ++iter) {
		cout << *iter << endl;
	}
	CList c = a; // ���� ���� ���(���� ������)
	c = b; // ���� ���� ���(���� ������)

	arr i(5);
	arr q(10);
	arr w = i; // ���� ������
	arr p = std::move(w); // �̵� ������
	w = q; // ����(����) ������
	arr m(100);
	CopyDeep(m, q); // ����(����) ������ ȣ��
	CopyShallow(i, q); // �̵� ���� ������ ȣ��
	return 0;
}