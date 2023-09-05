#include "Vehicle.h"
#include <vector>

using std::vector;

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

    return 0;
}