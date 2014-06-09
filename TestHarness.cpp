#include <iostream>
#include <memory>
#include "Command.h"

using namespace std;

//************************************************************************
//  Test Harness Helper functions
//************************************************************************

//******************************************************************
// Test Harness for Card // Command ADTs
//******************************************************************

int main() {
    while (!cin.eof()) {
        cout << "Enter command: ";
        Command cmd = Command();
        cin >> cmd;
    }
    
    return 0;
}