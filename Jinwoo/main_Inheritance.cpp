// 1�ܰ� pseudo code
// �θ� Ŭ���� <- �־���
// ��������� wheels�� ������ ����(�θ� ������ �� ��)
// �ڽ� Ŭ�������� ���ڰ� ���� ���� ������ �ʱ�ȭ�ϰ� ����ؾ� ��
// �ڽ� Ŭ���� -> Bicycle, Car
// Bicycle�� ���� ���� 2��
// Car�� ���� ���� 4��
// Drive �Լ��� �ڽ� Ŭ�������� ���Ǿ��� ���
// � �ڽ� Ŭ������ ȣ��Ǿ����� �������� ��
// Honk �Լ��� Car������ �۵� ����

#include <iostream>

using std::cout;
using std::endl;

class Vehicle
{
protected:
	int wheels;

public:
	void Drive()
	{
		cout << "����մϴ�. " << endl;
	}

public:
	Vehicle() : wheels(0)
	{

	}

	Vehicle(int _wheels) : wheels(_wheels)
	{
		cout << "������ " << _wheels << "���� ������ ��������ϴ�." << endl;
	}

	~Vehicle()
	{

	}
};

class Bicycle : public Vehicle
{
public:
	void Drive()
	{
		cout << "�����Ű� ";

		Vehicle::Drive();
	}

public:
	Bicycle() : Vehicle()
	{
	
	}

	Bicycle(int _wheels) : Vehicle(_wheels)
	{

	}

	~Bicycle()
	{

	}
};

class Car : public Vehicle
{
public:
	void Drive()
	{
		cout << "�ڵ����� ";

		Vehicle::Drive();
	}

	void Honk()
	{
		cout << "���� " << endl;
	}

public:
	Car() : Vehicle()
	{

	}

	Car(int _wheels) : Vehicle(_wheels)
	{

	}

	~Car()
	{

	}
};

int main()
{
	Vehicle vehic(8);
	Bicycle cycle(2);
	cycle.Drive();

	Car car(4);
	car.Honk();
	car.Drive();

	//cycle.Honk();
	vehic.Drive();

	return 0;
}