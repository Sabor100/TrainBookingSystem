#include "Ticket.h"

Ticket::Ticket(int ticketNr, std::unique_ptr<Passenger> passenger, const Train& train)
    : ticketNr(ticketNr), passenger(std::move(passenger)), train(train) {
}

Ticket::~Ticket() {}

int Ticket::getTicketNr() const {
    return ticketNr;
}

Passenger* Ticket::getPassenger() const {
    return passenger.get();
}
const Train& Ticket::getTrain() const {
    return train;
}
std::string Ticket::description() const {
    return "Ticket Number: " + std::to_string(ticketNr) +
        ", Passenger " + passenger->description() +
        ", Train Number: " + std::to_string(train.getTrainNr()) +
        ", Destination: " + train.getDestination();
}