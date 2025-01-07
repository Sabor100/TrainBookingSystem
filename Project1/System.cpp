#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>

System::System() {
    loadBookingsFromFile("bookings.txt");
}

System::~System() {
}

void System::run() {
    int choice = -1; // Initialisera med ett värde som inte är 0

    do {
        std::cout << "\n=== Train Booking System ===\n";
        std::cout << "1. Add a Train\n";
        std::cout << "2. Add a Ticket\n";
        std::cout << "3. Show All Bookings\n";
        std::cout << "4. Search Passenger\n";
        //std::cout << "5. Save Bookings to File\n";
        //std::cout << "6. Load Bookings from File\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Kontrollera om användaren matat in ett ogiltigt värde
        if (std::cin.fail()) {
            std::cin.clear(); // Rensar felstatus
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorera felaktig inmatning
            std::cout << "Invalid input. Please enter a number between 0 and 6.\n";
            continue; // Hoppa över till nästa iteration
        }

        std::cin.ignore(); // Ignorera newline-tecken från inmatningen

        switch (choice) {
        case 1:
            addTrain();
            break;
        case 2:
            addTicket();
            break;
        case 3:
            showAllBookings();
            break;
        case 4:
            searchPassenger();
            break;
        //case 5:
        //    saveBookingsToFile("bookings.txt");
        //    break;
        //case 6:
        //    loadBookingsFromFile("bookings.txt");
        //    break;
        case 0:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 0 and 6.\n";
        }

    } while (choice != 0); // Avsluta om användaren väljer 0
}


void System::addTrain() {
    int trainNr;
    std::string destination;

    std::cout << "Enter train number: ";
    std::cin >> trainNr;
    std::cin.ignore();
    std::cout << "Enter destination: ";
    std::getline(std::cin, destination);

    auto train = std::make_unique<Train>(trainNr, destination);
    trains.push_back(std::move(train));

    std::cout << "Train added successfully!\n";
}

void System::addTicket() {
    if (trains.empty()) {
        std::cout << "No trains available. Please add a train first.\n";
        return;
    }

    int trainNr, seatNr;
    std::string passengerName;
    string ssn;
    int passengerType; // 1 for FirstClass, 2 for SecondClass

    std::cout << "Enter train number: ";
    std::cin >> trainNr;
    std::cin.ignore();

    Train* selectedTrain = nullptr;
    for (const auto& train : trains) {
        if (train->getTrainNr() == trainNr) {
            selectedTrain = train.get();
            break;
        }
    }

    if (!selectedTrain) {
        std::cout << "Train not found.\n";
        return;
    }

    std::cout << "Enter passenger name: ";
    std::getline(std::cin, passengerName);
    std::cout << "Enter passenger SSN (YYMMDDXXXX): ";
    std::getline(std::cin, ssn);
    std::cout << "Enter seat number: ";
    std::cin >> seatNr;
    std::cin.ignore();
    std::cout << "Enter passenger type (1 for FirstClass, 2 for SecondClass): ";
    std::cin >> passengerType;
    std::cin.ignore();

    std::unique_ptr<Passenger> passenger;
    if (passengerType == 1) {
        std::string seatType, breakfast;
        std::cout << "Enter seat type: ";
        std::getline(std::cin, seatType);
        std::cout << "Enter breakfast: ";
        std::getline(std::cin, breakfast);
        passenger = std::make_unique<FirstClass>(seatType, breakfast, passengerName, ssn, seatNr);
    }
    else if (passengerType == 2) {
        int baggageAllowances;
        bool mealOption;
        std::cout << "Enter baggage allowances: ";
        std::cin >> baggageAllowances;
        std::cout << "Enter meal option (1 for Yes, 0 for No): ";
        std::cin >> mealOption;
        passenger = std::make_unique<SecondClass>(baggageAllowances, mealOption, passengerName, ssn, seatNr);
    }
    else {
        std::cout << "Invalid passenger type.\n";
        return;
    }

    auto ticket = std::make_unique<Ticket>(tickets.size() + 1, std::move(passenger), *selectedTrain);
    tickets.push_back(std::move(ticket));
    saveBookingsToFile("bookings.txt");


    std::cout << "Ticket added successfully!\n";
}

void System::showAllBookings() const {
    if (tickets.empty()) {
        std::cout << "No bookings found.\n";
        return;
    }

    for (const auto& ticket : tickets) {
        std::cout << ticket->description() << std::endl;
    }
}

void System::searchPassenger() const {
    std::string name;
    std::cout << "Enter passenger name: ";
    std::getline(std::cin, name);

    for (const auto& ticket : tickets) {
        if (ticket->getPassenger()->getName() == name) {
            std::cout << "Passenger found: " << ticket->description() << std::endl;
            return;
        }
    }
    std::cout << "Passenger not found.\n";
}

void System::saveBookingsToFile(const std::string& fileName) const {
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error: Could not open file " << fileName << " for writing.\n";
        return;
    }

    for (const auto& ticket : tickets) {
        outFile << ticket->description() << "\n";
    }

    outFile.close();
    std::cout << "Bookings saved to " << fileName << ".\n";
}

void System::loadBookingsFromFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error: Could not open file " << fileName << " for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string type, name, seatType, breakfast, destination;
        string ssn;
        int ticketNr, seatNr, baggageAllowances, trainNr;
        bool mealOption;

        // Exempel parsing av en rad från textfilen
        ss.ignore(15); // Ignorera "Ticket Number: "
        ss >> ticketNr;
        ss.ignore(12); // Ignorera ", Passenger: "
        ss.ignore(6);  // Ignorera "Type: "
        ss >> type;

        if (type == "First") {
            ss.ignore(7); // Ignorera "Class, "
            ss.ignore(6); // Ignorera "Name: "
            std::getline(ss, name, ',');
            ss.ignore(5); // Ignorera "SSN: "
            ss >> ssn;
            ss.ignore(13); // Ignorera ", Seat Number: "
            ss >> seatNr;
            ss.ignore(11); // Ignorera ", Seat Type: "
            std::getline(ss, seatType, ',');
            ss.ignore(12); // Ignorera ", Breakfast: "
            std::getline(ss, breakfast, ',');
            ss.ignore(15); // Ignorera ", Train Number: "
            ss >> trainNr;
            ss.ignore(13); // Ignorera ", Destination: "
            std::getline(ss, destination);

            auto passenger = std::make_unique<FirstClass>(seatType, breakfast, name, ssn, seatNr);
            auto train = std::make_unique<Train>(trainNr, destination);
            auto ticket = std::make_unique<Ticket>(ticketNr, std::move(passenger), *train);

            tickets.push_back(std::move(ticket));
        }
        else if (type == "Second") {
            ss.ignore(7); // Ignorera "Class, "
            ss.ignore(6); // Ignorera "Name: "
            std::getline(ss, name, ',');
            ss.ignore(5); // Ignorera "SSN: "
            ss >> ssn;
            ss.ignore(13); // Ignorera ", Seat Number: "
            ss >> seatNr;
            ss.ignore(19); // Ignorera ", Baggage Allowances: "
            ss >> baggageAllowances;
            ss.ignore(14); // Ignorera ", Meal Option: "
            ss >> mealOption;
            ss.ignore(15); // Ignorera ", Train Number: "
            ss >> trainNr;
            ss.ignore(13); // Ignorera ", Destination: "
            std::getline(ss, destination);

            auto passenger = std::make_unique<SecondClass>(baggageAllowances, mealOption, name, ssn, seatNr);
            auto train = std::make_unique<Train>(trainNr, destination);
            auto ticket = std::make_unique<Ticket>(ticketNr, std::move(passenger), *train);

            tickets.push_back(std::move(ticket));
        }
    }

    inFile.close();
    std::cout << "Bookings loaded from " << fileName << ".\n";
}
