#ifndef SECONDCLASS_H
#define SECONDCLASS_H

#include "Passenger.h"

class SecondClass : public Passenger {
private:
    int baggageAllowances;
    bool mealOption;

public:
    SecondClass();
    SecondClass(int baggageAllowances, bool mealOption, string name, string ssn, int seatNr);
    ~SecondClass();

    void setBaggageAllowances(int baggageAllowances);
    int getBaggageAllowances() const;
    void setMealOption(bool mealOption);
    bool getMealOption() const;

    string description() const override;
};

#endif