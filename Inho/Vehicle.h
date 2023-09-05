#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Vehicle {
   protected:
    int wheels;
    string name;

   public:
    Vehicle() : wheels(0), name(""){};
    Vehicle(int _wheels, string _name = "차량") : wheels(_wheels), name(_name) {
        cout << "바퀴가 " << _wheels << "개인 " << name
             << "을(를) 만들었습니다." << endl;
    };

   public:
    virtual void Drive() { cout << name << "이 출발합니다. " << endl; };
};

class Bicycle : public Vehicle {
   public:
    Bicycle(){};
    Bicycle(int _wheels)
        : Vehicle(_wheels, "자전거"){

          };
    void Drive() override { cout << name << "를 페달로 밟습니다. " << endl; }
};

class Car : public Vehicle {
   public:
    Car(){};
    Car(int _wheels) : Vehicle(_wheels, "자동차"){};

    void Drive() override { cout << name << "의 악셀을 누릅니다. " << endl; };
    void Honk() { cout << "빵빵" << endl; };
};