#include "SecondClass.h"

SecondClass::SecondClass() {}

SecondClass::SecondClass(int baggageAllowances, bool mealOption, string name, string ssn, int seatNr)
    : Passenger(name, ssn, seatNr), baggageAllowances(baggageAllowances), mealOption(mealOption) {
}

SecondClass::~SecondClass() {}

void SecondClass::setBaggageAllowances(int baggageAllowances) {
    this->baggageAllowances = baggageAllowances;
}

int SecondClass::getBaggageAllowances() const {
    return this->baggageAllowances;
}

void SecondClass::setMealOption(bool mealOption) {
    this->mealOption = mealOption;
}

bool SecondClass::getMealOption() const {
    return this->mealOption;
}

string SecondClass::description() const {
    return "Type: Second Class, Name: " + getName() + ", SSN: " + getSsn() + ", Seat Number: " + to_string(getSeatNr()) + ", Baggage Allowances: " + to_string(baggageAllowances) +", Meal Option: " + (mealOption ? "Yes" : "No");
}