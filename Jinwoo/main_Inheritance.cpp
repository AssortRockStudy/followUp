// 2단계 pseudo code
// 부모 클래스 <- 주어짐
// 부모 클래스 멤버변수 '바퀴 개수, name'
// name에는 기본적으로 "차량" 문자열이 들어감
// 대신 자식 클래스에서 호출할 경우 자식 클래스 차량의 문자열이 들어가야 함
// Drive 인자에 속도가 추가됨

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Vehicle
{
private:
	int wheels;
	string name;

protected:
	void Drive(int _speed)
	{
		cout << _speed << "km/h 속도로 " << name << "이(가) 출발합니다. " << endl;
	}

public:
	Vehicle() : wheels(0), name("")
	{};
	
	Vehicle(int _wheels, string _name = "차량") : wheels(_wheels), name(_name)
	{
		cout << "바퀴가 " << _wheels << "개인 " << name << "을(를) 만들었습니다." << endl;
	};

	~Vehicle()
	{

	}
};

class Bicycle : public Vehicle
{
public:
	void Drive(int _speed)
	{
		Vehicle::Drive(_speed);
	}

public:
	Bicycle() : Vehicle()
	{
	
	}

	Bicycle(int _wheels, string _name = "자전거") : Vehicle(_wheels, _name)
	{

	}

	~Bicycle()
	{

	}
};

class Car : public Vehicle
{
public:
	void Drive(int _speed)
	{
		Vehicle::Drive(_speed);
	}

	void Honk()
	{
		cout << "빵빵 " << endl;
	}

public:
	Car() : Vehicle()
	{

	}

	Car(int _wheels, string _name = "자동차") : Vehicle(_wheels, _name)
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
	Car car(4);

	cycle.Drive(10);
	car.Honk();
	car.Drive(30);

	// vehic.Drive();

	return 0;
}