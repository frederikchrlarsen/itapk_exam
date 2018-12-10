//
// Created by frederik on 12/10/18.
//

#ifndef ITAPK_EXAM_SENSOR_H
#define ITAPK_EXAM_SENSOR_H

#include <ostream>

namespace apk{


    template <class T>
    class Sensor {

        explicit Sensor(T min, T max);

        virtual void read();

    };

    template<class T>
    Sensor<T>::Sensor(T min, T max) {

    }

    template<class T>
    void Sensor<T>::read() {

    }


}
#endif //ITAPK_EXAM_SENSOR_H
