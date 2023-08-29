#include <iostream>

using std::cout;
using std::endl;

class AAA
{
	// �ܺΰ��� X, ��� �޴� �ڽ� Ŭ����(�Ļ� Ŭ����) �鿡�Դ� ����
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
	// ���� ���̵� <-> ���� �ε�
	void Move()
	{
		AAA::Move();

		cout << "BBB Move" << endl;
	}

public:
	// �ڽ�Ŭ������ �����ڿ����� �θ� Ŭ������ �⺻�����ڸ� ȣ���Ѵ�.(�������� ���� �ʾƵ� �����Ϸ����� ȣ���)
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




int main()
{
	// Ŭ����
	// ���, ������, �߻�ȭ
	// ��� : �ڵ��� ����, ���� ��� ����	

	// ��� ���迡�� �ʱ�ȭ ����, �θ� -> �ڽ�
	// ��� ���迡�� �Ҹ��� ȣ�� ����, �ڽ� -> �θ�


	int i = 0;
	i = sizeof(AAA);
	i = sizeof(BBB);

	AAA a;
	BBB b(10, 20);

	a.Move();
	b.Move();
	b.AAA::Move();

	return 0;
}