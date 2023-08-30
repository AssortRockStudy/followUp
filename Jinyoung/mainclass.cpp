#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class AAA
{
	// 외부공개 X, 상속 받는 자식 클래스(파생 클래스) 들에게는 공개
protected:
	int		m_A;


public:
	void Move()
	{
		cout << "AAA Move" << endl;
	}

public:
	AAA()
		: m_A(0)
	{

	}

	AAA(int _A)
		: m_A(_A)
	{

	}

	~AAA()
	{

	}
};

class BBB : public AAA
{
private:
	int		m_B;

public:
	// 오버 라이딩 <-> 오버 로딩
	void Move()
	{

		cout << "BBB 움직임" << endl;
	}

public:
	// 자식클래스의 생성자에서는 부모 클래스의 기본생성자를 호출한다.(수동으로 하지 않아도 컴파일러의해 호출됨)
	BBB()
		: m_B(0)
	{
		m_A = 10;
		m_B = 10;
	}

	BBB(int _A, int _B)
		: m_B(_B)
		, AAA(_A)
	{
	}

	~BBB()
	{
	}
};

class CCC : public BBB
{
private:
	int		m_C;

public:
	// 오버 라이딩 <-> 오버 로딩
	void Move()
	{

		cout << "BBB 움직임" << endl;
	}

public:
	// 자식클래스의 생성자에서는 부모 클래스의 기본생성자를 호출한다.(수동으로 하지 않아도 컴파일러의해 호출됨)
	CCC()
		: m_C(0)
	{
		m_A = 10;
	}

	CCC(int _A, int _B)
	{
	}

	~CCC()
	{
	}
};



int main()
{
	// 클래스
	// 상속, 다형성, 추상화
	// 상속 : 코드의 재사용, 공통 기능 구현	

	// 상속 관계에서 초기화 순서, 부모 -> 자식
	// 상속 관계에서 소멸자 호출 순서, 자식 -> 부모


	int i = 0;
	i = sizeof(AAA);
	i = sizeof(BBB);

	AAA a;
	BBB b(10, 20);

	a.Move();
	b.Move();
	b.AAA::Move();

	//상속+포인터
	//다형성
	//부모 포인터 타입 주소값에 입력되는 객체의 주소 타입은 해당(부모)클래스를 상속받아 파생된 클래스들중
	//누구든지 저장할수있다.
	{

		cout << "1231231"<<endl;
		AAA a;
		BBB b;


		AAA* pA = nullptr;
		BBB* pB = nullptr;

		pA = &a;
		pB = &b;

		//상속관계에 있는 클래스의 경우
		//부모 클래스 포인터 타입으로, 자식클래스의 객체 주소를 받을 수 있다.(가리킬 수 있다.)
		pA = &b;
		//pB = &a;

		vector<AAA*> vecData;

		vecData.push_back(new AAA);
		vecData.push_back(new BBB);
		vecData.push_back(new CCC);

		a.Move();
		b.Move();

		for (int i = 0; i < vecData.size(); ++i) 
		{
			vecData[i]->Move();
		}

	}

	return 0;
}