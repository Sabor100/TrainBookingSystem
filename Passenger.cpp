#include "Passenger.h"

Passenger::Passenger(string name, string ssn, int seatNr)
    : name(name), ssn(ssn), seatNr(seatNr) {
}

Passenger::Passenger() : name(""), ssn(""), seatNr(0) {}

Passenger::~Passenger() {}

void Passenger::setName(string name) {
    this->name = name;
}

string Passenger::getName() const {
    return this->name;
}

void Passenger::setSsn(string ssn) {
    this->ssn = ssn;
}

string Passenger::getSsn() const {
    return this->ssn;
}

void Passenger::setSeatNr(int seatNr) {
    this->seatNr = seatNr;
}

int Passenger::getSeatNr() const {
    return this->seatNr;
}