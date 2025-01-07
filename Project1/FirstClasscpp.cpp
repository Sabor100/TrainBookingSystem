#include "FirstClass.h"

FirstClass::FirstClass() {}

FirstClass::FirstClass(string seatType, string breakfast, string name, string ssn, int seatNr)
    : Passenger(name, ssn, seatNr), seatType(seatType), breakfast(breakfast) {
}

FirstClass::~FirstClass() {}

void FirstClass::setSeatType(string seatType) {
    this->seatType = seatType;
}

string FirstClass::getSeatType() const {
    return this->seatType;
}

void FirstClass::setBreakfast(string breakfast) {
    this->breakfast = breakfast;
}

string FirstClass::getBreakfast() const {
    return this->breakfast;
}

string FirstClass::description() const {
    return "Type: First Class, Name: " + getName() + ", SSN: " + getSsn() +
        ", Seat Number: " + to_string(getSeatNr()) + ", Seat Type: " + seatType +
        ", Breakfast: " + breakfast;
}