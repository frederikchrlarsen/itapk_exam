// Created by Jens on 28-12-2018.
//

#include <Sensor.h>
#include <Subscriber.h>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <numeric>
#include <cstdio>
#include <cstdlib>

#ifndef ITAPK_EXAM_MANIPULATEDATA_H
#define ITAPK_EXAM_MANIPULATEDATA_H


class manipulateData{

public:

    //Functor

    int operator ()()
    {
        return  accumulatedId;
    };

    void addSubscriber(apk::Subscriber* subscriber);
    void removeSubscriber(apk::Subscriber* subscriber);

    //bruger std::for_each med lambda-expression til at skrive alle ikke-konverterede boost ID'er ud
    void forEach();

    //bruger std::transform for at sætte det nuværende manipulateData-objekt lig med det modtagne
    void transform(manipulateData *man_);

    //Gør som transform() uden at bruge lambda expression
    void copy(manipulateData *man_);

    //Bruger boost::function og boost::bind for at sætte et en funktion til at kalde forEach();
    void bind_to_for_each();

    //Tager boost ID'erne i tilkoblede subscribers og lægger dem sammen til en enkelt integer (accumulatedID).
    //Bruger undervejs transformAllIDsToString
    void accumulate();

    //Konverterer ID'er for alle tilkoblede subscribers til strings
    void transformAllIDsToString();

    //Konverterer ID'er for alle tilkoblede subscribers til strings men lægger dem ikke sammen undervejs
    void transformIdsToString();

    //Ikke implementeret
    void clamp();

private:

    int accumulatedId = 0;
    std::list<std::string> idsInString;
    std::list<std::string> checkAccumulation;
    std::list<apk::Subscriber*> subscriber;
    std::vector<int> VectorOfNumbersInId;

};


#endif //ITAPK_EXAM_DISTRIBUTOR_H