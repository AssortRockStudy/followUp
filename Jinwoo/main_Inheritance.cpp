// 3단계 pseudo code
// 부모 클래스 <- 주어짐
// 부모 클래스 멤버변수 '바퀴 개수, name'
// name에는 기본적으로 "차량" 문자열이 들어감
// 대신 자식 클래스에서 호출할 경우 자식 클래스 차량의 문자열이 들어가야 함
// Drive 함수가 가상함수로 변경됨
// Drive함수를 상속받는 자식 클래스는 virtual Drive() override를 붙여줘야 함

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Vehicle
{
protected:
	int wheels;
	string name;

public:
	virtual void Drive()
	{
		cout << name << "이 출발합니다. " << endl;
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
	virtual void Drive() override
	{
		cout << name << "를 페달로 밟습니다" << endl;
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
	virtual void Drive() override
	{
		cout << name << "의 악셀을 누릅니다" << endl;
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
	Vehicle* vehic = new Vehicle(8);
	Bicycle* cycle = new Bicycle(2);
	Car* car = new Car(4);
	
	vector<Vehicle*> vehicles;

	vehicles.push_back(vehic);
	vehicles.push_back(cycle);
	vehicles.push_back(car);

	for (int i = 0; i < vehicles.size(); ++i)
	{
		vehicles[i]->Drive();
	}

	return 0;
}