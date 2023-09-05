#include <vector>

#include "Vehicle.h"

using std::vector;

int main() {
    // Vehicle vehic(8);
    // Bicycle cycle(2);
    // cycle.Drive();

    // Car car(4);
    // car.Honk();
    // car.Drive();

    //// cycle.Honk();
    // vehic.Drive();

    /*Vehicle vehic(8);
    Bicycle cycle(2);
    Car car(4);

    cycle.Drive(10);
    car.Honk();
    car.Drive(30);*/

    // vehic.Drive();

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

    return 0;
}