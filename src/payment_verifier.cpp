//
//  payment_verifier.cpp
//  Insight Code Challenge
//
//  Class implementation for Payment Verifier. Creates a graph
//  of user nodes from batch file data, then processes input
//  stream data.  Uses regex to verify data format, and outputs
//  to output1.txt, output2.txt, and output3.txt.  Incorrect
//  data entries in either the batch or stream file are ignored.
//

#include "payment_verifier.h"
#include <fstream>
#include <string>
#include <iostream>
#include <regex>

// Main entry point for processing batch and stream payments
void Payment_Verifier::processPayments() {
    std::ifstream file(_batch);
    
    // Create baseline network from batch file
    buildUserGraph(file);

    // Check new payments from stream file
    verifyPayments();
}

void Payment_Verifier::buildUserGraph(std::ifstream &file) {
    if (!file.is_open()) return;

    User_Node* new_user;
    std::string time, id1, id2, amount, message;
    
    // Grab header and validate with regex
    getline(file, time);
    if (!validateHeader(time))
        std::cout << "Invalid batch header, attempting to process anyway.\n";
    
    // read in batch file data
    while (getline(file, time, ',')) {
        getline(file, id1, ',');
        getline(file, id2, ',');
        getline(file, amount, ',');
        getline(file, message, '\n');

        // Validate time, id1, id2, amount with regex
        if (!validateInput(time, id1, id2, amount))
            continue;
            
        int u1 = stoi(id1), u2 = stoi(id2);
        
        // Add to network if new users
        if (_users.count(u1) == 0) {
            new_user = new User_Node(&_users);
            _users[u1] = new_user;
        }
        if (_users.count(u2) == 0) {
            new_user = new User_Node(&_users);
            _users[u2] = new_user;
        }
        // Add connection if doesn't exist
        if (!_users[u1]->hasConnection(_users[u2])) {
            _users[u1]->addAdjUser(_users[u2]);
            // Check against connection to self, allow only first time add
            if (u1 != u2)
              _users[u2]->addAdjUser(_users[u1]);
        }
    }
}

void Payment_Verifier::verifyPayments() {
    int lvl_found = 0;
    std::string time, id1, id2, amount, message;
    std::ifstream file(_stream);
    std::ofstream file1(_output1);
    std::ofstream file2(_output2);
    std::ofstream file3(_output3);
    
    // Grab header and validate with regex
    getline(file, time);
    if (!validateHeader(time))
        std::cout << "Invalid stream header, attempting to process anyway.\n";
    
    // read in batch file data
    while (getline(file, time, ',')) {
        getline(file, id1, ',');
        getline(file, id2, ',');
        getline(file, amount, ',');
        getline(file, message, '\n');
        
        // Validate time, id1, id2, amount with regex
        if (!validateInput(time, id1, id2, amount))
            continue;
 
        int u1 = stoi(id1), u2 = stoi(id2);
        
        // If both users exist, check if user to user transaction meets rule set
        lvl_found = (_users.count(u1) == 0 || _users.count(u2) == 0) ? 0 : _users[u1]->verifyUser(u2);
        
        // Write to output files accordingly
        switch (lvl_found) {
            case 4:
            case 3:
                // write verify to 3, failed to 1/2
                file3 << "trusted\n";
                file2 << "unverified\n";
                file1 << "unverified\n";
                break;
            case 2:
                // write verify to 3/2, failed to 1
                file3 << "trusted\n";
                file2 << "trusted\n";
                file1 << "unverified\n";
                break;
            case 1:
                // write verify to all
                file3 << "trusted\n";
                file2 << "trusted\n";
                file1 << "trusted\n";
                break;
            default:
                // write failed to all
                file3 << "unverified\n";
                file2 << "unverified\n";
                file1 << "unverified\n";
                break;
        }
    }
}

bool Payment_Verifier::validateHeader(std::string &hdr) {
    std::regex header("[ ]*time,[ ]*id1,[ ]*id2,[ ]*amount,[ ]*message[ ]*");
    return std::regex_match(hdr, header);
}

bool Payment_Verifier::validateInput(std::string &time, std::string &id1, std::string &id2, std::string &amount) {
    std::regex int_num("[ ]*[0-9]*[ ]*");
    std::regex money("[ ]*[0-9]*\\.[0-9]{2}[ ]*");
    std::regex time_date("[ ]*[0-9]{4}[-][0-9]{2}[-][0-9]{2}[ ]*[0-9]{2}:[0-9]{2}:[0-9]{2}[ ]*");
    return std::regex_match(time, time_date) &&
           std::regex_match(id1, int_num)    &&
           std::regex_match(id2, int_num)    &&
           std::regex_match(amount, money);
}

bool Payment_Verifier::deleteNode(int &u) {
    bool result = false;
    if (_users.count(u) != 0) {
        delete _users[u];
        result = true;
    }
    return result;
}
