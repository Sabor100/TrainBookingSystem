#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include "TrainCarriage.h"

class Train {
private:
    int trainNr;
    std::string destination;
    std::vector<TrainCarriage*> carriages;

public:
    Train(int trainNr, const std::string& destination);
    ~Train();

    int getTrainNr() const;
    std::string getDestination() const;
    void addCarriage(const TrainCarriage& carriage);
};

#endif