//
// Created by frederik on 12/21/18.
//

#ifndef ITAPK_EXAM_SUBSCRIBER_H
#define ITAPK_EXAM_SUBSCRIBER_H


#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include "sensors/UltraSonicSensor.h"
#include "sensors/Imu.h"

namespace apk{

class Subscriber{

public:
    typedef boost::uuids::uuid idType;

    Subscriber():id_(gen_()){
        std::cout << "Created subscriber: " << boost::uuids::to_string(this->getId()) << std::endl;
    };

    void test(){
        std::cout << boost::uuids::to_string(this->getId()) << std::endl;
    }

    const idType getId() const{
        return id_;
    }

    virtual void imuSensorSignal(Imu::ReturnType data) = 0;

    virtual void ultraSonicSensorSignal(UltraSonicSensor::ReturnType data) = 0;



private:
    boost::uuids::random_generator gen_;
    boost::uuids::uuid id_;
};

}
#endif //ITAPK_EXAM_SUBSCRIBER_H
