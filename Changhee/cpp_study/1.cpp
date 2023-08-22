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

	// 깊은 복사 구현
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

	// shallow 객체 생성 후 배열 안에 값 넣기
	shallow s1(5);
	s1.m_pData[0] = 1;
	s1.m_pData[1] = 2;
	s1.m_pData[2] = 3;
	s1.m_pData[3] = 4;
	s1.m_pData[4] = 5;

	// 기본 복사 생성자를 이용하여 s1을 s2에 복사
	shallow s2(s1);


	// s1, s2 출력
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

	// s2 내용 변경
	cout << "s2 변경\n\n";
	for (int i = 0; i < 5; ++i)
	{
		s2.m_pData[i] += 5;
	}

	// s1, s2 출력
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
	s2 변경

	shallow s1 :
	6 7 8 9 10
	shallow s2 :
	6 7 8 9 10

	s2만 변경 했는데 s1도 같이 변경된 것을 알 수 있다.
	기본 복사 생성자의 경우 주석처리된 복사생성자처럼 객체 안에 멤버 변수를 그대로 복사하는 방식으로 작동하는데, 
	만약 멤버변수중에 동적할당된 멤버변수가 있다면 변수가 가지고 있는 값은 동적할당된 힙 메모리의 주소이기 때문에 실제로 복사되는 것은 주소가 그대로 복사되고 새롭게 동적할당하는 것이 아니다.
	*/


	cout << endl << endl;
	cout << "deep copy\n\n";

	// deep 객체 생성 후 배열 안에 값 넣기
	deep d1(5);
	d1.m_pData[0] = 1;
	d1.m_pData[1] = 2;
	d1.m_pData[2] = 3;
	d1.m_pData[3] = 4;
	d1.m_pData[4] = 5;

	// 직접 구현한 복사 생성자를 이용하여 d1을 d2에 복사
	deep d2(d1);

	// d1, d2 출력
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

	// d2 내용 변경
	cout << "d2 변경\n\n";
	for (int i = 0; i < 5; ++i)
	{
		d2.m_pData[i] += 5;
	}

	// d1, d2 출력
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
	d2 변경

	deep d1:
	1 2 3 4 5
	deep s2:
	6 7 8 9 10

	직접 구현한 복사생성자는 새로운 힙 메모리를 할당 받고 그 안에 값들을 직접 복사하기 때문에 두개의 객체는 각각 다른 힙 메모리를 할당 받게된다. 
	이렇게 되었을 경우 d2를 변경하더라도 d2의 배열주소와 d1의 배열주소가 다르기 때문에 d1의 값은 변경되지 않는다.
	그리고 shallow에서 주석처리된 소멸자는 s1이 먼저 소멸한 이후 이미 delete된 메모리를 s2가 참조하고 있기 때문에 s2의 메모리가 delete될 때 에러가 나지만 deep copy의 경우 에러가 나지 않는다.
	*/


	return 0;
}