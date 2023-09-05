#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Vehicle {

protected:
    int wheels;
    string name;

public:
    Vehicle() : wheels(0), name("") {};
    Vehicle(int _wheels, string _name = "����") : wheels(_wheels), name(_name) {
        cout << "������ " << _wheels << "���� " << name
            << "��(��) ��������ϴ�." << endl;
    };

public:
    virtual void Drive() { cout << name << "�� ����մϴ�. " << endl; };
};

class Bicycle :public Vehicle
{
public:
    void Drive()
    {
        cout << name << "�� ��޷� ����ϴ�" << endl;
    }

public:
    Bicycle() {}
    Bicycle(int _wheels)
        : Vehicle(_wheels, "������")
    {
    }
    

    ~Bicycle() {}
};


class Car :public Vehicle
{

public:
    void Drive()
    {
        cout << name << "�� �Ǽ��� �����ϴ�." << endl;
    }

public:
    Car() {}
    Car(int _wheels) 
        : Vehicle(_wheels, "�ڵ���")
    {
    }


    ~Car() {}
};


int main()
{
    vector<Vehicle*> vehicles;

    Vehicle* vehic = new Vehicle(8);
    Bicycle* cycle = new Bicycle(2);
    Car* car = new Car(4);

    vehicles.push_back(vehic);
    vehicles.push_back(cycle);
    vehicles.push_back(car);
    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i]->Drive();
    }


}