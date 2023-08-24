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

	Pair()
		:first(nullptr), second(nullptr) {}
	Pair(const T1& _first,const T2& _second)
		:first(_first), second(_second) {}

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
};



template <typename T1, typename T2>
class CBST
{
private:
	BSTNode<T1, T2>* m_Root;
	int m_Count;


public:
	CBST()
		:m_Root(nullptr),m_Count(0){}


	CBST(const Pair<T1, T2>& _data)
		:m_Root(nullptr), m_Count(0)
	{
		pushdata(_data);
	}

	void pushdata(const Pair<T1, T2>& _data)
	{
		BSTNode<T1, T2>* newnode = new BSTNode< T1, T2 >(_data);

		//�����Ͱ� ������.
		if(0==m_Count)
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

		NODE_TYPE targetrl ;

		do {
			pnode = curnode;

		//�����Ͱ� �����庸�� ũ��
			if (_data.first > curnode->data.first) { targetrl = RCHILD; }
		//������
		else if(_data.first < curnode->data.first) { targetrl = LCHILD; }
		//������
		else if (_data.first == curnode->data.first) { curnode = nullptr; first_eq = true; break; }

		curnode = curnode->Ptr[targetrl];

		} while (curnode);
		
		//�����Ͱ� ���� �������
		if(!first_eq)
		{
			pnode->Ptr[targetrl] = newnode;
			newnode->Ptr[PARENT] = pnode;
			++m_Count;
		}
		//�����Ͱ� �������
		else
		{
			pnode->data.second = _data.second;
		}

	}

};

