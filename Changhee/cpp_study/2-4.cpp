#include <iostream>
#include <list>
#include <crtdbg.h>


using std::list;
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

private:
	int*	m_pData;
	int		m_iSize;
	int		m_iCur;

public:
	void push_back(int _data)
	{
		if (m_iSize == m_iCur)
		{
			// �迭 ���Ҵ�
			int* newData = new int[m_iSize * 2];

			for (int i = 0; i < m_iSize; ++i)
			{
				newData[i] = m_pData[i];
			}

			delete m_pData;
			m_pData = newData;
		}

		m_pData[m_iCur++] = _data;
	}

	int size()
	{
		return m_iCur;
	}

	int& operator[](int _index)
	{
		return m_pData[_index];
	}


public:
	myArray()
		: m_iSize(5)
		, m_pData(nullptr)
		, m_iCur(0)
	{
		cout << "�⺻ ������ ȣ��" << endl;
	}

	myArray(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
		, m_iCur(0)
	{
		cout << "�⺻ ������(int) ȣ��" << endl;
		m_pData = new int[m_iSize];
	}

	// ���� ������
	myArray(const myArray& _Other)
	{
		cout << "���� ������ ȣ��" << endl;

		m_iSize = _Other.m_iSize;
		m_iCur = _Other.m_iCur;
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
		m_iCur = _Other.m_iCur;
		m_pData = _Other.m_pData;


		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;
		_Other.m_iCur = 0;
	}


	// ���� ������
	myArray& operator= (const myArray& _Other)
	{
		cout << "���Կ����� ȣ��" << endl;

		if (nullptr != m_pData)
			delete[] m_pData;

		m_iSize = _Other.m_iSize;
		m_iCur = _Other.m_iCur;
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
		m_iCur = _Other.m_iCur;
		m_pData = _Other.m_pData;

		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;
		_Other.m_iCur = 0;

		return *this;
	}


	~myArray()
	{
		delete[] m_pData;
	}
};


int main() {


	// �޸� leak Ȯ�� -> leak ����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	myArray mArr(5);

	mArr.push_back(1);
	mArr.push_back(2);
	mArr.push_back(3);


	cout << "\nmArr1 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;

	// =======================
	// ���� ������ ȣ��(���� ����)
	// =======================

	// ����� ���ÿ� �Ҵ��ϱ� ������ ����ȭ�Ǿ� ������ -> ���Կ����ڰ� �ƴ϶� ���� �����ڰ� ȣ��ȴ�.

	cout << "----------------------------------\n";
	cout << "���� �����ڸ� �̿��� mArr2�� ����\n";

	myArray mArr2 = mArr;
	// myArray mArr2(mArr);


	cout << "\nmArr1 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr2 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;



	// ���� ���� Ȯ��

	cout << "----------------------------------\n";

	cout << "mArr2�� �� ����\n";
	mArr2[0] = 10;

	cout << "\nmArr1 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr2 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	// ��������ڸ� ���� ������ ���� ���縦 �Ͽ��� ������ mArr2�� ���� �����Ͽ��� mArr1�� ���� ������ ����


	// ==============
	// �̵� ������ ȣ��
	// ==============

	cout << "----------------------------------\n";
	cout << "�̵������� ȣ�� mArr1 -> mArr_move\n";

	myArray mArr_move(std::move(mArr));

	cout << "\nmArr1 ��� : ";
	for (int i = 0; i < mArr.size(); ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr_move ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr_move[i] << " ";
	}
	std::cout << std::endl;

	cout << "----------------------------------\n";
	cout << "���Կ����� mArr2 -> mArrCopy\n";
	
	myArray mArrCopy;
	mArrCopy = mArr2;


	cout << "\nmArr2 ��� : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr_Copy ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArrCopy[i] << " ";
	}
	std::cout << std::endl;


	cout << "mArrCopy�� �� ����\n";
	mArrCopy[0] = 100;

	cout << "\nmArr2 ��� : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	cout << "\nmArr_Copy ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArrCopy[i] << " ";
	}
	std::cout << std::endl;

	// ���� �����ڰ� �� �����Ǿ� mArr_Copy�� ���� �����Ͽ��� mArr2�� ���� ������� �ʴ´�.
	cout << "----------------------------------\n";
	cout << "�̵� ���Կ����� mArr2 -> mArr3\n";

	myArray mArr3;
	mArr3 = std::move(mArr2);

	cout << "\nmArr2 ��� : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	cout << "\nmArr3 ��� : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr3[i] << " ";
	}
	std::cout << std::endl;



	return 0;
}