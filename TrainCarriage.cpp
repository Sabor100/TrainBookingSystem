#include "TrainCarriage.h"

TrainCarriage::TrainCarriage() : maxSeats(50), availableSeats(50) {} 

TrainCarriage::~TrainCarriage() {}


int TrainCarriage::getMaxSeats() const {
    return maxSeats;
}

int TrainCarriage::getAvailableSeats() const {
    return availableSeats;
}


void TrainCarriage::setMaxSeats(int maxSeats) {
    this->maxSeats = maxSeats;
    this->availableSeats = maxSeats; 
}

void TrainCarriage::setAvailableSeats(int availableSeats) {
    this->availableSeats = availableSeats;
}


bool TrainCarriage::bookSeat() {
    if (availableSeats > 0) {
        --availableSeats;
        return true;
    }
    return false; 
}

bool TrainCarriage::bookSeat(int change) {
    if (change < 0 && availableSeats > 0) { 
        availableSeats += change;
        return true;
    }
    else if (change > 0) {
        availableSeats += change;
        if (availableSeats > maxSeats) {
            availableSeats = maxSeats;
        }
        return true;
    }
    return false; // No seats left 
}

