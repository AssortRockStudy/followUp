//#include "Vehicle.h"
//
//int main() {
//    Vehicle vehic(8);
//    Bicycle cycle(2);
//    cycle.Drive();
//
//    Car car(4);
//    car.Honk();
//    car.Drive();
//
//    //cycle.Honk();  // �ּ� ���Ž� ���� �ٷ� ����
//    vehic.Drive();
//
//
//    return 0;
//}

#include "Vehicle.h"

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