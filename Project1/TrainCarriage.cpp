#include "TrainCarriage.h"

TrainCarriage::TrainCarriage()
    : maxSeats(0), seats(0), availableSeatsNr(0), goods(0), maxWeight(0.0), material(""), restRoomAvailable(false), tableNr(0) {
}

TrainCarriage::TrainCarriage(int maxSeats, int goods, float maxWeight, const string& material, bool restRoomAvailable, int tableNr)
    : maxSeats(maxSeats), goods(goods), maxWeight(maxWeight), material(material), restRoomAvailable(restRoomAvailable), tableNr(tableNr) {
    this->seats = 0;
    this->availableSeatsNr = maxSeats;
}

TrainCarriage::~TrainCarriage() {}


void TrainCarriage::setMaxSeats(int maxSeats) {
    this->maxSeats = maxSeats;
    this->availableSeatsNr = maxSeats - this->seats; // Update available seats
}

void TrainCarriage::setSeats(int seats) {
    this->seats = seats;
    this->availableSeatsNr = maxSeats - seats; // Update available seats
}

void TrainCarriage::setAvailableSeatsNr(int availableSeatsNr) {
    this->availableSeatsNr = availableSeatsNr;
}

void TrainCarriage::setGoods(int goods) {
    this->goods = goods;
}

void TrainCarriage::setMaxWeight(float maxWeight) {
    this->maxWeight = maxWeight;
}

void TrainCarriage::setMaterial(const string& material) {
    this->material = material;
}

void TrainCarriage::setRestRoomAvailable(bool restRoomAvailable) {
    this->restRoomAvailable = restRoomAvailable;
}

void TrainCarriage::setTableNr(int tableNr) {
    this->tableNr = tableNr;
}

// Getters
int TrainCarriage::getMaxSeats() const {
    return maxSeats;
}

int TrainCarriage::getSeats() const {
    return seats;
}

int TrainCarriage::getAvailableSeatsNr() const {
    return availableSeatsNr;
}

int TrainCarriage::getGoods() const {
    return goods;
}

float TrainCarriage::getMaxWeight() const {
    return maxWeight;
}

string TrainCarriage::getMaterial() const {
    return material;
}

bool TrainCarriage::getRestRoomAvailable() const {
    return restRoomAvailable;
}

int TrainCarriage::getTableNr() const {
    return tableNr;
}

