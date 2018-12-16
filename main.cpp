#include <iostream>
#include "Imu.h"
#include "Sensor.h"

int main() {

    // Callback function as a lambda expression for now
    std::function<void(std::string)> call = [&](std::string a){ std::cout << a << std::endl; };

    // The sensor interface
    apk::Sensor<float>* imu;

    // Instantiate an Imu sensor
    imu = new Imu<float>(call);

    // Connect to the sensor
    imu->connect();

    // Let the Imu thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    imu->disconnect();

    std::cout << imu->test() << std::endl;
    return 0;
}