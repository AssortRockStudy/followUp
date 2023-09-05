// To Do List
// 1. R-Value swap 구현
// 2. 이동 연산자, 생성자 / 복사 연산자, 생성자 호출 확인해보기
// 3. CopyShallow와 CopyDeep을 위한 간단한 객체 생성
// 4. 복사, 이동 생성자 구현
// 5. 복사, 이동 연산자 구현
#include <stdlib.h>
#include <stdio.h>
#include "TemplateCList.h"

using std::cout;
using std::endl;

class arr {
private:
	int dCnt;
	int mCnt;
	int* pData;

public:
	arr(int t) :dCnt(0), mCnt(t), pData(nullptr) {
		pData = new int[mCnt];
	}
	// 복사 생성자
	arr(const arr& oth) {
		cout << "복사 생성자 호출" << endl;
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
	// 이동 생성자
	arr(arr&& oth) {
		cout << "이동 생성자 호출" << endl;
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
	// 대입(복사) 연산자
	arr& operator =(const arr& oth) {
		cout << "대입 연산자 호출" << endl;
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
		cout << "이동 대입 연산자 호출" << endl;
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

void CopyShallow(arr& a, arr& b) {
	a = std::move(b);
}

void CopyDeep(arr& a, arr& b) {
	a = b;
}

int main() {
	TemplateCList<int> a;
	a.pushFront(5);
	a.pushFront(8);
	a.pushFront(2);
	a.pushFront(9);
	a.pushFront(40);
	a.pushFront(30);
	TemplateCList<int>::iterator iter = a.begin();
	for (iter = a.begin(); iter != a.end(); ++iter) {
		cout << *iter << endl;
	}
	iter = a.begin();
	iter++;
	iter++;
	iter++;
	--iter;
	cout << "감소 연산자" << endl;
	cout << *iter-- << endl; // 9
	cout << *iter << endl; // 40 >> 확인
	cout << *(--iter) << endl; // 30 >> 확인

	TemplateCList<int> b;
	b.pushFront(100);
	cout << "Array 1" << endl;
	for (iter = a.begin(); iter != a.end(); ++iter) {
		cout << *iter << endl;
	}
	cout << "Array 2" << endl;
	for (iter = b.begin(); iter != b.end(); ++iter) {
		cout << *iter << endl;
	}
	TemplateCList<int> c = a; // 깊은 복사 출력(복사 생성자)
	c = b; // 깊은 복사 출력(복사 연산자)

	arr i(5);
	arr q(10);
	arr w = i; // 복사 생성자
	arr p = std::move(w); // 이동 생성자
	w = q; // 대입(복사) 연산자
	arr m(100);
	CopyDeep(m, q); // 대입(복사) 연산자 호출
	CopyShallow(i, q); // 이동 대입 연산자 호출
	return 0;
}