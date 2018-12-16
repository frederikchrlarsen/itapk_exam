//
// Created by frederik on 12/10/18.
//

#ifndef ITAPK_EXAM_SENSOR_H
#define ITAPK_EXAM_SENSOR_H

#include <ostream>
#include <functional>

namespace apk{


template <class T>
class Sensor {

public:
    explicit Sensor();

    virtual void read();

    virtual std::string test();

    virtual void connect() = 0;

    virtual void disconnect() = 0;

protected:

};

template<class T>
Sensor<T>::Sensor() {
}

template<class T>
void Sensor<T>::read() {

}

template<class T>
std::string Sensor<T>::test() {

    return __PRETTY_FUNCTION__;

}

}
#endif //ITAPK_EXAM_SENSOR_H
