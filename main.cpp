
#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#define max 100

using namespace std;

int maxBid() {
    int maxb = 0;
    ifstream summaryFile("summary_data.txt");

    int bookingId, courtNum, equipmentRent = 0, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    while (summaryFile >> bookingId >> courtNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        if (maxb < bookingId) {
            maxb = bookingId;
        }
    }
    summaryFile.close();
    return maxb + 1;
}

int checkCourt(int court) {
    ifstream facilityFile("facility_data.txt");

    int bookingId, courtNum, equipmentRent = 0, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    while (facilityFile >> bookingId >> courtNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        if (courtNum == court) {
            return 1;
        }
    }
    facilityFile.close();
    return 0;
}

class Member {
public:
    char fname[100];
    char sname[100];
    char address[100];
    char phone[12];
    char from_time[20];
    char to_time[20];
    float payment_advance;
    int booking_id;
    int equipment_rent;
};

class SportsFacility {
public:
    int facilityNumber;
    char sportType[50];
    int hourlyRate;
    int status;

    Member member;
    void friend searchFacility(int);
};

void searchFacility(int facilityNo) {
    int found = checkCourt(facilityNo);
    ifstream facilityFile("facility_data.txt");

    if (found == 1) {
        cout << "\n----- Facility Booking Details -----\n";
        
        int bookingId, courtNum, equipmentRent, paymentAdvance;
        string fname, sname, address, phone, fromTime, toTime;

        while (facilityFile >> bookingId >> courtNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
            if (courtNum == facilityNo) {
                cout << std::setw(20) << std::left << "Booking ID: " << bookingId << endl;
                cout << std::setw(20) << std::left << "Facility No.: " << courtNum << endl;
                cout << std::setw(20) << std::left << "Member Name: " << fname << " " << sname << endl;
                cout << std::setw(20) << std::left << "Phone: " << phone << endl;
                cout << std::setw(20) << std::left << "Start Time: " << fromTime << endl;
                cout << std::setw(20) << std::left << "End Time: " << toTime << endl;
                cout << std::setw(20) << std::left << "Advance Paid: " << paymentAdvance << endl;
                cout << std::setw(20) << std::left << "Equipment Rent: " << equipmentRent << endl;
                break;
            }
        }
    } else {
        cout << "Facility is currently available" << endl;
    }
    facilityFile.close();
    getch();
}

class FacilityAllocate {
public:
    vector<int> badminton, cricket, football, basketball, tennis, swimming, gym, tabletennis, squash;
    int nextAvailableFacility(int sportType);
};

int FacilityAllocate::nextAvailableFacility(int sportType) {
    ifstream facilityFile("facility_data.txt");
    
    int bookingId, facilityNum, equipmentRent = 0, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    while (facilityFile >> bookingId >> facilityNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        switch(facilityNum/100) {
            case 1: badminton.push_back(facilityNum); break;
            case 2: cricket.push_back(facilityNum); break;
            case 3: football.push_back(facilityNum); break;
            case 4: basketball.push_back(facilityNum); break;
            case 5: tennis.push_back(facilityNum); break;
            case 6: swimming.push_back(facilityNum); break;
            case 7: gym.push_back(facilityNum); break;
            case 8: tabletennis.push_back(facilityNum); break;
            case 9: squash.push_back(facilityNum); break;
        }
    }

    sort(badminton.begin(), badminton.end());
    sort(cricket.begin(), cricket.end());
    sort(football.begin(), football.end());
    sort(basketball.begin(), basketball.end());
    sort(tennis.begin(), tennis.end());
    sort(swimming.begin(), swimming.end());
    sort(gym.begin(), gym.end());
    sort(tabletennis.begin(), tabletennis.end());
    sort(squash.begin(), squash.end());

    int startNum;
    vector<int>* sportVec;

    switch(sportType) {
        case 1: startNum = 101; sportVec = &badminton; break;
        case 2: startNum = 201; sportVec = &cricket; break;
        case 3: startNum = 301; sportVec = &football; break;
        case 4: startNum = 401; sportVec = &basketball; break;
        case 5: startNum = 501; sportVec = &tennis; break;
        case 6: startNum = 601; sportVec = &swimming; break;
        case 7: startNum = 701; sportVec = &gym; break;
        case 8: startNum = 801; sportVec = &tabletennis; break;
        case 9: startNum = 901; sportVec = &squash; break;
        default: return -1;
    }

    int nextNum = startNum;
    for(int num : *sportVec) {
        if(num == nextNum) nextNum++;
        else return nextNum;
    }
    return nextNum;
}

class GymkhanaMgmt : public SportsFacility {
public:
    void checkIn();
    void bookedFacilities();
    void searchMember(char*);
    void checkOut(int);
    void guestSummaryReport();
};

// Implementation of methods...

class SportsInfo {
public:
    SportsInfo() {
        cout << "\n*** Welcome to Our Gymkhana Sports Club ***\n" << endl;
        cout << "\nSports Facilities and Rates:\n" << endl;

        string facilities[] = {
            "Badminton Courts", 
            "Cricket Nets",
            "Football Ground",
            "Basketball Court",
            "Tennis Courts",
            "Swimming Pool",
            "Gymnasium",
            "Table Tennis",
            "Squash Courts"
        };

        int hourlyRates[] = {200, 500, 1000, 300, 400, 250, 150, 200, 300};

        string amenities[] = {
            "Rackets available for rent",
            "Bowling machine available",
            "Flood lights for evening play",
            "Indoor air-conditioned court",
            "Professional coaching available",
            "Temperature controlled water",
            "Modern exercise equipment",
            "Professional tables",
            "Air-conditioned courts"
        };

        for (int i = 0; i < 9; i++) {
            cout << "Facility: " << facilities[i] << endl;
            cout << "Rate: Rs." << hourlyRates[i] << " per hour" << endl;
            cout << "Amenities: " << amenities[i] << endl;
            cout << "************" << endl;
        }
    }
};

// Main function implementation would be similar but with sports-related menu options
void GymkhanaMgmt::guestSummaryReport() {
    ifstream summaryFile("summary_data.txt");

    int bookingId, facilityNum, equipmentRent = 0, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    cout << "\n----- Current Facility Bookings Report -----\n" << endl;
    
    while (summaryFile >> bookingId >> facilityNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        cout << std::setw(20) << std::left << "Booking ID: " << bookingId << endl;
        cout << std::setw(20) << std::left << "Facility No.: " << facilityNum << endl;
        cout << std::setw(20) << std::left << "Member Name: " << fname << " " << sname << endl;
        cout << std::setw(20) << std::left << "Phone: " << phone << endl;
        cout << std::setw(20) << std::left << "Start Time: " << fromTime << endl;
        cout << std::setw(20) << std::left << "End Time: " << toTime << endl;
        cout << std::setw(20) << std::left << "Advance Paid: " << paymentAdvance << endl;
        cout << std::setw(20) << std::left << "Equipment Rent: " << equipmentRent << endl;
        cout << "----------------------------------------\n" << endl;
    }
    summaryFile.close();
    getch();
}

void GymkhanaMgmt::checkIn() {
    int found, facilityNo, sportType;
    cout << "\nAvailable Sports Facilities:\n";
    cout << "1. Badminton Courts\n";
    cout << "2. Cricket Nets\n";
    cout << "3. Football Ground\n";
    cout << "4. Basketball Court\n";
    cout << "5. Tennis Courts\n";
    cout << "6. Swimming Pool\n";
    cout << "7. Gymnasium\n";
    cout << "8. Table Tennis\n";
    cout << "9. Squash Courts\n";
    cout << "Enter facility type to book (1-9): ";
    cin >> sportType;

    FacilityAllocate fa;
    facilityNo = fa.nextAvailableFacility(sportType);

    if (facilityNo != -1) {
        int bookingId = maxBid();

        string fname, sname, address, phone, fromTime, toTime;
        int paymentAdvance, equipmentRent = 0;

        cout << "\nEnter Member First Name: ";
        cin >> fname;

        cout << "Enter Member Last Name: ";
        cin >> sname;

        cout << "Enter Address (city): ";
        cin >> address;

        cout << "Enter Phone: ";
        cin >> phone;

        cout << "Enter Start Time (HH:MM): ";
        cin >> fromTime;

        cout << "Enter End Time (HH:MM): ";
        cin >> toTime;

        cout << "Enter Advance Payment: ";
        cin >> paymentAdvance;

        char rentEquip;
        cout << "Do you want to rent equipment? (y/n): ";
        cin >> rentEquip;

        if (rentEquip == 'y' || rentEquip == 'Y') {
            cout << "Enter equipment rental amount: ";
            cin >> equipmentRent;
        }

        // Save booking to facility data file
        ofstream facilityFile("facility_data.txt", ios::app);
        facilityFile << bookingId << " " << facilityNo << " " << fname << " " << sname << " "
                    << address << " " << phone << " " << fromTime << " " << toTime << " "
                    << paymentAdvance << " " << equipmentRent << endl;
        facilityFile.close();

        // Save booking to summary data file
        ofstream summaryFile("summary_data.txt", ios::app);
        summaryFile << bookingId << " " << facilityNo << " " << fname << " " << sname << " "
                   << address << " " << phone << " " << fromTime << " " << toTime << " "
                   << paymentAdvance << " " << equipmentRent << endl;
        summaryFile.close();

        cout << "\nFacility Booked Successfully!" << endl;
        cout << "Your Facility Number is: " << facilityNo << endl;
    } else {
        cout << "\nNo facilities available for this sport currently." << endl;
    }
    getch();
}

void GymkhanaMgmt::bookedFacilities() {
    ifstream facilityFile("facility_data.txt");

    vector<vector<int>> facilities(9);  // One vector for each sport type

    int bookingId, facilityNum, equipmentRent, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    while (facilityFile >> bookingId >> facilityNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        int sportType = (facilityNum / 100) - 1;  // Convert facility number to sport type index
        facilities[sportType].push_back(facilityNum);
    }

    cout << "\n----- Currently Booked Facilities -----\n" << endl;
    
    string sportNames[] = {
        "Badminton Courts", "Cricket Nets", "Football Ground",
        "Basketball Court", "Tennis Courts", "Swimming Pool",
        "Gymnasium", "Table Tennis", "Squash Courts"
    };

    for (int i = 0; i < 9; i++) {
        cout << sportNames[i] << ": ";
        if (facilities[i].empty()) {
            cout << "No bookings";
        } else {
            sort(facilities[i].begin(), facilities[i].end());
            for (int facilityNum : facilities[i]) {
                cout << facilityNum << " ";
            }
        }
        cout << endl;
    }

    facilityFile.close();
    getch();
}

void GymkhanaMgmt::searchMember(char* memberName) {
    ifstream facilityFile("facility_data.txt");
    bool found = false;

    cout << "\n----- Member Booking Details -----\n" << endl;

    int bookingId, facilityNum, equipmentRent, paymentAdvance;
    string fname, sname, address, phone, fromTime, toTime;

    while (facilityFile >> bookingId >> facilityNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
        if (fname == memberName) {
            found = true;
            cout << std::setw(20) << std::left << "Booking ID: " << bookingId << endl;
            cout << std::setw(20) << std::left << "Facility No.: " << facilityNum << endl;
            cout << std::setw(20) << std::left << "Member Name: " << fname << " " << sname << endl;
            cout << std::setw(20) << std::left << "Phone: " << phone << endl;
            cout << std::setw(20) << std::left << "Start Time: " << fromTime << endl;
            cout << std::setw(20) << std::left << "End Time: " << toTime << endl;
            cout << std::setw(20) << std::left << "Advance Paid: " << paymentAdvance << endl;
            cout << std::setw(20) << std::left << "Equipment Rent: " << equipmentRent << endl;
            cout << "----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No bookings found for member: " << memberName << endl;
    }

    facilityFile.close();
    getch();
}

int getFacilityRate(int facilityNum) {
    int sportType = facilityNum / 100;
    switch(sportType) {
        case 1: return 200;  // Badminton
        case 2: return 500;  // Cricket
        case 3: return 1000; // Football
        case 4: return 300;  // Basketball
        case 5: return 400;  // Tennis
        case 6: return 250;  // Swimming
        case 7: return 150;  // Gym
        case 8: return 200;  // Table Tennis
        case 9: return 300;  // Squash
        default: return 0;
    }
}

void GymkhanaMgmt::checkOut(int facilityNum) {
    int found = checkCourt(facilityNum);
    if (found == 1) {
        float hours;
        cout << "\nEnter number of hours used: ";
        cin >> hours;

        float facilityCharge = hours * getFacilityRate(facilityNum);

        // Process checkout and generate bill
        ifstream inFile("facility_data.txt");
        ofstream tempFile("temp_facility_data.txt");

        int bookingId, currFacilityNum, equipmentRent, paymentAdvance;
        string fname, sname, address, phone, fromTime, toTime;

        bool foundBooking = false;
        while (inFile >> bookingId >> currFacilityNum >> fname >> sname >> address >> phone >> fromTime >> toTime >> paymentAdvance >> equipmentRent) {
            if (currFacilityNum == facilityNum) {
                foundBooking = true;
                cout << "\n----- Checkout Bill -----\n";
                cout << std::setw(25) << std::left << "Member Name: " << fname << " " << sname << endl;
                cout << std::setw(25) << std::left << "Facility Number: " << facilityNum << endl;
                cout << std::setw(25) << std::left << "Hours Used: " << hours << endl;
                cout << std::setw(25) << std::left << "Facility Charges: " << facilityCharge << endl;
                cout << std::setw(25) << std::left << "Equipment Rental: " << equipmentRent << endl;
                cout << std::setw(25) << std::left << "Total Amount: " << facilityCharge + equipmentRent << endl;
                cout << std::setw(25) << std::left << "Advance Paid: " << paymentAdvance << endl;
                cout << std::setw(25) << std::left << "Balance Due: " 
                     << (facilityCharge + equipmentRent - paymentAdvance) << endl;
            } else {
                tempFile << bookingId << " " << currFacilityNum << " " << fname << " "
                        << sname << " " << address << " " << phone << " " << fromTime << " "
                        << toTime << " " << paymentAdvance << " " << equipmentRent << endl;
            }
        }

        inFile.close();
        tempFile.close();

        remove("facility_data.txt");
        rename("temp_facility_data.txt", "facility_data.txt");

        if (!foundBooking) {
            cout << "No booking found for this facility." << endl;
        }
    } else {
        cout << "This facility is not currently booked." << endl;
    }
    getch();
}

// Main menu function
void manageFacilities(GymkhanaMgmt gm) {
    int opt, facilityNo;
    do {
        system("cls");
        cout << "\n----- Gymkhana Facility Management -----\n";
        cout << "1. View Facility Information\n";
        cout << "2. View Booked Facilities\n";
        cout << "3. Search Facility\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter Option: ";
        cin >> opt;

        switch(opt) {
            case 1:
                SportsInfo();
                getch();
                break;
            case 2:
                gm.bookedFacilities();
                break;
            case 3:
                cout << "\nEnter facility number: ";
                cin >> facilityNo;
                searchFacility(facilityNo);
                break;
            case 4:
                break;
            default:
                cout << "\nPlease enter a valid option.";
                getch();
                break;
        }
    } while(opt != 4);
}

// Main function
int main() {
    GymkhanaMgmt gm;
    int opt, facilityNo;
    char memberName[100];

    do {
        system("cls");
        cout << "\n----- Gymkhana Sports Club Management System -----\n";
        cout << "1. Manage Facilities\n";
        cout << "2. Book Facility\n";
        cout << "3. Release Facility\n";
        cout << "4. Search Member\n";
        cout << "5. View Booking Report\n";
        cout << "6. Exit\n";
        cout << "Enter Option: ";
        
        cin >> opt;

        switch(opt) {
            case 1:
                manageFacilities(gm);
                break;
            case 2:
                gm.checkIn();
                break;
            case 3:
                cout << "Enter Facility Number: ";
                cin >> facilityNo;
                gm.checkOut(facilityNo);
                break;
            case 4:
                cout << "Enter Member Name: ";
                cin >> memberName;
                gm.searchMember(memberName);
                break;
            case 5:
                gm.guestSummaryReport();
                break;
            case 6:
                cout << "\nThank you for using Gymkhana Management System!\n";
                break;
            default:
                cout << "\nPlease enter a valid option.";
                getch();
                break;
        }
    } while(opt != 6);

    return 0;
}