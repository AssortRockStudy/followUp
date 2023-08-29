#include <iostream>
#include <string>

using namespace std;




class Vehicle {
protected:
    int wheels;
    string name;

public:
    Vehicle() : wheels(0) {};
    Vehicle(int _wheels, string _name = "차량") : wheels(_wheels), name(_name) {
        cout << "바퀴가 " << _wheels << "개인 " << name
            << "을(를) 만들었습니다." << endl;
    };

    void Drive(int _speed) { cout << _speed << "km/h 속도로 " << name << "이(가) 출발합니다. " << endl; };
};


class Bicycle : public Vehicle {
protected:

public:

    Bicycle() {  };
    Bicycle(int _wheels) :Vehicle(_wheels,"자전거")
    {
    };

};

class Car : public Vehicle {
protected:

public:

    Car() 
    {
    };
    Car(int _wheels) :Vehicle(_wheels,"자동차")
    {
    };

    void Honk() { cout << "빵빵아" << endl; };

};






int main() {
    Vehicle vehic(8);
    Bicycle cycle(2);
    Car car(4);

    cycle.Drive(10);
    car.Honk();
    car.Drive(30);

    //vehic.Drive();


    return 0;
}