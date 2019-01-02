

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

    manipulateData()
    {
        amountOfManipulateDataObjects++;
    }

    ~manipulateData()
    {
        amountOfManipulateDataObjects--;
    }

    int operator ()(int variant) const
    {
        return  amountOfManipulateDataObjects -1;
    };

    int operator()(std::string & variant) const
    {
        return amountOfAttachedSubscribers;
    }

    void addSubscriber(apk::Subscriber* subscriber);
    void removeSubscriber(apk::Subscriber* subscriber);

    //bruger std::for_each med lambda-expression til at skrive alle ikke-konverterede boost ID'er ud
    void forEach();

    //Gør som transform() uden at bruge lambda expression
    void copy(manipulateData *man_);

    //Bruger boost::function og boost::bind for at sætte et en funktion til at kalde forEach();
    void bind_to_for_each();

    //Tager boost ID'erne i tilkoblede subscribers og lægger dem sammen til en enkelt integer (accumulatedID).
    //Bruger undervejs transformAllIDsToString
    void accumulate();

    //Konverterer ID'er for alle tilkoblede subscribers til strings
    void transformAllIDsToString(std::list<std::string> & arg);


    int getAccumulatedID()
    {
        return accumulatedId;
    }

    static int amountOfManipulateDataObjects;
    static int amountOfAttachedSubscribers;

    //Bruger boost::variant og boost:apply_visitor for at vælge mellem operators()

    template<class T> int writeNumObjectsOrAmountOfSubscribers(T x)
    {
        manipulateData m1;
        boost::variant< int, std::string > IDvariantInType(x);
        int result = boost::apply_visitor( m1, IDvariantInType );
        std::cout << result << std::endl;
        return result;
    }

private:

    int accumulatedId = 0;
    std::list<apk::Subscriber*> subscriber;

};


#endif //ITAPK_EXAM_DISTRIBUTOR_H

