// Editted by Ali Behfarnia on 10/24.

// Async
// a. It is a function that allows you to execute a callable (like a function or a lambda) asynchronously.
// b. It returns a future that represents the result of the asynchronous operation.
// c. When it is used, the callable may run in a separate thread, allowing the main thread to continue executing without waiting for the callable to finish.

// Use cases:
// a. I/O Operations
// b. Concurrent Computations: When you have multiple independent tasks that can be computed simultaneously.
// c. Good for long-Running Tasks that needs a lot of time to be completed, preventing the application from becoming unresponsive.


// launch::async
// It is to run in a new thread immediately.
// Ideal for tasks that should not be delayed and need to run as soon as they are invoked.

// launch::deferred
// The task does not execute immediately; it only runs when the result is needed.
// Useful for scenarios where the result of a computation may not be needed immediately or may not be needed at all.


#include <iostream>
#include <future>
#include <chrono>

using namespace std;

int calculate_sum(int a, int b) {
    this_thread::sleep_for(chrono::seconds(2)); // Simulate a delay
    return a + b;
}

int main() {
    
    future<int> fu = async(launch::async, calculate_sum, 5, 10);      // It runs in a new thread immediately
    future<int> def = async(launch::deferred, calculate_sum, 3, 7);   //

    cout << "Calculating sum with launch::async...\n";

    // Get the result from the async task (this will block until the task is complete)
    cout << "Sum (launch::async) is: " << fu.get() << '\n';

    cout << "Calculating sum with launch::deferred (will execute when called)...\n";

    // Get the result from the deferred task (this triggers execution)
    cout << "Sum (launch::deferred) is: " << def.get() << '\n';

    return 0;
}

// Results:
//Calculating sum with launch::async...
//Sum (launch::async) is: 15
//Calculating sum with launch::deferred (will execute when called)...
//Sum (launch::deferred) is: 10
