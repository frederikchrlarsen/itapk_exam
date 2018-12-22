//
// Created by frederik on 12/21/18.
//

#ifndef ITAPK_EXAM_DISTRIBUTOR_H
#define ITAPK_EXAM_DISTRIBUTOR_H


#include "Subscriber.h"
#include "Sensor.h"
#include <list>

namespace apk{

template <class T>
class Distributor{

public:
    void test(){

    }

private:
    std::list<apk::Sensor<int>*> sensor;

    std::list<apk::Subscriber*> subscriber;


};
}

#endif //ITAPK_EXAM_DISTRIBUTOR_H
