#include <iostream>
#include <functional>
#include <chrono>
#include <Subscriber.h>
#include <Distributor.h>
#include <DataPlotter.h>
#include "Imu.h"
#include "Sensor.h"
#include "UltraSonicSensor.h"


void testDist();

int main() {
    //testUltraSonicSensor();
    testDist();

    return 0;
}

void testDist(){

    apk::Distributor dist;

    apk::DataPlotter sub1, sub2;
    dist.addSubscriber(&sub1);
    dist.addSubscriber(&sub2);
    dist.test();

    // Callback function as a lambda expression for now
    //std::function<void(float)> call = [&](float a){ std::cout << a << std::endl; };

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an Imu sensor
    imu = new apk::Imu<float>;

    apk::Sensor* ultraSonicSensor;

    ultraSonicSensor = new UltraSonicSensor;
    dist.addSensor(ultraSonicSensor);
    dist.connectSensor(ultraSonicSensor);
    dist.subConnectToSensor(&sub1, ultraSonicSensor);


    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.subConnectToSensor(&sub1, imu);
    // Connect to the sensor
    //imu->connect();

    // Let the Imu thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.subConnectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.removeSubscriber(&sub1);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;
}