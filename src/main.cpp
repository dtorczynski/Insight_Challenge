//
//  main.cpp
//  Insight Code Challenge
//
//

#include <iostream>
#include <vector>
#include "payment_verifier.h"
#include "user_node.h"

// Entry point into the application
int main(int argc, char *argv[]) {
    if (argc < 6) {
        std::cout << "Expected 5 arguments, fewer than 5 received.\n";
        std::cout << "Correct syntax is: \n";
        std::cout << "arg1 -- batch file\n";
        std::cout << "arg2 -- stream file\n";
        std::cout << "arg3 -- output feature 1 file\n";
        std::cout << "arg4 -- output feature 2 file\n";
        std::cout << "arg5 -- output feature 3 file\n";
        return 0;
    }
    // Create verification object and run process payments on that object
    std::string batch   = argv[1],
                stream  = argv[2],
                output1 = argv[3],
                output2 = argv[4],
                output3 = argv[5];

    Payment_Verifier p(batch, stream, output1, output2, output3);
    p.processPayments();
    
    return 0;
}
