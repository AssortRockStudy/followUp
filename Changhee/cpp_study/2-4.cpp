#include <iostream>
#include <list>
#include <crtdbg.h>


using std::list;
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

private:
	int*	m_pData;
	int		m_iSize;
	int		m_iCur;

public:
	void push_back(int _data)
	{
		if (m_iSize == m_iCur)
		{
			// 배열 재할당
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
		cout << "기본 생성자 호출" << endl;
	}

	myArray(int _size)
		: m_iSize(_size)
		, m_pData(nullptr)
		, m_iCur(0)
	{
		cout << "기본 생성자(int) 호출" << endl;
		m_pData = new int[m_iSize];
	}

	// 복사 생성자
	myArray(const myArray& _Other)
	{
		cout << "복사 생성자 호출" << endl;

		m_iSize = _Other.m_iSize;
		m_iCur = _Other.m_iCur;
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
		m_iCur = _Other.m_iCur;
		m_pData = _Other.m_pData;


		_Other.m_iSize = 0;
		_Other.m_pData = nullptr;
		_Other.m_iCur = 0;
	}


	// 대입 연산자
	myArray& operator= (const myArray& _Other)
	{
		cout << "대입연산자 호출" << endl;

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

	// 이동 대입 연산자
	myArray& operator= (myArray&& _Other)
	{
		cout << "이동 대입연산자 호출" << endl;

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


	// 메모리 leak 확인 -> leak 없음
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	myArray mArr(5);

	mArr.push_back(1);
	mArr.push_back(2);
	mArr.push_back(3);


	cout << "\nmArr1 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;

	// =======================
	// 복사 생성자 호출(깊은 복사)
	// =======================

	// 선언과 동시에 할당하기 때문에 최적화되어 생성자 -> 대입연산자가 아니라 복사 생성자가 호출된다.

	cout << "----------------------------------\n";
	cout << "복사 생성자를 이용해 mArr2를 선언\n";

	myArray mArr2 = mArr;
	// myArray mArr2(mArr);


	cout << "\nmArr1 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr2 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;



	// 깊은 복사 확인

	cout << "----------------------------------\n";

	cout << "mArr2의 값 변경\n";
	mArr2[0] = 10;

	cout << "\nmArr1 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr2 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	// 복사생성자를 직접 구현해 깊은 복사를 하였기 때문에 mArr2의 값을 변경하여도 mArr1의 값이 변하지 않음


	// ==============
	// 이동 생성자 호출
	// ==============

	cout << "----------------------------------\n";
	cout << "이동생성자 호출 mArr1 -> mArr_move\n";

	myArray mArr_move(std::move(mArr));

	cout << "\nmArr1 출력 : ";
	for (int i = 0; i < mArr.size(); ++i)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr_move 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr_move[i] << " ";
	}
	std::cout << std::endl;

	cout << "----------------------------------\n";
	cout << "대입연산자 mArr2 -> mArrCopy\n";
	
	myArray mArrCopy;
	mArrCopy = mArr2;


	cout << "\nmArr2 출력 : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;



	cout << "\nmArr_Copy 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArrCopy[i] << " ";
	}
	std::cout << std::endl;


	cout << "mArrCopy의 값 변경\n";
	mArrCopy[0] = 100;

	cout << "\nmArr2 출력 : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	cout << "\nmArr_Copy 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArrCopy[i] << " ";
	}
	std::cout << std::endl;

	// 대입 연산자가 잘 구현되어 mArr_Copy의 값을 변경하여도 mArr2의 값이 변경되지 않는다.
	cout << "----------------------------------\n";
	cout << "이동 대입연산자 mArr2 -> mArr3\n";

	myArray mArr3;
	mArr3 = std::move(mArr2);

	cout << "\nmArr2 출력 : ";
	for (int i = 0; i < mArr2.size(); ++i)
	{
		std::cout << mArr2[i] << " ";
	}
	std::cout << std::endl;

	cout << "\nmArr3 출력 : ";
	for (int i = 0; i < 3; ++i)
	{
		std::cout << mArr3[i] << " ";
	}
	std::cout << std::endl;



	return 0;
}