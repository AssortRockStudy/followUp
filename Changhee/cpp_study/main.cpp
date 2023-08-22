#include <iostream>

using std::cout;
using std::endl;


/*
 &는 원본은 참조할 수 있는 l-value 이다. const 붙일 경우 함수안에서는 r-value가 되어 원본을 변경할 수 없다.
 &&는 r-value 참조이지만 원본은 변경할 수 있다. 하지만 r-value가 상수라는 의미이기 때문에 해당 원본을 변경하여도 변경이 되지 않는다.(ex. 상수 10을 20으로 변경한다고 숫자 10이 20이 되지 않는다)
 그래서 &&는 거의 사용하는 의미가 없고  이동 대입연산자의 트리거 정도로 사용된다.

 int && -> a 가 오류가 남
 int & -> 원본 변경 가능

 const & 타입으로 모두 커버 가능
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
		cout << "기본 생성자 호출" << endl;
	}

	myArray(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
	{
		cout << "기본 생성자(int) 호출" << endl;
		m_pData = new int[m_iSize];
	}

	// 복사 생성자
	myArray(const myArray& _Other)
	{
		cout << "복사 생성자 호출" << endl;

		m_iSize = _Other.m_iSize;
		m_pData = new int[m_iSize];


		for (int i = 0; i < m_iSize; ++i)
		{
			m_pData[i] = _Other.m_pData[i];
		}
	}

	// 이동 생성자 -> r-value 참조가 트리거가 된다.(&&)
	myArray(myArray&& _Other)
	{
		
		cout << "이동 생성자 호출" << endl;

		// 자신의 모든것을 넘겨주고 깡통이 됨. 생명주기가 끝나면 알아서 삭제
		m_iSize = _Other.m_iSize;
		m_pData = _Other.m_pData;

		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;
	}


	// 대입 연산자
	myArray& operator= (const myArray& _Other)
	{
		cout << "대입연산자 호출" << endl;

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

	// 이동 대입 연산자
	myArray& operator= (myArray&& _Other)
	{
		cout << "이동 대입연산자 호출" << endl;

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