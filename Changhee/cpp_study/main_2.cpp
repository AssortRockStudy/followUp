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
    Vehicle(int _wheels, string _name = "����") 
        : wheels(_wheels), name(_name) 
    {
        cout << "������ " << _wheels << "���� " << name << "��(��) ��������ϴ�." << endl;
    };

protected:
    void Drive(int _speed) { cout << _speed << "km/h �ӵ��� " << name << "��(��) ����մϴ�. " << endl; };
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
        : Vehicle(_wheels, "������")
    {}

    ~Bicycle()
    {}
};


class Car : public Vehicle
{

public:
    void Honk()
    {
        cout << "����\n";
    }

    void Drive(int _speed)
    {
        Vehicle::Drive(_speed);
    }

public:
    Car(){}

    Car(int _wheels)
        : Vehicle(_wheels, "�ڵ���")
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

    // vehic.Drive(); // �ּ� ���Ž� ���� �ٷ� ����

    return 0;
}