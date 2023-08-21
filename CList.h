#pragma once



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
			pTarget = pTarget->pNext;
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