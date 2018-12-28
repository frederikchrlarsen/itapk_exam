//
// Created by frederik on 12/10/18.
//

#ifndef ITAPK_EXAM_SENSOR_H
#define ITAPK_EXAM_SENSOR_H

#include <ostream>
#include <functional>
#include <boost/any.hpp>
namespace apk{


class Sensor {

public:
    explicit Sensor() = default;

    virtual std::string test(){
        return __PRETTY_FUNCTION__;
    };

    virtual void addCallback(std::function<void(boost::any)>) = 0;

    virtual void connect() = 0;

    virtual void disconnect() = 0;

protected:

};

}
#endif //ITAPK_EXAM_SENSOR_H
