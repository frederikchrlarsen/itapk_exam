//
// Created by frederik on 12/30/18.
//

#include <Units.h>

#include "Units.h"

long double apk::Length::cm() const {
    return length_m*100.0;
}

long double apk::Length::meters() const {
    return length_m;
}

long double apk::Length::kilometers() const {
    return length_m/1000.0;
}

long double apk::Length::miles() const {
    return length_m*meterToMilesFactor;
}

apk::Length apk::Length::operator+(apk::Length rh) const {
    return Length{length_m + rh.meters(), apk::Length::METER};
}

apk::Length apk::Length::operator-(apk::Length rh) const {
    return Length{length_m - rh.meters(), Length::METER};
}

apk::Length apk::literals::operator ""_m(long double arg) {
    return Length{arg, apk::Length::METER};
}

apk::Length apk::literals::operator ""_cm(long double arg) {
    return Length{arg, apk::Length::CM};
}

apk::Length apk::literals::operator ""_km(long double arg) {
    return Length{arg, apk::Length::KILOMETERS};
}

apk::Length apk::literals::operator ""_mi(long double arg) {
    return Length{arg, apk::Length::MILES};
}

apk::Length apk::literals::operator ""_m(unsigned long long arg) {
    return Length{arg, apk::Length::METER};
}

apk::Length apk::literals::operator ""_cm(unsigned long long arg) {
    return Length{arg, apk::Length::CM};
}

apk::Length apk::literals::operator ""_km(unsigned long long arg) {
    return Length{arg, apk::Length::KILOMETERS};
}

apk::Length apk::literals::operator ""_mi(unsigned long long arg) {
    return Length{arg, apk::Length::MILES};
}
