#include <iostream>
#include <memory>
#include <cstdlib>
#include "Command.h"
#include "Deck.h"

using namespace std;

//************************************************************************
//  Test Harness Helper functions
//************************************************************************

//******************************************************************
// Test Harness for Card // Command ADTs
//******************************************************************

int main(int argc, char* argv[]) {
    int randomSeed;
    if (argc > 1) {
        randomSeed = atoi(argv[1]);
    }

    Command cmd = Command();

    while (!cin.eof()) {
        cout << "Enter command:";
        cin >> cmd;
    }

    
    return 0;
}