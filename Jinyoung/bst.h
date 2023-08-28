#pragma once

//������ ����
//����,����,���� Ž�����, ���� ���
//������ �˻�
//������ ����
//make_pair�Լ� ����?

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
		//root�ϰ�� Ptr[PARENT]->Ptr[LCHILD] �����ϸ�ȵ�.
		if (this->IsRoot()) return false;
		return this == Ptr[PARENT]->Ptr[LCHILD] ; 
	}
	bool IsRChild() 
	{
		//root�ϰ�� Ptr[PARENT]->Ptr[LCHILD] �����ϸ�ȵ�.
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
		//m_Root �� nullptr �̸� (�����Ͱ� 1���� �Է��� �ȵ� ��Ȳ) end iterator ���ش�.
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
		//m_Root �� nullptr �̸� (�����Ͱ� 1���� �Է��� �ȵ� ��Ȳ) end iterator ���ش�.
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

		//�����Ͱ� ������.
		if (0 == m_Count)
		{
			m_Root = newnode;
			++m_Count;
			return;
		}

		//�����Ͱ� �ϳ��̻�������.
		//1.root������ ����.
		//2.�������� first�������ؼ�
		//   2-1������ left ũ�� right �� �̵��Ѵ�
		//		ó��)curnode�� first���� _data�� first���� ���Ѵ�. 
		//			 pnode�� curnode�� ����,
		//			 ������ curnode�� curnode�� LCHILD ����
		//			 ũ�� cudenode�� curnode�� RCHILD ����
		//			 ������ cudenode�� nullptr���� ,first_eqƮ���� ture
		//3.�ݺ����� �ݺ������� curnode�� nullptr�� �ƴѰ�� ����
		// 
		//4. �ݺ���������ó��  
		//   4-1)pnode.ptr[target]�� newnode ����
		//	 4-2)newnode.ptr[PARENT]�� pnode ����
		//	
		//   ������ second ���� ���������.

		BSTNode<T1, T2>* pnode = m_Root;
		BSTNode<T1, T2>* curnode = m_Root;
		//�̹� ���� first���� ������� ���.
		bool first_eq = false;

		NODE_TYPE targetrl;

		do {
			pnode = curnode;

			//�����Ͱ� �����庸�� ũ��
			if (_data.first > curnode->data.first) { targetrl = RCHILD; }
			//������
			else if (_data.first < curnode->data.first) { targetrl = LCHILD; }
			//������
			else if (_data.first == curnode->data.first) { curnode = nullptr; first_eq = true; break; }

			curnode = curnode->Ptr[targetrl];

		} while (curnode);

		//�����Ͱ� ���� �������
		if (!first_eq)
		{
			pnode->Ptr[targetrl] = newnode;
			newnode->Ptr[PARENT] = pnode;
			++m_Count;
		}
		//�����Ͱ� �������
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
			//���� �ļ��ڸ� ã�Ƽ� ����Ų��.
			BSTNode<T1, T2>* curnode = m_Target;


			//��Ģ1. 
			//���� �ڽ��� �ִٸ�, �����ڽ��� ����Ų��.
			if (curnode->HasLChild())
			{
				curnode = curnode->Ptr[LCHILD];
			}
			//�����ڽ��� ����,�������ڽ��� �ִٸ�,�������ڽ��� ����Ų��.
			else if (curnode->HasRChild())
			{
				curnode = curnode->Ptr[RCHILD];
			}
			//��Ģ2.
			//������ �ڽ��� ���ٸ�,���� �θ��� ���� �ڽ��϶����� �ö󰣴�.
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

			//���� �ļ��ڸ� ã�Ƽ� ����Ų��.
			// 
			// ��Ģ
			// 1. �������ڽ��� �ִٸ�, ���������ΰ��� �����ڽ��� ������ ���� �������� ��������
			// 
			// 2. ������ �ڽ��� ���ٸ� , ���� �θ��� �����ڽ��϶����� �ö󰣴�.
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
			//R���ϵ�Ȥ�� ������� ����.
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
			//null == target ���� ȣ���Ѱ�� ������ ���ڸ� ã���ִ� �Լ�.
			if (!m_Target)
			{
				return last();
			}

			//���� �����ڸ� ã�Ƽ� ����Ų��.
			// 
			// ��Ģ
			// 1. �����ڽ��� �ִٸ�, �������ΰ��� �������ڽ��� ������ ���� ���������� ��������
			// 
			// 2. ���� �ڽ��� ���ٸ� , ���� �θ��� �������ڽ��϶����� �ö󰣴�.

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
	//����Լ� ����
	//DeletNode(m_Root);
	//m_Count =0;

	//�ݺ�������
	//��� ��带
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
	//����Լ� ����
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