//
// Created by Tais on 25/12/2018.
//

#ifndef ITAPK_EXAM_UNITS_H
#define ITAPK_EXAM_UNITS_H

// REF: Inspiration found on https://arne-mertz.de/2016/10/modern-c-features-user-defined-literals/
// TODO: template or other fix to support more inputs.
#include <boost/static_assert.hpp>

class Length {
public:

    enum unit{
        CM,
        METER,
        KILOMETERS,
        MILES
    };

    template <class T>
    Length(T length, Length::unit unit){
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

    long double cm(){
        return length_m*100.0;
    }

    long double meters(){
        return length_m;
    }

    long double kilometers(){
        return length_m/1000.0;
    }

    long double miles(){
        return length_m*meterToMilesFactor;
    }

    Length operator+(Length rh){
        return Length{length_m + rh.meters(), Length::METER};
    }

    Length operator-(Length rh){
        return Length{length_m - rh.meters(), Length::METER};
    }

    // Following would allow negative units but what is -10m?
    //Length operator-(){
    //    return Length{-length_m, Length::METER};
    //}

private:
    long double length_m;
    static constexpr double milesToMeterFactor = 1609.344;
    static constexpr double meterToMilesFactor = 0.000621371192;
};

// Long double for comma numbers
Length operator"" _m (long double arg)
{
    return Length{arg, Length::METER};
}

Length operator"" _cm ( long double arg )
{
    return Length{arg, Length::CM};
}

Length operator "" _km(long double arg) {
    return Length{arg, Length::KILOMETERS};
}

Length operator "" _mi(long double arg) {
    return Length{arg, Length::MILES};
}

// Unsigned long long for integers
Length operator"" _m (unsigned long long arg)
{
    return Length{arg, Length::METER};
}

Length operator"" _cm (unsigned long long arg )
{
    return Length{arg, Length::CM};
}

Length operator "" _km(unsigned long long arg) {
    return Length{arg, Length::KILOMETERS};
}

Length operator "" _mi(unsigned long long arg) {
    return Length{arg, Length::MILES};
}

void testLength(){
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
}



#endif //ITAPK_EXAM_UNITS_H
