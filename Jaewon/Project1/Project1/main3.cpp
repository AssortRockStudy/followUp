#include "Vehicle.h"


int main() {
    Vehicle vehic(8);
    Bicycle cycle(2);
    cycle.Drive();

    Car car(4);
    car.Honk();
    car.Drive();

    //cycle.Honk();  // �ּ� ���Ž� ���� �ٷ� ����
    vehic.Drive();


    return 0;
}