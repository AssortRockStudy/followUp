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
    Vehicle(int _wheels, string _name = "����") : wheels(_wheels), name(_name) {
        cout << "������ " << _wheels << "���� " << name
             << "��(��) ��������ϴ�." << endl;
    };

   public:
    virtual void Drive() { cout << name << "�� ����մϴ�. " << endl; };
};

class Bicycle : public Vehicle {
   public:
    Bicycle(){};
    Bicycle(int _wheels)
        : Vehicle(_wheels, "������"){

          };
    void Drive() override { cout << name << "�� ��޷� ����ϴ�. " << endl; }
};

class Car : public Vehicle {
   public:
    Car(){};
    Car(int _wheels) : Vehicle(_wheels, "�ڵ���"){};

    void Drive() override { cout << name << "�� �Ǽ��� �����ϴ�. " << endl; };
    void Honk() { cout << "����" << endl; };
};