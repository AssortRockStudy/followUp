#pragma once
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
    Vehicle(int _wheels, string _name = "차량") : wheels(_wheels), name(_name) {
        cout << "바퀴가 " << _wheels << "개인 " << name
            << "을(를) 만들었습니다." << endl;
    };

protected:
    void Drive(int _speed) { cout << _speed << "km/h 속도로 " << name << "이(가) 출발합니다. " << endl; };
};

class Bicycle : public Vehicle {

public:
    void Drive(int speed) {
        Vehicle::Drive(speed);
    }

public:
    Bicycle() :Vehicle() {}
    Bicycle(int wheelNum, string name = "자전거") :Vehicle(wheelNum, name) {  }
    ~Bicycle(){}

};

class Car : public Vehicle {
public:
    void Drive(int speed) {
        Vehicle::Drive(speed);
    }
    void Honk() { cout << "빵빵" << endl; }
public:
    Car():Vehicle() {  }
    Car(int wheelNum, string name = "자동차"):Vehicle(wheelNum, name) {}
    ~Car(){}
};