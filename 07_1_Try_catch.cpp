//  Created by Ali Behfarnia on 10/24.

// Try and Catch:
//  The try and catch blocks are used to handle exceptions, which are runtime errors that can occur during the execution of a program. The try block contains code that might throw an exception, and the catch block handles the exception if one is thrown.

#include <iostream>
#include <stdexcept>  // For standard exceptions

using namespace std;  // Use the standard namespace

// Function to divide two numbers
double divide(int a, int b) {
    // Check for division by zero
    if (b == 0) {
        throw runtime_error("Division by zero error");  // Throwing an exception
    }
    return static_cast<double>(a) / b;
}

int main() {
    int x = 10;
    int y = 0;

    // Try block to attempt the division
    try {
        double result = divide(x, y);
        cout << "Result: " << result << endl;
    }
    // Catch block to handle the exception
    // Const ensures the handler doesn't accidentally alter the exception while handling it
    catch (const runtime_error &e) {
        cout << "Exception caught: " << e.what() << endl; //e.what(), which returns the message passed
        
    }

    cout << "Program continues..." << endl;

    return 0;
}
