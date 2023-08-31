#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


//class Vehicle {
//protected:
//    int wheels;
//
//public:
//    Vehicle()
//        : wheels(0) {};
//
//    Vehicle(int _wheels)
//        : wheels(_wheels) 
//    {
//        cout << "������ " << _wheels << "���� ������ ��������ϴ�." << endl;
//    };
//
//    void Drive()
//    { cout << "����մϴ�. " << endl; };
//};
//
//
//class Bicycle : public Vehicle
//{
//public:
//    Bicycle()
//        {};
//    Bicycle(int _wheels)
//        : Vehicle(_wheels) {}
//    ~Bicycle() {}
//
//    void Drive()
//    {
//        cout << "�����Ű� ����մϴ�." << endl;
//    }
//};
//
//class Car : public Vehicle
//{
//public:
//    Car()
//    {};
//    Car(int _wheels)
//        : Vehicle(_wheels) {}
//    ~Car() {}
//
//    void Drive()
//    {
//        cout << "�ڵ����� ����մϴ�." << endl;
//    }
//
//    void Honk()
//    {
//        cout << "����" << endl;
//    }
//
//};


//class Vehicle {
//private:
//    int wheels;
//    string name;
//
//public:
//    Vehicle()
//        : wheels(0), name("") {};
//    Vehicle(int _wheels, string _name = "����")
//        : wheels(_wheels), name(_name) 
//    {
//        cout << "������ " << _wheels << "���� " << name << "��(��) ��������ϴ�." << endl;
//        
//    };
//
//protected:
//    void Drive(int _speed) 
//    { 
//        cout << _speed << "km/h �ӵ��� " << name << "��(��) ����մϴ�. " << endl; 
//    };
//};
//
//class Bicycle : public Vehicle
//{
//public:
//    Bicycle(int _wheels, string _name = "������")
//        : Vehicle(_wheels, _name)
//    {
//    }
//    ~Bicycle()
//    {}
//
//    void Drive(int _speed)
//    {
//        Vehicle::Drive(_speed);
//    }
//};
//
//class Car : public Vehicle
//{
//public:
//    Car(int _wheels, string _name = "�ڵ���")
//        : Vehicle(_wheels, _name) {}
//    ~Car()
//    {}
//
//    void Drive(int _speed)
//    {
//        Vehicle::Drive(_speed);
//    }
//
//    void Honk()
//    {
//        cout << "����" << endl;
//    }
//};

class Vehicle {
protected:
    int wheels;
    string name;

public:
    Vehicle() : 
        wheels(0), name("") {};

    Vehicle(int _wheels, string _name = "����") 
        : wheels(_wheels), name(_name) 
    {
        cout << "������ " << _wheels << "���� " << name << "��(��) ��������ϴ�." << endl;
    };

public:
    virtual void Drive()
    { cout << name << "�� ����մϴ�. " << endl; };
};

class Bicycle : public Vehicle
{
public:
    Bicycle(int _wheels)
        : Vehicle(_wheels, "������") {};

    ~Bicycle() {};

public:
    virtual void Drive() override
    { cout << name << "�� ����� ����ϴ�. " << endl; };
};

class Car : public Vehicle
{
public:
    Car(int _wheels)
        : Vehicle(_wheels, "�ڵ���") {};

    ~Car() {};
public:
    virtual void Drive() override
    { cout << name << "�� �Ǽ��� �����ϴ�. " << endl; };

};