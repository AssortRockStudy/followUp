#include <iostream>
#include <string>

using namespace std;




class Vehicle {
protected:
    int wheels;

public:
    Vehicle() : wheels(0) {};
    Vehicle(int _wheels) : wheels(_wheels) {
        cout << "바퀴가 " << _wheels << "개인 차량을 만들었습니다." << endl;
    };

    void Drive() { cout << "출발합니다. " << endl; };
};


class Bicycle : public Vehicle {
protected:

public:
    string name = "자전거";
    Bicycle() {};
    Bicycle(int _wheels) :Vehicle(_wheels) {
    };

    void Drive() { cout << name << "가"; Vehicle::Drive(); };
};

class Car : public Vehicle {
protected:
    int wheels;
    string name = "자동차";

public:
    Car() : wheels(0) {};
    Car(int _wheels) :Vehicle(_wheels) {
    };

    void Drive() { cout << name << "가"; Vehicle::Drive(); };
    void Honk() { cout << "빵빵아" << endl; };

};






int main() {
    Vehicle vehic(8);
    Bicycle cycle(2);
    cycle.Drive();

    Car car(4);
    car.Honk();
    car.Drive();

    //cycle.Honk();  // 주석 제거시 빨간 줄로 오류
    vehic.Drive();


    return 0;
}