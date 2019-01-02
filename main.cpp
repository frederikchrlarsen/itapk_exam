#include <iostream>
#include <functional>
#include <chrono>
#include "Subscriber.h"
#include "Distributor.h"
#include "DataPlotter.h"
#include "Imu.h"
#include "Sensor.h"
#include "UltraSonicSensor.h"
#include "manipulateData.h"
#include "SensorData.h"


void testDist();

void testLength();

void testUltraSonicSensor();

void testSpeed();

void testSensorData();

void testDataPlotter();

int main() {

    //testSpeed();
    //testLength();
    //testUltraSonicSensor();
    //testSensorData();
    //testDist();
    testDataPlotter();

    /*

    apk::DataPlotter sub1, sub2;

    manipulateData m1;
    m1.addSubscriber(&sub1);
    m1.addSubscriber(&sub2);
    m1.forEach();
    m1.accumulate();

    int accumulatedId = m1();
    std::cout << std::endl;
    std::cout << accumulatedId;

     */
    return 0;
}

void testDist(){

    apk::Distributor dist;

    apk::DataPlotter sub1(20), sub2(20);

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an Imu sensor
    imu = new apk::Imu<float>;

    apk::Sensor* ultraSonicSensor;
    ultraSonicSensor = new apk::UltraSonicSensor;
    auto ultraSonicSensorPtr = (apk::UltraSonicSensor*) ultraSonicSensor;

    dist.addSensor(ultraSonicSensor);
    dist.connectSensor(ultraSonicSensor);
    dist.connectToSensor(&sub1, ultraSonicSensor);
    dist.connectToSensor(&sub1, ultraSonicSensor);



    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.connectToSensor(&sub1, imu);
    // Connect to the sensor
    //imu->connect();

    // Let the Imu thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.connectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.removeSubscriber(&sub2);
    dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    ultraSonicSensorPtr->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;


/*
    apk::DataPlotter sub3, sub4;

    manipulateData m1, m2;
    m1.addSubscriber(&sub1);
    m1.addSubscriber(&sub2);

    m1.forEach();
    m1.accumulate();
    m1.writeNumberOfObjectsOrAmountOfSubscribers(2.5);

    //std::cout << std::endl;
*/






}

void testLength() {
    using namespace apk::literals;

    auto x1 = 10.0_km;
    auto x2 = 20.0_mi;
    auto x3 = 15.0_cm;
    auto x4 = 10_m;
    auto x5 = 10_m - 15_m;

    auto total = x1 + x2 + x3 + x4 - 115.0_m;

    std::cout << "Km:" << x1.kilometers() << std::endl;
    std::cout << "Mi:" << x1.miles() << std::endl << std::endl;

    std::cout << "MILES: " << x2.miles() << std::endl;
    std::cout << "Km: " << x2.kilometers() << std::endl << std::endl;

    std::cout << "Total miles: " << total.miles() << std::endl;
    std::cout << "Total km: " << total.kilometers() << std::endl;
    std::cout << "x4 m: " << x4.meters() << std::endl;

    auto length = 5_m;
    std::cout << "Length object: " << length << std::endl;
    //std::cout << "Length" << 5_m << std::endl; // Can't use << since 5_m is prvalue.
}

void testSpeed(){
    using namespace apk::literals;

    auto length = 5_m;
    auto duration = std::chrono::seconds(2);

    auto speed = length/duration;

    std::cout << "Speed calculated from length of " << length << " over a duration of " << duration.count() << "s. : "<< speed << std::endl;

    auto s1 = 5_mPs + 5.0_mPs;
    std::cout << "Speed object: " << s1 << std::endl; // s1 is an xvalue
    //std::cout << "Speed difference object: " << 5_mPs + 5_mPs - 2_mPs << std::endl; // Again prvalue.
}

void testUltraSonicSensor(){

    using namespace std::literals;
    typedef apk::UltraSonicSensor::ReturnType UltraSonicSensorDataType;
    typedef apk::UltraSonicSensor::SignalType UltraSonicSensorSignal;

    struct printLength{
        void operator()(UltraSonicSensorDataType length){
            std::cout << "Length in meters: " << length.meters() << std::endl;
        }
    };

    UltraSonicSensorSignal sig;

    apk::UltraSonicSensor ultraSonicSensor(sig);

    sig.connect(printLength());

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);

    ultraSonicSensor.disconnect();
    ultraSonicSensor.setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(1000ms);

    ultraSonicSensor.connect();
    std::this_thread::sleep_for(5000ms);
    ultraSonicSensor.disconnect();
    std::this_thread::sleep_for(1000ms);
}

void testSensorData(){

    int arr[24] = {0};
    for(int i = 0; i<24; ++i)
        arr[i] = i;
    apk::SensorData<int, 24> s(arr);
    apk::SensorData<int, 24> s2(s);
    apk::SensorData<int, 24> s3;

    for(int i = 0; i<24; ++i)
        s3.push_back(i);
    //std::cout << s << " size: " << s.size() << std::endl;
    //std::cout << s2 << " size: " << s2.size() << std::endl;
    //std::cout << s3 << " size: " << s3.size() << std::endl;

    int index = 0;
    int arr2[24] = {};
    while(s3.size() != 0){
        size_t a = s3.size();
        arr2[0] = s3.pop();
        if(index%2 == 0)
            s3.push_back(index);
        std::cout << arr2[0] << ", ";
        index++;
    }
    //std::cout << s3 << " size: " << s3.size() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}

void testDataPlotter(){
    apk::Distributor dist;

    apk::DataPlotter sub1(1), sub2(10);
    sub1.startLoop();

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an Imu sensor
    imu = new apk::Imu<float>;

    apk::Sensor* ultraSonicSensor;
    ultraSonicSensor = new apk::UltraSonicSensor;
    auto ultraSonicSensorPtr = (apk::UltraSonicSensor*) ultraSonicSensor;

    dist.addSensor(ultraSonicSensor);
    dist.connectSensor(ultraSonicSensor);
    dist.connectToSensor(&sub1, ultraSonicSensor);
    dist.connectToSensor(&sub1, ultraSonicSensor);



    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.connectToSensor(&sub1, imu);
    // Connect to the sensor
    //imu->connect();

    // Let the Imu thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.connectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.removeSubscriber(&sub2);
    dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    ultraSonicSensorPtr->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;
}