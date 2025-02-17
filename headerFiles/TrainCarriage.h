#ifndef TRAINCARRIAGE_H
#define TRAINCARRIAGE_H

class TrainCarriage {
private:
    int maxSeats;
    int availableSeats;

public:
    TrainCarriage(); 
    ~TrainCarriage(); 

    
    int getMaxSeats() const;
    int getAvailableSeats() const;

    
    void setMaxSeats(int maxSeats);
    void setAvailableSeats(int availableSeats);

    
    bool bookSeat();
    bool bookSeat(int change = -1); 
};

#endif
