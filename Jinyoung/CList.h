#pragma once
#include <assert.h>
#include <iostream>;

using namespace std;



struct tNode {
	int iData;
	tNode* pNext;
	tNode* pPrev;

	tNode()
		:iData(0), pNext(nullptr), pPrev(nullptr){}

	tNode(int _data, tNode* _pNext = nullptr, tNode* _pPrev = nullptr)
		:iData(_data), pNext(_pNext), pPrev(_pPrev){}
};



class CList {

private:
	class iterator;
	tNode* pHead;
	tNode* pTail;
	int iCount;



public:
	void pushback(int _data);
	void pushfront(int _data);
	iterator begin() { return iterator(this, pHead); }
	iterator end() { return iterator(this, nullptr); }



	//얕은 복사
	void CopyShallow(CList& _other) {
		pHead = _other.pHead;
		pTail = _other.pTail;
		iCount = _other.iCount;
	}

	//깊은복사
	void CopyDeep(CList& _other) {
		pHead = nullptr;
		pTail = nullptr;
		iCount = 0;

		iterator it = _other.begin();

		for (;  _other.end()!= it ; ++it)
		{
			this->pushback(*it);
		}
	}

	/*

	//복사생성자
	CList(CList& _other)
		:pHead(nullptr), pTail(nullptr), iCount(0) {
		
		iterator it = _other.begin();

		for (; _other.end() != it; ++it)
		{
			this->pushback(*it);
		}

		cout << "복사생성자 호출" << endl;
	}
	*/

	//이동생성자
	CList(CList&& _other)
		:pHead(_other.pHead), pTail(_other.pTail), iCount(_other.iCount) {
				

		_other.iCount = 0;
		_other.pHead = nullptr;
		_other.pTail = nullptr;

		cout << "이동생성자 호출" << endl;
	}

	//대입 연산자
	CList& operator = (CList& _other) {
		pHead = nullptr;
		pTail = nullptr;
		iCount = 0;

		iterator it = _other.begin();

		for (; _other.end() != it; ++it)
		{
			this->pushback(*it);
		}
		cout << "대입 연산자 호출" << endl;
		return *this;
	}


	//이동 대입연산자
	CList& operator = (CList&& _other) {
		pHead = _other.pHead;
		pTail = _other.pTail;
		iCount = _other.iCount;


		_other.pHead=nullptr;
		_other.pTail= nullptr;
		_other.iCount= 0;
		cout << "이동 대입연산자 호출" << endl;

		return *this;
	}


	//swap 구현
	void swap(CList&& _other) {
		CList tmpcl = std::move(*this);
		*this = _other;
		_other = std::move(tmpcl);
		cout << "swap 호출" << endl;
	}



	//////////////////////230821 0417수정///////////////////////////
	iterator erase(iterator& it) {
		tNode* tmpnode = it.pTarget;
		tNode* prevnode = tmpnode->pPrev;
		tNode* nextnode = tmpnode->pNext;

		it.pTarget = nextnode;
		if (prevnode) {
			prevnode->pNext = nextnode;	
		}
		else {
			pHead = nextnode;
		}
		if (nextnode) { nextnode->pPrev = prevnode;  }else{ pTail = nullptr; }
		

		delete tmpnode;
		--iCount;
		return it;
	}
	//////////////////////230821 0417수정///////////////////////////

	CList()
		:pHead(nullptr), pTail(nullptr), iCount(0)	{}
	~CList();



	class iterator {
	private:
		CList* pOwner;
		tNode* pTarget;

	public:

		bool operator ==(iterator& _other) {
			if (pOwner == _other.pOwner 
				&& pTarget == _other.pTarget) {
				return true;
			}
			else { return false; }
		}

		bool operator !=(iterator& _other) {
			if (pOwner == _other.pOwner
				&& pTarget == _other.pTarget) {
				return false;
			}
			else { return true; }
		}

		//원본값 수정도 가능해야한다.
		int& operator *() { return pTarget->iData; }


		iterator& operator ++() {
			if (pTarget) {
				pTarget = pTarget->pNext;
			}
			else { assert(nullptr); }
			return *this;
		}

		iterator operator ++(int) {

			iterator tmpiterator(*this);
			++(*this);
			return tmpiterator;
		}


		iterator& operator --() {
			pTarget = pTarget->pPrev;
			return *this;
		}

		iterator operator --(int) {

			iterator tmpiterator(*this);
			--(*this);
			return tmpiterator;
		}




		iterator()
			:pOwner(nullptr), pTarget(nullptr)	{}
		iterator(CList* _pOwner, tNode* _pTarget)
			:pOwner(_pOwner), pTarget(_pTarget)	{}

		~iterator()	{}



		friend class CList;
	};

};