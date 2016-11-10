//
//  payment_verifier.h
//  Insight Code Challenge
//
//  Class definition for Payment Verifier, the object used
//  to process batch and stream files. Contains user id to
//  graph node mapping.
//

#ifndef payment_verifier_h
#define payment_verifier_h

#include <stdio.h>
#include "user_node.h"
#include <string>

class Payment_Verifier {
public:
    Payment_Verifier (std::string s1, std::string s2, std::string output1,
                      std::string output2, std::string output3) :
                      _batch(s1), _stream(s2), _output1(output1),
                      _output2(output2), _output3(output3) {};
    void processPayments();
    bool validateHeader(std::string &hdr);
    bool validateInput(std::string &time, std::string &id1, std::string &id2, std::string &amount);
    bool deleteNode(int &u);
private:
    void buildUserGraph(std::ifstream &file);
    void verifyPayments();
    // Member Variables
    std::string _batch, _stream, _output1, _output2, _output3;
    std::map<int, User_Node*> _users;
};
#endif /* payment_verifier_h */
