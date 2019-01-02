//
// Created by frederik on 12/10/18.
//

#ifndef ITAPK_EXAM_SENSOR_H
#define ITAPK_EXAM_SENSOR_H

#include <ostream>
#include <functional>
#include <boost/any.hpp>
#include <boost/signals2/signal.hpp>

namespace apk{
    class Sensor {

        public:

            enum SensorType{
                IMU,
                ULTRASONIC
            };

            explicit Sensor() = default;

            virtual std::string test(){
                return __PRETTY_FUNCTION__;
            };

            virtual SensorType getSensorType() const = 0;

            virtual void connect() {
                connected = true;
            }

            void disconnect() {
                connected = false;
            }

            bool isConnected(){
                return connected;
            }

        protected:
            bool connected = false;
    };
}

#endif //ITAPK_EXAM_SENSOR_H
