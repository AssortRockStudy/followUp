#pragma once

#include <iostream>

using std::cout;
using std::endl;

class Vehicle {
protected:
    int wheels;

public:
    Vehicle() : wheels(0) {};
    Vehicle(int _wheels) : wheels(_wheels) {
        cout << "바퀴가 " << _wheels << "개인 차량을 만들었습니다." << endl;
    };

    void Drive() { cout << "출발합니다. " << endl; };
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
    Bicycle()
    {
    }

    Bicycle(int _wheels)
        : Vehicle(_wheels)
    {
    }


    ~Bicycle()
    {
    }

};


class Car : public Vehicle
{

public:
    void Honk()
    {
        cout << "빵빵\n";
    }

    void Drive()
    {
        cout << "자동차가 ";
        Vehicle::Drive();
    }

public:
    Car()
    {
    }
    Car(int _wheels)
        : Vehicle(_wheels)
    {
    }

    ~Car()
    {
    }
};