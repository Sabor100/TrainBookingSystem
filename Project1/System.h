#ifndef SYSTEM_H
#define SYSTEM_H

#include "FirstClass.h"
#include "SecondClass.h"
#include <vector>
#include <memory>
#include <string>
#include "Ticket.h"
#include "Train.h"

using namespace std;

class System {
private:
    std::vector<std::unique_ptr<Ticket>> tickets;
    std::vector<std::unique_ptr<Train>> trains;

    void addTrain();
    void addTicket();
    void showAllBookings() const;
    void searchPassenger() const;
    void saveBookingsToFile(const std::string& fileName) const;
    void loadBookingsFromFile(const std::string& fileName);

public:
    System();
    ~System();
    void run(); // Kör meny
};

#endif