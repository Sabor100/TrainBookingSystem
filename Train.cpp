#include "Train.h"

Train::Train() : trainNr(0), destination("") {

}
Train::Train(int trainNr, const std::string& destination)
    : trainNr(trainNr), destination(destination) {
}

Train::~Train() {
  
}

int Train::getTrainNr() const {
    return trainNr;
}

std::string Train::getDestination() const {
    return destination;
}

bool Train::bookSeat(int change) {
    return carriage.bookSeat(change);
}

int Train::getAvailableSeats() const {
    return carriage.getAvailableSeats();
}

void Train::setAvailableSeats(int seats) {
    carriage.setAvailableSeats(seats);
}
