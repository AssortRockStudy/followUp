#include <iostream>
#include <string>
#include <vector>

using namespace std;






class Vehicle {
protected:
    int wheels;
    string name;

public:
    Vehicle() : wheels(0), name("") {};
    Vehicle(int _wheels, string _name = "차량") : wheels(_wheels), name(_name) {
        cout << "바퀴가 " << _wheels << "개인 " << name
            << "을(를) 만들었습니다." << endl;
    };

public:
    virtual void Drive() { cout << name << "이 출발합니다. " << endl; };
};


class Bicycle : public Vehicle {
protected:

public:

    Bicycle() {  };
    Bicycle(int _wheels) :Vehicle(_wheels,"자전거")
    {
    };
    void Drive() { cout << name << "를 페달로 밟습니다." << endl; };

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
    void Drive() { cout << name << "의 악셀를 누릅니다." << endl; };

};






int main() {

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

    //vehic.Drive();


    return 0;
}