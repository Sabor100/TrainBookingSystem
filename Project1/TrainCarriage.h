#ifndef TRAINCARRIAGE_H
#define TRAINCARRIAGE_H

#include <string>

using namespace std;

class TrainCarriage {
private:
    int maxSeats;
    int seats;
    int availableSeatsNr;
    int goods;
    float maxWeight;
    string material;
    bool restRoomAvailable;
    int tableNr;

public:
    TrainCarriage();
    TrainCarriage(int maxSeats, int goods, float maxWeight, const string& material, bool restRoomAvailable, int tableNr);
    ~TrainCarriage();

    // Setters
    void setMaxSeats(int maxSeats);
    void setSeats(int seats);
    void setAvailableSeatsNr(int availableSeatsNr);
    void setGoods(int goods);
    void setMaxWeight(float maxWeight);
    void setMaterial(const string& material);
    void setRestRoomAvailable(bool restRoomAvailable);
    void setTableNr(int tableNr);

    // Getters
    int getMaxSeats() const;
    int getSeats() const;
    int getAvailableSeatsNr() const;
    int getGoods() const;
    float getMaxWeight() const;
    string getMaterial() const;
    bool getRestRoomAvailable() const;
    int getTableNr() const;
};

#endif
