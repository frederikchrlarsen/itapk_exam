#include <iostream>
#include <functional>
#include <chrono>
#include "Subscriber.h"
#include "Distributor.h"
#include "DataPlotter.h"
#include "ImuSensor.h"
#include "Sensor.h"
#include "UltraSonicSensor.h"
#include "manipulateData.h"
#include "SensorData.h"
#include "Regulator.h"

void testRegulator();

void testDist();

void testLength();

void testUltraSonicSensor();

void testSpeed();

void testSensorData();

void testDataPlotter();

void testSystem();

void manipulateData_();

void testImuSensor();

int main() {

    //testSpeed();
    //testLength();
    //testUltraSonicSensor();
    testImuSensor();
    //testSensorData();
    //testDist();
    //testDataPlotter();
    //testSystem();
    //testRegulator();

    //manipulateData_();



    return 0;
}
void testSystem(){
    apk::Distributor dist;

    apk::DataPlotter dataPlotter(24);
    dataPlotter.startLoop();

    // Instantiate an ImuSensor sensor
    auto* imu = new apk::ImuSensor;

    // Instantiate an UltraSonic sensor
    auto* ultraSonicSensor = new apk::UltraSonicSensor;

    dist.addSensor(ultraSonicSensor);
    // Set options
    ultraSonicSensor->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_5);
    ultraSonicSensor->setDistanceType(apk::UltraSonicSensor::DistanceType::METER);

    dist.connectSensor(ultraSonicSensor);
    dist.connectToSensor(&dataPlotter, ultraSonicSensor);
    //dist.connectToSensor(&dataPlotter, ultraSonicSensor);

    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.connectToSensor(&dataPlotter, imu);

    // Let program run a bit before changing sampletime.
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    ultraSonicSensor->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.connectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.removeSubscriber(&sub2);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500*7));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;
}

void testDist(){

    apk::Distributor dist;

    apk::DataPlotter sub1(20), sub2(20);

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an ImuSensor sensor
    imu = new apk::ImuSensor;

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

    // Let the ImuSensor thread run and disconnect after
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

    apk::DataPlotter sub1(24), sub2(10);
    sub1.startLoop();

    // The sensor interface
    apk::Sensor* imu;
    // Instantiate an ImuSensor sensor
    imu = new apk::ImuSensor;

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

    // Let the ImuSensor thread run and disconnect after
    ultraSonicSensorPtr->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.connectToSensor(&sub2, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.removeSubscriber(&sub2);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    dist.disconnectSensor(imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500*7));

    //imu->disconnect();

    std::cout << imu->test() << std::endl;
}

void testRegulator() {
    apk::Distributor dist;

    apk::Regulator regulator(2);
    regulator.run();

    std::this_thread::sleep_for(std::chrono::milliseconds(3100));

    apk::DataPlotter dataPlotter(24);

    // Instantiate an ImuSensor sensor
    auto *imu = new apk::ImuSensor;

    // Instantiate an UltraSonic sensor
    auto *ultraSonicSensor = new apk::UltraSonicSensor;

    dist.addSensor(ultraSonicSensor);
    // Set options
    ultraSonicSensor->setSampleRate(apk::UltraSonicSensor::SampleRate::HZ_5);
    ultraSonicSensor->setDistanceType(apk::UltraSonicSensor::DistanceType::METER);

    dist.connectSensor(ultraSonicSensor);
    dist.connectToSensor(&regulator, ultraSonicSensor);
    //dist.connectToSensor(&dataPlotter, ultraSonicSensor);

    dist.addSensor(imu);
    dist.connectSensor(imu);
    dist.connectToSensor(&regulator, imu);
    std::this_thread::sleep_for(std::chrono::milliseconds(3100));
}

void manipulateData_()
{

    std::cout << "Tilføjer subscribers og mData objekter" << std::endl;
    apk::DataPlotter sub1, sub2, sub3, sub4, sub5, sub6;
    manipulateData m1, m2;
    m1.addSubscriber(&sub1);
    m1.addSubscriber(&sub2);
    m2.addSubscriber(&sub3);
    m2.addSubscriber(&sub4);

    //Boost ID for m1 med subscribers sub3 og sub4 tilføjet

    std::cout << "Boost ID for sub1 og sub2" << std::endl;
    m1.forEach();

    std::cout << "Akkumuleret ID for m1" << std::endl;
    m1.accumulate();

    std::cout << "Boost ID for sub3 og sub4" << std::endl;
    m2.forEach();

    std::cout << "Akkumuleret ID for m2" << std::endl;
    m2.accumulate();

    std::cout << std::endl << std::endl;

    std::cout << "m2 kopieres til m1" << std::endl;
    m1.copy(&m2);
    m2.forEach();
    m2.accumulate();

    std::cout << "Udskrivning af totale antal mData objekter" << std::endl;
    m1.writeNumObjectsOrAmountOfSubscribers(2.5);
    std::cout << std::endl;

    std::cout << "Udskrivning af totale antal af subscribers tilkoblet mData objekter" << std::endl;
    m1.writeNumObjectsOrAmountOfSubscribers("hej");

    std::cout << "Tilføjer to nye subscribers til mData1, og laver et nyt mData objekt m3" << std::endl;

    m1.addSubscriber(&sub5);
    m1.addSubscriber(&sub6);
    manipulateData m3;

    std::cout << "Udskrivning af totale antal mData objekter" << std::endl;
    m1.writeNumObjectsOrAmountOfSubscribers(2.5);
    std::cout << std::endl;

    std::cout << "Udskrivning af totale antal af subscribers tilkoblet mData objekter" << std::endl;
    m1.writeNumObjectsOrAmountOfSubscribers("hej");
    std::cout << std::endl;

    std::cout << "For each ved brug af binding" << std::endl;
    m1.bind_to_for_each();
}

void testImuSensor(){

    apk::Distributor dist;

    apk::Regulator sub1(1);
    sub1.run();

    // The sensor interface
    auto imuSensor = new apk::ImuSensor;


    dist.addSensor(imuSensor);
    dist.connectSensor(imuSensor);
    dist.connectToSensor(&sub1, imuSensor);

    // Connect to the sensor
    //imu->connect();

    // Let the ImuSensor thread run and disconnect after
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    imuSensor->setSampleRate(apk::ImuSensor::SampleRate::HZ_10);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    //dist.removeSubscriber(&sub2);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    //dist.disconnectFromSensor(&sub1, ultraSonicSensor);
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    std::this_thread::sleep_for(std::chrono::milliseconds(2500*7));

    //imu->disconnect();


}