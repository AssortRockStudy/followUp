#include <iostream>

using std::cout;
using std::endl;


/*
 &�� ������ ������ �� �ִ� l-value �̴�. const ���� ��� �Լ��ȿ����� r-value�� �Ǿ� ������ ������ �� ����.
 &&�� r-value ���������� ������ ������ �� �ִ�. ������ r-value�� ������ �ǹ��̱� ������ �ش� ������ �����Ͽ��� ������ ���� �ʴ´�.(ex. ��� 10�� 20���� �����Ѵٰ� ���� 10�� 20�� ���� �ʴ´�)
 �׷��� &&�� ���� ����ϴ� �ǹ̰� ����  �̵� ���Կ������� Ʈ���� ������ ���ȴ�.

 int && -> a �� ������ ��
 int & -> ���� ���� ����

 const & Ÿ������ ��� Ŀ�� ����
*/

class myArray
{

public:
	int*	m_pData;
	int		m_iSize;

public:
	myArray()
		: m_iSize(0)
		, m_pData(nullptr)
	{
		cout << "�⺻ ������ ȣ��" << endl;
	}

	myArray(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
	{
		cout << "�⺻ ������(int) ȣ��" << endl;
		m_pData = new int[m_iSize];
	}

	// ���� ������
	myArray(const myArray& _Other)
	{
		cout << "���� ������ ȣ��" << endl;

		m_iSize = _Other.m_iSize;
		m_pData = new int[m_iSize];


		for (int i = 0; i < m_iSize; ++i)
		{
			m_pData[i] = _Other.m_pData[i];
		}
	}

	// �̵� ������ -> r-value ������ Ʈ���Ű� �ȴ�.(&&)
	myArray(myArray&& _Other)
	{
		
		cout << "�̵� ������ ȣ��" << endl;

		// �ڽ��� ������ �Ѱ��ְ� ������ ��. �����ֱⰡ ������ �˾Ƽ� ����
		m_iSize = _Other.m_iSize;
		m_pData = _Other.m_pData;

		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;
	}


	// ���� ������
	myArray& operator= (const myArray& _Other)
	{
		cout << "���Կ����� ȣ��" << endl;

		if (nullptr != m_pData)
			delete[] m_pData;

		m_iSize = _Other.m_iSize;
		m_pData = new int[m_iSize];


		for (int i = 0; i < m_iSize; ++i)
		{
			m_pData[i] = _Other.m_pData[i];
		}

		return *this;
	}

	// �̵� ���� ������
	myArray& operator= (myArray&& _Other)
	{
		cout << "�̵� ���Կ����� ȣ��" << endl;

		if (nullptr != m_pData)
			delete[] m_pData;

		m_iSize = _Other.m_iSize;
		m_pData = _Other.m_pData;

		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;

		return *this;
	}


	~myArray()
	{
		delete[] m_pData;
	}
};


int main() {



	return 0;
}