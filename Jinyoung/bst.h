﻿#pragma once

//데이터 삽입
//전위,중위,후위 탐색출력, 깊이 출력
//데이터 검색
//데이터 삭제
//make_pair함수 구현?

enum NODE_TYPE
{
	PARENT,
	LCHILD,
	RCHILD,
};


template <typename T1, typename T2>
struct Pair
{
	T1 first;
	T2 second;


};





template <typename T1, typename T2>
struct BSTNode
{
	Pair<T1, T2> data;
	BSTNode<T1, T2>* Ptr[3];

	BSTNode()
		:data(nullptr), Ptr({ nullptr, nullptr, nullptr }) {};

	BSTNode(const Pair<T1, T2>& _data,
		BSTNode<T1, T2>* pparent = nullptr,
		BSTNode<T1, T2>* plchild = nullptr,
		BSTNode<T1, T2>* prchild = nullptr)
		:data(_data), Ptr{ pparent ,plchild ,prchild } {};

public:
	bool HasLChild() { return Ptr[LCHILD]; }
	bool HasRChild() { return Ptr[RCHILD]; }
	bool IsRoot() { return !(Ptr[PARENT]); }

	bool IsLChild() 
	{
		//root일경우 Ptr[PARENT]->Ptr[LCHILD] 연산하면안됨.
		if (this->IsRoot()) return false;
		return this == Ptr[PARENT]->Ptr[LCHILD] ; 
	}
	bool IsRChild() 
	{
		//root일경우 Ptr[PARENT]->Ptr[LCHILD] 연산하면안됨.
		if (this->IsRoot()) return false;
		return this == Ptr[PARENT]->Ptr[RCHILD] ; 
	}


};



template <typename T1, typename T2>
class CBST
{
private:
	BSTNode<T1, T2>* m_Root;
	int m_Count;
	void DeletNode(BSTNode<T1, T2>* pbst);


public:
	CBST()
		:m_Root(nullptr), m_Count(0) {}

	void clear();
	void clear_r();
	class iterator;

	iterator begin()
	{
		//m_Root 가 nullptr 이면 (데이터가 1개도 입력이 안된 상황) end iterator 를준다.
		if (!m_Root) { return end(); }

		BSTNode<T1, T2>* node = m_Root;
		while (node->Ptr[LCHILD])
		{
			node = node->Ptr[LCHILD];
		}
		return iterator(this, node);
	}

	iterator root()
	{
		//m_Root 가 nullptr 이면 (데이터가 1개도 입력이 안된 상황) end iterator 를준다.
		if (!m_Root) { return end(); }

		return iterator(this, m_Root);
	}

	iterator end()
	{
		return iterator(this, nullptr);
	}

	int depth()
	{
		int tmpdepth = 0;
		int depth = 0;
		if (nullptr == m_Root) { return depth; }

		BSTNode<T1, T2>* curnode = root().m_Target;


		while (curnode)
		{
			if (curnode->HasRChild())
			{
				curnode = curnode->Ptr[RCHILD];
				++tmpdepth;
				depth = (tmpdepth > depth) ? tmpdepth : depth;
			}

			else
			{

				while (curnode->IsRChild())
				{

					curnode = curnode->Ptr[PARENT];
					--tmpdepth;
					if (curnode->Ptr[PARENT]->IsRoot() && curnode->IsRChild())
					{
						curnode = nullptr;
						break;
					}
				}
				if (curnode) { curnode = curnode->Ptr[PARENT]->Ptr[RCHILD]; }

			}
			
		}
		return depth;

	}



	CBST(const Pair<T1, T2>& _data)
		:m_Root(nullptr), m_Count(0)
	{
		pushdata(_data);
	}


	void pushdata(const Pair<T1, T2>& _data)
	{
		BSTNode<T1, T2>* newnode = new BSTNode< T1, T2 >(_data);

		//데이터가 없을때.
		if (0 == m_Count)
		{
			m_Root = newnode;
			++m_Count;
			return;
		}

		//데이터가 하나이상있을때.
		//1.root노드부터 시작.
		//2.현재노드의 first값을비교해서
		//   2-1작으면 left 크면 right 로 이동한다
		//		처리)curnode의 first값과 _data의 first값을 비교한다. 
		//			 pnode에 curnode를 저장,
		//			 작으면 curnode에 curnode의 LCHILD 대입
		//			 크면 cudenode에 curnode의 RCHILD 대입
		//			 같으면 cudenode에 nullptr대입 ,first_eq트리거 ture
		//3.반복문의 반복조건은 curnode가 nullptr가 아닌경우 까지
		// 
		//4. 반복문끝난후처리  
		//   4-1)pnode.ptr[target]에 newnode 대입
		//	 4-2)newnode.ptr[PARENT]에 pnode 대입
		//	
		//   같으면 second 값을 덮어쓰고종료.

		BSTNode<T1, T2>* pnode = m_Root;
		BSTNode<T1, T2>* curnode = m_Root;
		//이미 같은 first값이 들어있을 경우.
		bool first_eq = false;

		NODE_TYPE targetrl;

		do {
			pnode = curnode;

			//데이터가 현재노드보다 크면
			if (_data.first > curnode->data.first) { targetrl = RCHILD; }
			//작으면
			else if (_data.first < curnode->data.first) { targetrl = LCHILD; }
			//같으면
			else if (_data.first == curnode->data.first) { curnode = nullptr; first_eq = true; break; }

			curnode = curnode->Ptr[targetrl];

		} while (curnode);

		//데이터가 같지 않은경우
		if (!first_eq)
		{
			pnode->Ptr[targetrl] = newnode;
			newnode->Ptr[PARENT] = pnode;
			++m_Count;
		}
		//데이터가 같은경우
		//do nothing
		/*else
		{
			pnode->data.second = _data.second;
		}*/

	}



public:


	class iterator
	{
	private:
		CBST<T1, T2>* m_pOwner;
		BSTNode<T1, T2>* m_Target;


	public:
		Pair<T1, T2>& operator * ()
		{
			return m_Target->data;
		}

		Pair<T1, T2>* operator -> ()
		{
			return &m_Target->data;
		}
		


		iterator()
			: m_pOwner(nullptr)
			, m_Target(nullptr)
		{}

		iterator(CBST<T1, T2>* _Owner, BSTNode<T1, T2>* _Target)
			: m_pOwner(_Owner)
			, m_Target(_Target)
		{}

		~iterator()
		{}

		bool operator ==(const iterator& _other)
		{
			return m_pOwner == _other.m_pOwner && m_Target == _other.m_Target;
		}

		bool operator !=(const iterator& _other)
		{
			return !((*this) == _other);
		}

		iterator& prepp()
		{
			assert(m_Target);
			//전위 후속자를 찾아서 가리킨다.
			BSTNode<T1, T2>* curnode = m_Target;


			//규칙1. 
			//왼쪽 자식이 있다면, 왼쪽자식을 가리킨다.
			if (curnode->HasLChild())
			{
				curnode = curnode->Ptr[LCHILD];
			}
			//왼쪽자식이 없고,오른쪽자식이 있다면,오른쪽자식을 가리킨다.
			else if (curnode->HasRChild())
			{
				curnode = curnode->Ptr[RCHILD];
			}
			//규칙2.
			//오른쪽 자식이 없다면,내가 부모의 왼쪽 자식일때까지 올라간다.
			//
			else
			{

				while (curnode->IsRChild())
				{

					curnode = curnode->Ptr[PARENT];
					if (curnode->Ptr[PARENT]->IsRoot() && curnode->IsRChild())
					{
						curnode = nullptr;
						break;
					}
				}
				if (curnode) { curnode = curnode->Ptr[PARENT]->Ptr[RCHILD]; }

			}
			m_Target = curnode;
			return *this;
		}


		iterator& operator ++()
		{
			assert(m_Target);

			//중위 후속자를 찾아서 가리킨다.
			// 
			// 규칙
			// 1. 오른쪽자식이 있다면, 오른쪽으로가서 왼쪽자식이 없을때 까지 왼쪽으로 내려간다
			// 
			// 2. 오른쪽 자식이 없다면 , 내가 부모의 왼쪽자식일때까지 올라간다.
			//



			BSTNode<T1, T2>* curnode = m_Target;


			if (curnode->HasRChild())
			{
				curnode = curnode->Ptr[RCHILD];
				while (curnode->HasLChild()) {
					curnode = curnode->Ptr[LCHILD];
				}
			}
			else
			{
				while (curnode->IsRChild())
				{
					if (curnode->IsRoot())
					{
						curnode = nullptr;
						break;
					}
					curnode = curnode->Ptr[PARENT];
				}
				curnode = curnode->Ptr[PARENT];
			}


			m_Target = curnode;
			return *this;
		}



		

		iterator& operator++(int)
		{
			iterator copyiter = *this;
			++(*this);
			return copyiter;
		}


		iterator& last()
		{
			BSTNode<T1, T2>* curnode = m_Root;
			//R차일드혹은 없을경우 중지.
			while (curnode->HasRChild)
			{
				curnode = curnode[RCHILD];
			}
			m_Target = curnode;
			return *this;
		}

		iterator& operator--()
		{
			assert(m_pOwner);
			assert(m_pOwner->m_Root);
			//null == target 에서 호출한경우 마지막 인자를 찾아주는 함수.
			if (!m_Target)
			{
				return last();
			}

			//중위 선행자를 찾아서 가리킨다.
			// 
			// 규칙
			// 1. 왼쪽자식이 있다면, 왼쪽으로가서 오른쪽자식이 없을때 까지 오른쪽으로 내려간다
			// 
			// 2. 왼쪽 자식이 없다면 , 내가 부모의 오른쪽자식일때까지 올라간다.

			BSTNode<T1, T2>* curnode = m_Target;

			if (curnode->HasLChild())
			{
				curnode = curnode->Ptr[LCHILD];
				while (curnode->HasRChild()) {
					curnode = curnode->Ptr[RCHILD];
				}
			}
			else
			{
				while (curnode->IsLChild())
				{
					if (curnode->IsRoot())
					{
						curnode = nullptr;
						break;
					}
					curnode = curnode->Ptr[PARENT];
				}
				curnode = curnode->Ptr[PARENT];
			}
			m_Target = curnode;
			return *this;
		}
		iterator& operator--(int)
		{
			iterator copyiter = *this;
			--(*this);
			return copyiter;
		}
		friend class CBST;
	};

};


template <typename T1, typename T2>
void CBST<T1, T2>::clear()
{
	//재귀함수 버전
	//DeletNode(m_Root);
	//m_Count =0;

	//반복문버전
	//모든 노드를
	TCList<BSTNode<T1, T2>* > temp;

	if (m_Root) {
		temp.push_back(m_Root);
	}


	while (0 != temp.size())
	{
		BSTNode<T1, T2>* pNode = temp.front();
		temp.pop_front();

		if (pNode->Ptr[LCHILD])
		{
			temp.pushback(pNode->Ptr[LCHILD]);
		}
		if (pNode->Ptr[RCHILD])
		{
			temp.pushback(pNode->Ptr[RCHILD]);
		}

		delete pNode;
	}

	m_Count = 0;
	m_Root = nullptr;

}


template <typename T1, typename T2>
void CBST<T1, T2>::clear_r() 
{
	//재귀함수 버전
	DeletNode(m_Root);
	m_Count =0;
	m_Root = nullptr;
}


template <typename T1, typename T2>
void CBST<T1, T2>::DeletNode(BSTNode<T1, T2>* pbst) {

	if (pbst->Ptr[LCHILD]) {
		DeletNode(pbst->Ptr[LCHILD]);
	}
	BSTNode<T1, T2>* rptr = pbst->Ptr[RCHILD];
	delete pbst;

	if (rptr) {
		DeletNode(rptr);
	}

}



template<typename T1, typename T2>
Pair<T1, T2> Create_Pair(const T1& _first, const T2& _second)
{
	Pair<T1, T2> data;
	data.first = _first;
	data.second = _second;
	return data;
}