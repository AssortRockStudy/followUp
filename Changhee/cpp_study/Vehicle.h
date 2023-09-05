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
        cout << "������ " << _wheels << "���� ������ ��������ϴ�." << endl;
    };

    void Drive() { cout << "����մϴ�. " << endl; };
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
        cout << "����\n";
    }

    void Drive()
    {
        cout << "�ڵ����� ";
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