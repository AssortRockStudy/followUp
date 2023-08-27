#pragma once


#pragma once
#include <assert.h>
#include <iostream>;

using namespace std;


template <typename T>
struct ttNode {
	T iData;
	ttNode<T>* pNext;
	ttNode<T>* pPrev;

public:
	ttNode<T>()
		:iData(nullptr), pNext(nullptr), pPrev(nullptr) {}

	//pushback�� const T&���ϸ� ���ʵ� const T&�� ������Ѵ�.
	ttNode<T>(const T& _data, ttNode<T>* _pNext = nullptr, ttNode<T>* _pPrev = nullptr)
		:iData(_data),		pNext(_pNext),		pPrev(_pPrev) {}
};


template <typename T>
class TCList {

private:
	ttNode<T>* pHead;
	ttNode<T>* pTail;
	int iCount;



public:
	class iterator;
	void pushback(const T& _data);
	void pushfront(const T& _data);
	iterator begin() { return iterator(this, pHead); }
	iterator end() { return iterator(this, nullptr); }



	//���� ����~
	void CopyShallow(const TCList& _other) {
		pHead = _other.pHead;
		pTail = _other.pTail;
		iCount = _other.iCount;
	}

	//��������
	void CopyDeep(TCList& _other) {
		pHead = nullptr;
		pTail = nullptr;
		iCount = 0;

		iterator it = _other.begin();

		for (; _other.end() != it; ++it)
		{
			this->pushback(*it);
		}
	}

	//���������
	TCList(const TCList& _other)
		:pHead(nullptr), pTail(nullptr), iCount(0) {

		ttNode<T>* curnode = _other.pHead;

		while (curnode)
		{
			this->pushback(curnode->iData);
			curnode = curnode->pNext;
		}

		cout << "��������� ȣ��" << endl;
	}

	//�̵�������
	TCList(TCList&& _other)
		:pHead(_other.pHead), pTail(_other.pTail), iCount(_other.iCount) {


		_other.iCount = 0;
		_other.pHead = nullptr;
		_other.pTail = nullptr;

		cout << "�̵������� ȣ��" << endl;
	}

	//���� ������
	TCList& operator = (const TCList& _other) {
		pHead = nullptr;
		pTail = nullptr;
		iCount = 0;

		ttNode<T>* curnode =_other.pHead;

		while (curnode)
		{
			this->pushback(curnode->iData);
			curnode=curnode->pNext;
		}
		cout << "���� ������ ȣ��" << endl;
		return *this;
	}


	//�̵� ���Կ�����
	TCList& operator = (TCList&& _other) {
		pHead = _other.pHead;
		pTail = _other.pTail;
		iCount = _other.iCount;


		_other.pHead = nullptr;
		_other.pTail = nullptr;
		_other.iCount = 0;
		cout << "�̵� ���Կ����� ȣ��" << endl;

		return *this;
	}


	//swap ����
	void swap(TCList&& _other) {
		TCList tmpcl = std::move(*this);
		*this = _other;
		_other = std::move(tmpcl);
		cout << "swap ȣ��" << endl;
	}

	T& front() { return pHead->iData; };
	T& back() { return pTail->iData; };


	void pop_fornt()
	{
		assert(pHead);
		ttNode<T>* pNext = pHead->pNext;
		delete pHead;
		pHead = pNext;
		pHead->pPrev = nullptr;
		--iCount;
	}

	void pop_back()
	{
		assert(pTail);
		ttNode<T>* pPrev = pTail->pPrev;
		delete pTail;
		pTail = pPrev;
		pTail->pNext = nullptr;
		--iCount;
	}

	//////////////////////230821 0417����///////////////////////////
	iterator erase(iterator& it) {
		ttNode<T>* tmpnode = it.pTarget;
		ttNode<T>* prevnode = tmpnode->pPrev;
		ttNode<T>* nextnode = tmpnode->pNext;

		it.pTarget = nextnode;
		if (prevnode) {
			prevnode->pNext = nextnode;
		}
		else {
			pHead = nextnode;
		}
		if (nextnode) { nextnode->pPrev = prevnode; }
		else { pTail = nullptr; }


		delete tmpnode;
		--iCount;
		return it;
	}
	//////////////////////230821 0417����///////////////////////////

	TCList()
		:pHead(nullptr), pTail(nullptr), iCount(0) {}
	~TCList();


	class iterator {
	private:
		TCList* pOwner;
		ttNode<T>* pTarget;

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

		//������ ������ �����ؾ��Ѵ�.
		T& operator *() { return pTarget->iData; }


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
			:pOwner(nullptr), pTarget(nullptr) {}
		iterator(TCList<T>* _pOwner, ttNode<T>* _pTarget)
			:pOwner(_pOwner), pTarget(_pTarget) {}

		~iterator() {}



		friend class TCList;
	};

};


template <typename T>
void TCList<T>::pushfront(const T& _data)
{
	ttNode<T>* newnode = new ttNode<T>(_data);


	if (0 == iCount)
	{
		//�����Ͱ� �ϳ��� �������
		pHead = pTail = newnode;
	}
	else
	{
		newnode->pNext = pHead;
		pHead->pPrev = newnode;
		pHead = newnode;
	}
	++iCount;
}


template <typename T>
void TCList<T>::pushback(const T& _data)
{
	ttNode<T>* newnode = new ttNode<T>(_data);


	if (0 == iCount)
	{
		//�����Ͱ� �ϳ��� �������
		pHead = pTail = newnode;
	}
	else
	{
		pTail->pNext = newnode;
		newnode->pPrev = pTail;
		pTail = newnode;
	}

	++iCount;
}




template <typename T>
TCList<T>::~TCList() {
	ttNode<T>* curnode = pHead;

	while (curnode) {
		ttNode<T>* tmpnode = curnode->pNext;
		delete curnode;
		curnode = tmpnode;
	}

	pHead = nullptr;
	pTail = nullptr;
	iCount = 0;
}