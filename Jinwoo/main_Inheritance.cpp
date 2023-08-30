// 1단계 pseudo code
// 부모 클래스 <- 주어짐
// 멤버변수로 wheels를 가지고 있음(부모만 가져도 될 듯)
// 자식 클래스에서 각자가 가진 바퀴 개수를 초기화하고 출력해야 함
// 자식 클래스 -> Bicycle, Car
// Bicycle의 바퀴 개수 2개
// Car의 바퀴 개수 4개
// Drive 함수는 자식 클래스에서 사용되었을 경우
// 어떤 자식 클래스가 호출되었는지 출력해줘야 함
// Honk 함수는 Car에서만 작동 가능

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
		cout << "출발합니다. " << endl;
	}

public:
	Vehicle() : wheels(0)
	{

	}

	Vehicle(int _wheels) : wheels(_wheels)
	{
		cout << "바퀴가 " << _wheels << "개인 차량을 만들었습니다." << endl;
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
		cout << "자전거가 ";

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
		cout << "자동차가 ";

		Vehicle::Drive();
	}

	void Honk()
	{
		cout << "빵빵 " << endl;
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