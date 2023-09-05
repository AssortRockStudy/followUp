#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Vehicle {
private:
    int wheels;
    string name;

public:
    Vehicle() : wheels(0), name("") {};
    Vehicle(int _wheels, string _name = "차량") 
        : wheels(_wheels), name(_name) 
    {
        cout << "바퀴가 " << _wheels << "개인 " << name << "을(를) 만들었습니다." << endl;
    };

protected:
    void Drive(int _speed) { cout << _speed << "km/h 속도로 " << name << "이(가) 출발합니다. " << endl; };
};


class Bicycle : public Vehicle
{
public:
    void Drive(int _speed)
    {
        Vehicle::Drive(_speed);
    }


public:
    Bicycle()    {}
    Bicycle(int _wheels)
        : Vehicle(_wheels, "자전거")
    {}

    ~Bicycle()
    {}
};


class Car : public Vehicle
{

public:
    void Honk()
    {
        cout << "빵빵\n";
    }

    void Drive(int _speed)
    {
        Vehicle::Drive(_speed);
    }

public:
    Car(){}

    Car(int _wheels)
        : Vehicle(_wheels, "자동차")
    {}

    ~Car()
    {}
};


int main() {
    Vehicle vehic(8);
    Bicycle cycle(2);
    Car car(4);

    cycle.Drive(10);
    car.Honk();
    car.Drive(30);

    // vehic.Drive(); // 주석 제거시 빨간 줄로 오류

    return 0;
}