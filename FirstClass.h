#ifndef FIRSTCLASS_H
#define FIRSTCLASS_H

#include "Passenger.h"

class FirstClass : public Passenger {
private:
    string seatType;
    string breakfast;

public:
    FirstClass();
    FirstClass(string seatType, string breakfast, string name, string ssn, int seatNr);
    ~FirstClass();

    void setSeatType(string seatType);
    string getSeatType() const;
    void setBreakfast(string breakfast);
    string getBreakfast() const;

    string description() const override;
};

#endif