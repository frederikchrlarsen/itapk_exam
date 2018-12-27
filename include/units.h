//
// Created by Tais on 25/12/2018.
//

#ifndef ITAPK_EXAM_UNITS_H
#define ITAPK_EXAM_UNITS_H

// REF: Inspiration found on http://se.ethz.ch/~meyer/publications/OTHERS/scott_meyers/dimensions.pdf

class Length {
public:
    enum unit{
        CM,
        METER,
        KILOMETERS,
        MILES
    };

    Length(long double length, Length::unit unit){
        switch (unit) {
            case CM:
                length_m = length/100;
                break;
            case METER:
                length_m = length;
                break;
            case KILOMETERS:
                length_m = length*1000;
                break;
            case MILES:
                length_m = length*milesToMeterFactor;
                break;
        }
    }

    long double getLengthMeter(){
        return length_m;
    }

    long double getLengthKm(){
        return length_m/1000;
    }

    long double getLengthMiles(){
        return length_m*meterToMilesFactor;
    }

    Length operator+(Length rh){
        return Length{rh.getLengthMeter()+length_m, Length::METER};
    }

private:
    long double length_m;
    static constexpr double milesToMeterFactor = 1609.344;
    static constexpr double meterToMilesFactor = 0.000621371192;
};

Length operator"" _m ( long double arg )
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

//// used as conversion
//constexpr long double operator"" _deg ( long double deg )
//{
//    return deg*3.141592/180;
//}
//
////used with custom type
//struct mytype
//{
//    mytype ( unsigned long long m):m(m){}
//    unsigned long long m;
//};
//
//mytype operator"" _mytype ( unsigned long long n )
//{
//    return mytype(n);
//}
//
//// used for sideeffects
//void operator"" _print ( const char* str )
//{
//    std::cout << str;
//}
//
//unsigned long long binHelper(unsigned long long value)
//{
//    std::cout << "binHelper! " << value << std::endl;
//    return value ? binHelper(value/10) << 1 | value%10 : 0;
//}

void testLength(){
    auto x1 = 10.0_km;
    auto x2 = 20.0_mi;
    auto x3 = 15.0_cm;

    auto total = x1 + x2 + x3 + 115.0_m;

    std::cout << "Km:" << x1.getLengthKm() << std::endl;
    std::cout << "Mi:" << x1.getLengthMiles() << std::endl << std::endl;

    std::cout << "MILES: " << x2.getLengthMiles() << std::endl;
    std::cout << "Km: " << x2.getLengthKm() << std::endl << std::endl;

    std::cout << "Total miles: " << total.getLengthMiles() << std::endl;
    std::cout << "Total km: " << total.getLengthKm() << std::endl;
}

#endif //ITAPK_EXAM_UNITS_H
