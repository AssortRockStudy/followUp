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
        cout << "������ " << _wheels << "���� ������ ��������ϴ�." << endl;
    };

    void Drive()
    { cout << "����մϴ�. " << endl; };
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
        cout << "�����Ű� ����մϴ�." << endl;
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
        cout << "�ڵ����� ����մϴ�." << endl;
    }

    void Honk()
    {
        cout << "����" << endl;
    }

};