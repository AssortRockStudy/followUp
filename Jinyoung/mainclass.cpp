#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

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

class CCC : public BBB
{
private:
	int		m_C;

public:
	// ���� ���̵� <-> ���� �ε�
	void Move()
	{

		cout << "BBB Move" << endl;
	}

public:
	// �ڽ�Ŭ������ �����ڿ����� �θ� Ŭ������ �⺻�����ڸ� ȣ���Ѵ�.(�������� ���� �ʾƵ� �����Ϸ����� ȣ���)
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

	//���+������
	//������
	//�θ� ������ Ÿ�� �ּҰ��� �ԷµǴ� ��ü�� �ּ� Ÿ���� �ش�(�θ�)Ŭ������ ��ӹ޾� �Ļ��� Ŭ��������
	//�������� �����Ҽ��ִ�.
	{

		cout << "1231231"<<endl;
		AAA a;
		BBB b;


		AAA* pA = nullptr;
		BBB* pB = nullptr;

		pA = &a;
		pB = &b;

		//��Ӱ��迡 �ִ� Ŭ������ ���
		//�θ� Ŭ���� ������ Ÿ������, �ڽ�Ŭ������ ��ü �ּҸ� ���� �� �ִ�.(����ų �� �ִ�.)
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