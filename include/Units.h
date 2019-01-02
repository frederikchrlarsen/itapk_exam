//
// Created by Tais on 25/12/2018.
//

#ifndef ITAPK_EXAM_UNITS_H
#define ITAPK_EXAM_UNITS_H

// REF: Inspiration found on https://arne-mertz.de/2016/10/modern-c-features-user-defined-literals/
// TODO: template or other fix to support more inputs.
#include <boost/static_assert.hpp>
#include <iostream>
#include <chrono>

namespace apk{
    class Speed;

    class Length {
    public:

        enum unit{
            CM,
            METER,
            KILOMETERS,
            MILES
        };

        Length():length_m(0){

        }

        template<class T>
        Length(T length, apk::Length::unit unit) {
            switch (unit) {
                case CM:
                    length_m = length/100.0;
                    break;
                case METER:
                    length_m = length;
                    break;
                case KILOMETERS:
                    length_m = length*1000.0;
                    break;
                case MILES:
                    length_m = length*milesToMeterFactor;
                    break;
            }
        }

        long double cm() const;

        long double meters() const;

        long double kilometers() const;

        long double miles() const;

        Length operator+(Length rh) const;

        Length operator-(Length rh) const;

        apk::Speed operator/(std::chrono::seconds seconds) const;

        friend std::ostream& operator<< ( std::ostream& o, apk::Length& length ){
            return o << length.meters() << "m";
        }

    private:
        long double length_m;
        static constexpr double milesToMeterFactor = 1609.344;
        static constexpr double meterToMilesFactor = 0.000621371192;
    };

    class Speed{
    public:
        enum unit{
            MPS
        };

        template<class T>
        Speed(T speed, apk::Speed::unit unit) {
            switch (unit) {
                case MPS:
                    speed_mPs = speed;
                    break;
            }
        }

        long double mPs() const;

        Speed operator+(Speed rh) const;

        Speed operator-(Speed rh) const;

        friend std::ostream& operator<< ( std::ostream& o, apk::Speed& speed ){
            return o << speed.mPs() << "m";
        }

    private:
        long double speed_mPs;
    };

    inline namespace literals{
        Length operator"" _m (long double arg);

        Length operator"" _cm (long double arg);

        Length operator "" _km(long double arg);

        Length operator "" _mi(long double arg);

        Speed operator"" _mPs (long double arg);

        // Unsigned long long for integers
        Length operator"" _m (unsigned long long arg);

        Length operator"" _cm (unsigned long long arg);

        Length operator "" _km(unsigned long long arg);

        Length operator "" _mi(unsigned long long arg);

        Speed operator"" _mPs (unsigned long long arg);
    }
}

#endif //ITAPK_EXAM_UNITS_H
