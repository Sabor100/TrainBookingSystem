#include "Train.h"

Train::Train(int trainNr, const std::string& destination)
    : trainNr(trainNr), destination(destination) {
}

Train::~Train() {
    for (auto c : carriages) {
        delete c;
    }
}

int Train::getTrainNr() const {
    return trainNr;
}

std::string Train::getDestination() const {
    return destination;
}

void Train::addCarriage(const TrainCarriage& carriage) {
    carriages.push_back(new TrainCarriage(carriage));
}