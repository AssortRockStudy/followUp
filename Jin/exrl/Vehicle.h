#include <iostream>
using std::cout;
using std::endl;


class Vehicle {
protected:
    int wheels;

public:
    Vehicle()
        : wheels(0) {};

    Vehicle(int _wheels)
        : wheels(_wheels) 
    {
        cout << "바퀴가 " << _wheels << "개인 차량을 만들었습니다." << endl;
    };

    void Drive()
    { cout << "출발합니다. " << endl; };
};


class Bicycle : public Vehicle
{
public:
    Bicycle()
        {};
    Bicycle(int _wheels)
        : Vehicle(_wheels) {}
    ~Bicycle() {}

    void Drive()
    {
        cout << "자전거가 출발합니다." << endl;
    }
};

class Car : public Vehicle
{
public:
    Car()
    {};
    Car(int _wheels)
        : Vehicle(_wheels) {}
    ~Car() {}

    void Drive()
    {
        cout << "자동차가 출발합니다." << endl;
    }

    void Honk()
    {
        cout << "빵빵" << endl;
    }

};