#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
private:
    string name;
    string ssn;
    int seatNr;

public:
    Passenger(string name, string ssn, int seatNr);
    Passenger();
    virtual ~Passenger();

    void setName(string name);
    string getName() const;
    void setSsn(string ssn);
    string getSsn() const;
    void setSeatNr(int seatNr);
    int getSeatNr() const;

    virtual string description() const = 0; // Pure virtual function
};

#endif
