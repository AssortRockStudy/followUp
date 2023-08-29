#include <iostream>

using std::cout;
using std::endl;


class shallow
{

public:
	int*	m_pData;
	int		m_iSize;

public:
	shallow()
		: m_iSize(0)
		, m_pData(nullptr)
	{
	}

	shallow(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
	{
		m_pData = new int[m_iSize];
	}
	
	shallow(const shallow& _Other)
	{
		m_iSize = _Other.m_iSize;
		m_pData = _Other.m_pData;
	}

	//~shallow()
	//{
	//	delete m_pData;
	//}
};


class deep
{

public:
	int*	m_pData;
	int		m_iSize;

public:
	deep()
		: m_iSize(0)
		, m_pData(nullptr)
	{
	}

	deep(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
	{
		m_pData = new int[m_iSize];
	}

	// ���� ���� ����
	deep(const deep& _Other)
	{
		m_iSize = _Other.m_iSize;
		m_pData = new int[m_iSize];

		for (int i = 0; i < m_iSize; ++i)
		{
			m_pData[i] = _Other.m_pData[i];
		}
	}

	~deep()
	{
		delete[] m_pData;
	}
};



int main()
{

	cout << "shallow copy\n\n";

	// shallow ��ü ���� �� �迭 �ȿ� �� �ֱ�
	shallow s1(5);
	s1.m_pData[0] = 1;
	s1.m_pData[1] = 2;
	s1.m_pData[2] = 3;
	s1.m_pData[3] = 4;
	s1.m_pData[4] = 5;

	// �⺻ ���� �����ڸ� �̿��Ͽ� s1�� s2�� ����
	shallow s2(s1);


	// s1, s2 ���
	cout << "shallow s1:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << s1.m_pData[i] << " ";
	}
	cout << endl;

	cout << "shallow s2:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << s2.m_pData[i] << " ";
	}
	cout << endl;

	// s2 ���� ����
	cout << "s2 ����\n\n";
	for (int i = 0; i < 5; ++i)
	{
		s2.m_pData[i] += 5;
	}

	// s1, s2 ���
	cout << "shallow s1:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << s1.m_pData[i] << " ";
	}
	cout << endl;

	cout << "shallow s2:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << s2.m_pData[i] << " ";
	}
	cout << endl;

	/*
	shallow s1 :
	1 2 3 4 5
	shallow s2 :
	1 2 3 4 5
	s2 ����

	shallow s1 :
	6 7 8 9 10
	shallow s2 :
	6 7 8 9 10

	s2�� ���� �ߴµ� s1�� ���� ����� ���� �� �� �ִ�.
	�⺻ ���� �������� ��� �ּ�ó���� ���������ó�� ��ü �ȿ� ��� ������ �״�� �����ϴ� ������� �۵��ϴµ�, 
	���� ��������߿� �����Ҵ�� ��������� �ִٸ� ������ ������ �ִ� ���� �����Ҵ�� �� �޸��� �ּ��̱� ������ ������ ����Ǵ� ���� �ּҰ� �״�� ����ǰ� ���Ӱ� �����Ҵ��ϴ� ���� �ƴϴ�.
	*/


	cout << endl << endl;
	cout << "deep copy\n\n";

	// deep ��ü ���� �� �迭 �ȿ� �� �ֱ�
	deep d1(5);
	d1.m_pData[0] = 1;
	d1.m_pData[1] = 2;
	d1.m_pData[2] = 3;
	d1.m_pData[3] = 4;
	d1.m_pData[4] = 5;

	// ���� ������ ���� �����ڸ� �̿��Ͽ� d1�� d2�� ����
	deep d2(d1);

	// d1, d2 ���
	cout << "deep d1:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << d1.m_pData[i] << " ";
	}
	cout << endl;

	cout << "deep d2:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << d2.m_pData[i] << " ";
	}
	cout << endl;

	// d2 ���� ����
	cout << "d2 ����\n\n";
	for (int i = 0; i < 5; ++i)
	{
		d2.m_pData[i] += 5;
	}

	// d1, d2 ���
	cout << "deep d1:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << d1.m_pData[i] << " ";
	}
	cout << endl;

	cout << "deep s2:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		cout << d2.m_pData[i] << " ";
	}
	cout << endl;
	
	/*
	deep d1:
	1 2 3 4 5
	deep d2:
	1 2 3 4 5
	d2 ����

	deep d1:
	1 2 3 4 5
	deep s2:
	6 7 8 9 10

	���� ������ ��������ڴ� ���ο� �� �޸𸮸� �Ҵ� �ް� �� �ȿ� ������ ���� �����ϱ� ������ �ΰ��� ��ü�� ���� �ٸ� �� �޸𸮸� �Ҵ� �ްԵȴ�. 
	�̷��� �Ǿ��� ��� d2�� �����ϴ��� d2�� �迭�ּҿ� d1�� �迭�ּҰ� �ٸ��� ������ d1�� ���� ������� �ʴ´�.
	�׸��� shallow���� �ּ�ó���� �Ҹ��ڴ� s1�� ���� �Ҹ��� ���� �̹� delete�� �޸𸮸� s2�� �����ϰ� �ֱ� ������ s2�� �޸𸮰� delete�� �� ������ ������ deep copy�� ��� ������ ���� �ʴ´�.
	*/


	return 0;
}