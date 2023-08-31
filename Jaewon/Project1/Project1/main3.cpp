#include "Vehicle.h"


int main() {
    Vehicle vehic(8);
    Bicycle cycle(2);
    Car car(4);

    cycle.Drive(10);
    car.Honk();
    car.Drive(30);

    // vehic.Drive(); // 주석 제거시 빨간 줄로 오류

    return 0;
}