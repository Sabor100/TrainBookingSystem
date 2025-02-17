#ifndef TICKET_H
#define TICKET_H

#include <memory>
#include "Passenger.h"
#include "Train.h"

class Ticket {
private:
    int ticketNr;
    std::unique_ptr<Passenger> passenger;
    Train train;

public:
    Ticket(int ticketNr, std::unique_ptr<Passenger> passenger, const Train& train);
    ~Ticket();

    int getTicketNr() const;
    Passenger* getPassenger() const;
    std::string description() const;
    const Train& getTrain() const; 
};

#endif