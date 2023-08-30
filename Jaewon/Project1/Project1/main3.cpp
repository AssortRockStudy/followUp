#include "Vehicle.h"


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