//
// Created by frederik on 12/21/18.
//

#ifndef ITAPK_EXAM_DISTRIBUTOR_H
#define ITAPK_EXAM_DISTRIBUTOR_H


#include "Subscriber.h"
#include "Sensor.h"
#include <list>
#include <boost/signals2.hpp>
#include <sensors/UltraSonicSensor.h>

namespace apk{
    class Distributor{

    public:
        typedef boost::signals2::signal<void (float)> float_signal;
        typedef std::function<void(boost::any)> float_func;
        typedef apk::Sensor* sensor_ptr;

        //typedef boost::signals2::signal<void (ImuData)> imu_signal;
        //typedef std::function<void(ImuData)> imu_func;


        void test();

        void addSubscriber(apk::Subscriber* subscriber);
        void removeSubscriber(apk::Subscriber* subscriber);
        void subConnectToSensor(apk::Subscriber* sub, sensor_ptr sensor);
        void addSensor(sensor_ptr sensor);
        void removeSensor(sensor_ptr sensor);
        void connectSensor(sensor_ptr sensor);
        void registerSensorCallback(sensor_ptr sensor, const float_func &callback);
        void disconnectSensor(sensor_ptr sensor);
        std::list<sensor_ptr> getSensorList();

    private:
        bool isSensorInList(sensor_ptr sensor);

        std::list<sensor_ptr> sensor;

        std::list<apk::Subscriber*> subscriber;

        UltraSonicSensor::SignalType ultraSonicSensorSignal;

        //float_signal sig;

        //std::vector<boost::signals2::connection> signalList_;

        std::map<apk::Subscriber*, boost::signals2::connection*> subConnectionMap;

    };
}

#endif //ITAPK_EXAM_DISTRIBUTOR_H
