#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include "TrainCarriage.h"

class Train {
private:
    int trainNr;
    std::string destination;
    TrainCarriage carriage; 

public:
    Train();
    Train(int trainNr, const std::string& destination);
    ~Train();

    int getTrainNr() const;
    std::string getDestination() const;

    
    bool bookSeat(int change = -1);
    int getAvailableSeats() const;
    void setAvailableSeats(int seats); 
};

#endif
