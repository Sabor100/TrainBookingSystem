#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>

System::System() {
    loadBookingsFromFile("bookings.txt");

}

System::~System() {
    saveBookingsToFile("bookings.txt");
}

void System::run() {
    int choice = -1;

    do {
        std::cout << "\n=== Train Booking System ===\n";
        std::cout << "1. Add a Train\n";
        std::cout << "2. Add a Ticket\n";
        std::cout << "3. Show All Bookings\n";
        std::cout << "4. Search Passenger\n";
        std::cout << "5. Delete Booking\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 0 and 5.\n";
            continue;
        }

        std::cin.ignore();

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
        case 5:
            deleteBooking();
            break;
        case 0:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 0 and 5.\n";
        }

    } while (choice != 0);
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
    std::string ssn;
    int passengerType;

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

    if (selectedTrain->getAvailableSeats() <= 0) {
        std::cout << "No seats available on this train.\n";
        return;
    }

    std::cout << "Available seats on train " << trainNr << ": " << selectedTrain->getAvailableSeats() << "\n";

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

    if (!selectedTrain->bookSeat()) {
        std::cout << "No seats available for booking. Try another train.\n";
        return;
    }

    auto ticket = std::make_unique<Ticket>(tickets.size() + 1, std::move(passenger), *selectedTrain);
    tickets.push_back(std::move(ticket));

    saveBookingsToFile("bookings.txt");

    std::cout << "Ticket added successfully! Seats left on train " << trainNr << ": " << selectedTrain->getAvailableSeats() << "\n";

}

void System::deleteBooking() {
    int trainNr;
    std::cout << "Enter ticket number to delete booking: ";
    std::cin >> trainNr;

    auto it = std::remove_if(tickets.begin(), tickets.end(), [trainNr, this](const std::unique_ptr<Ticket>& ticket) {
        if (ticket->getTicketNr() == trainNr) {
            for (auto& train : trains) {
                if (train->getTrainNr() == ticket->getTicketNr()) {
                    train->bookSeat(1);
                }
            }
            return true;
        }
        return false;
        });

    if (it != tickets.end()) {
        tickets.erase(it, tickets.end());
        std::cout << "Ticket found and has been deleted.\n";
    }
    else {
        std::cout << "No ticket found for the given ticket number.\n";
    }
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
    std::cout << "Bookings and train details saved to " << fileName << ".\n";
}


void splitString(string& input, char delimiter, string arr[], int& index) {
    istringstream stream(input);
    string token;

    while (getline(stream, token, delimiter)) {
        arr[index++] = token;
    }
}

inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

void System::loadBookingsFromFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << fileName << " for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string type, name, seatType, breakfast, destination;
        string ssn;
        int ticketNr, seatNr, trainNr, baggageAllowances;
        bool mealOption;

        char delimiter = ',';
        string arrayOfSubStr[400];
        int index = 0;
        splitString(line, delimiter, arrayOfSubStr, index);

        for (int i = 0; i < index; i++) {
            if (arrayOfSubStr[i].find("Ticket Number") != string::npos) {
				ticketNr = stoi(arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1));
			} else if(arrayOfSubStr[i].find("Passenger Type") != string::npos) {
				type = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1);
                ltrim(type);
			}
			else if (arrayOfSubStr[i].find("Name") != string::npos) {
				name = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1); 
			}
			else if (arrayOfSubStr[i].find("SSN") != string::npos) {
				ssn = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1);
			}
			else if (arrayOfSubStr[i].find("Seat Number") != string::npos) {
				seatNr = stoi(arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1));
			}
			else if (arrayOfSubStr[i].find("Seat Type") != string::npos) {
				seatType = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1);
			}
			else if (arrayOfSubStr[i].find("Breakfast") != string::npos) {
				breakfast = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1);
			}
			else if (arrayOfSubStr[i].find("Train Number") != string::npos) {
				trainNr = stoi(arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1));
			}
			else if (arrayOfSubStr[i].find("Destination") != string::npos) {
				destination = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1);
			}
            else if (arrayOfSubStr[i].find("Baggage Allowances") != string::npos) {
				baggageAllowances = stoi(arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1));
			}
			else if (arrayOfSubStr[i].find("Meal Option") != string::npos) {
				mealOption = arrayOfSubStr[i].substr(arrayOfSubStr[i].find(":") + 1) == " No" ? false : true;
            }
        }
        
        if (type == "First Class") {
            auto passenger = std::make_unique<FirstClass>(ltrim_copy(seatType), ltrim_copy(breakfast), ltrim_copy(name), ltrim_copy(ssn), seatNr);
            auto train = std::make_unique<Train>(trainNr, ltrim_copy(destination));
            auto ticket = std::make_unique<Ticket>(ticketNr, std::move(passenger), *train);
            tickets.push_back(std::move(ticket));
        }
        else {
            auto passenger = std::make_unique<SecondClass>(baggageAllowances, mealOption, ltrim_copy(name), ltrim_copy(ssn), seatNr);
            auto train = std::make_unique<Train>(trainNr, ltrim_copy(destination));
            auto ticket = std::make_unique<Ticket>(ticketNr, std::move(passenger), *train);

            tickets.push_back(std::move(ticket));
        }
    }

    inFile.close();
}