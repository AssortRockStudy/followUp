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
//        cout << "바퀴가 " << _wheels << "개인 차량을 만들었습니다." << endl;
//    };
//
//    void Drive()
//    { cout << "출발합니다. " << endl; };
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
//        cout << "자전거가 출발합니다." << endl;
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
//        cout << "자동차가 출발합니다." << endl;
//    }
//
//    void Honk()
//    {
//        cout << "빵빵" << endl;
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
//    Vehicle(int _wheels, string _name = "차량")
//        : wheels(_wheels), name(_name) 
//    {
//        cout << "바퀴가 " << _wheels << "개인 " << name << "을(를) 만들었습니다." << endl;
//        
//    };
//
//protected:
//    void Drive(int _speed) 
//    { 
//        cout << _speed << "km/h 속도로 " << name << "이(가) 출발합니다. " << endl; 
//    };
//};
//
//class Bicycle : public Vehicle
//{
//public:
//    Bicycle(int _wheels, string _name = "자전거")
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
//    Car(int _wheels, string _name = "자동차")
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
//        cout << "빵빵" << endl;
//    }
//};

class Vehicle {
protected:
    int wheels;
    string name;

public:
    Vehicle() : 
        wheels(0), name("") {};

    Vehicle(int _wheels, string _name = "차량") 
        : wheels(_wheels), name(_name) 
    {
        cout << "바퀴가 " << _wheels << "개인 " << name << "을(를) 만들었습니다." << endl;
    };

public:
    virtual void Drive()
    { cout << name << "이 출발합니다. " << endl; };
};

class Bicycle : public Vehicle
{
public:
    Bicycle(int _wheels)
        : Vehicle(_wheels, "자전거") {};

    ~Bicycle() {};

public:
    virtual void Drive() override
    { cout << name << "로 페달을 밟습니다. " << endl; };
};

class Car : public Vehicle
{
public:
    Car(int _wheels)
        : Vehicle(_wheels, "자동차") {};

    ~Car() {};
public:
    virtual void Drive() override
    { cout << name << "의 악셀을 누릅니다. " << endl; };

};