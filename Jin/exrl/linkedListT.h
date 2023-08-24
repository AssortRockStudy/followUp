#pragma once
#include <iostream>

using std::cout;
using std::endl;
template <typename T>
struct Node
{
	T		data;
	Node*	prev;
	Node*	next;

	Node()
		: data(0)
		, prev(nullptr)
		, next(nullptr) {}
	Node(T _data, Node* _prev = nullptr, Node* _next = nullptr)
		: data(_data)
		, prev(_prev)
		, next(_next) {}
};

template <typename T>
class List
{
private:
	int		mCount;
	Node<T>*	mHead;
	Node<T>*	mTail;
public:
	List()
		: mCount(0)
		, mHead(nullptr)
		, mTail(nullptr) {}

	List(int _mCount, Node<T>* _mHead, Node<T>* _mTail)
		: mCount(_mCount)
		, mHead(_mHead)
		, mTail(_mTail) {}

	~List()
	{
		Node<T>* dNode = mHead;
		for (int i = 0; i < mCount; ++i)
		{
			Node<T>* nextDNode = dNode->next;
			delete dNode;
			dNode = nextDNode;
		}
	}

	List(const List<T>& _other) // 복사 생성자
		: mCount(0)
		, mHead(nullptr)
		, mTail(nullptr)
	{

		Node<T>* targetNode = _other.mHead;
		for (int i = 0; i < _other.mCount; ++i)
		{
			pushBack(targetNode->data);
			targetNode = targetNode->next;
		}
	}

	List(List<T>&& _other) // 이동 생성자
		: mCount(_other.mCount)
		, mHead(_other.mHead)
		, mTail(_other.mTail)
	{
		_other.mCount = 0;
		_other.mHead = nullptr;
		_other.mTail = nullptr;
	}

	void pushBack(T _data)
	{
		Node<T>* newNode = new Node<T>(_data);
		if (mHead == nullptr)
		{
			mHead = mTail = newNode;
		}
		else
		{
			mTail->next = newNode;
			newNode->prev = mTail;
			mTail = newNode;
		}
		++mCount;
	}

	void pushFront(T _data)
	{
		Node<T>* newNode = new Node<T>(_data);
		if (mHead == nullptr)
		{
			mHead = mTail = newNode;
		}
		else
		{
			mHead->prev = newNode;
			newNode->next = mHead;
			mHead = newNode;
		}
		++mCount;
	}

	List<T>& operator =(const List<T>& _other) // 대입 복사
	{
		// 지금 가리키고 있는 것 지우기
		// 데이터 넣기	
		cout << " = operator call!" << endl;
		Node<T>* targetNode = mHead;
		if (nullptr != mHead)
		{
			for (int i = 0; i < _other.mCount; ++i)
			{
				Node<T>* nextTargetNode = targetNode->next;
				delete targetNode;
				targetNode = nextTargetNode;
			}
		}
		this->mCount = 0;
		mHead = nullptr;
		mTail = nullptr;

		targetNode = _other.mHead;
		for (int i = 0; i < _other.mCount; ++i)
		{
			pushBack(targetNode->data);
			targetNode = targetNode->next;
		}
		return *this;
	}

	List<T>& operator =(List&& _other) // 대입 이동
	{
		Node<T>* targetNode = mHead;
		if (nullptr != mHead)
		{
			for (int i = 0; i < _other.mCount; ++i)
			{
				Node<T>* nextTargetNode = targetNode->next;
				delete targetNode;
				targetNode = nextTargetNode;
			}
		}
			mCount = _other.mCount;
			mHead = _other.mHead;
			mTail = _other.mTail;

			_other.mCount = 0;
			_other.mHead = nullptr;
			_other.mTail = nullptr;

			return *this;
	}

	class iterator
	{
	private :
		List<T>*	mOwnerList;
		Node<T>*	mTargetNode;
	
	public:
		iterator()
			: mOwnerList(nullptr)
			, mTargetNode(nullptr) {}

		iterator(List<T>* _ownerList, Node<T>* _targetNode)
			: mOwnerList(_ownerList)
			, mTargetNode(_targetNode) {}

		~iterator() {};

		iterator begin()
		{
			return(this, mHead);
		}

		iterator end()
		{
			return(this, nullptr);
		}

		bool operator == (iterator& _other)
		{
			if (mOwnerList == _other.mOwnerList && mTargetNode == _other.mTargetNode)
				return true;
			return false;
		}

		bool operator != (iterator& _other)
		{
			if (mOwnerList == _other.mOwnerList && mTargetNode == _other.mTargetNode)
				return false;
			return true;
		}

		T operator *()
		{
			if (nullptr == mTargetNode)
			{
				// 경고다..
			}
			return mTargetNode->data;
		}

		iterator& operator ++()
		{
			if (nullptr == mTargetNode)
			{
				// 경고,...
			}
			else
			{
				mTargetNode = mTargetNode->next;
			}
			return *this;
		}

		iterator operator ++(int)
		{
			iterator copyiter(*this);
			++(*this);
			return copyiter;
		}

		iterator& operator --()
		{
			if (nullptr != mTargetNode)
			{
				// 경고,,
			}
			else
			{
				mTargetNode = mTargetNode->prev;
			}
			return *this;
		}

		iterator operator --(int)
		{
			iterator copyiter(*this);
			--(*this);
			return copyiter;
		}

		iterator erase(iterator& iter)
		{
			if (iter.mTargetNode != mHead)
			{
				iter.mTargetNode->prev->next = iter.mTargetNode->next;
			}
			else
			{
				mHead = iter.mTargetNode->next;
			}
			if (iter.mTargetNode != mTail)
			{
				iter.mTargetNode->next->prev = iter.mTargetNode->prev;
			}
			else
			{
				mTail = iter.mTargetNode->prev;
			}
			iterator nextiter(this, iter.TargetNode->next);
			--mCount;
			delete iter.mTargetNode;
			return nextiter;
		}
	};

};