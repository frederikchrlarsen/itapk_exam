//
// Created by frederik on 12/21/18.
//

#ifndef ITAPK_EXAM_DISTRIBUTOR_H
#define ITAPK_EXAM_DISTRIBUTOR_H


#include "Subscriber.h"
#include "Sensor.h"
#include <list>
#include <boost/signals2.hpp>
#include "sensors/UltraSonicSensor.h"

namespace apk{
    class Distributor{

    public:
        typedef std::pair<apk::Subscriber*, apk::Sensor*> conMapKeyType;

        typedef std::map<conMapKeyType, boost::signals2::connection> conMapType;

        typedef apk::Sensor* sensorPtrType;

        void connectToSensor(apk::Subscriber* sub, sensorPtrType sensor);

        void disconnectFromSensor(apk::Subscriber* sub, sensorPtrType sensor);

        void addSensor(sensorPtrType sensor);

        void removeSensor(sensorPtrType sensor);

        void connectSensor(sensorPtrType sensor);

        void disconnectSensor(sensorPtrType sensor);

        std::list<sensorPtrType> getSensorList();

    private:

        bool isSensorInList(sensorPtrType sensor);

        std::list<sensorPtrType> sensor_;

        UltraSonicSensor::SignalType ultraSonicSensorSignal_;

        conMapType subSensorConMap_;

    };
}

#endif //ITAPK_EXAM_DISTRIBUTOR_H
