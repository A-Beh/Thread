// Editted by Ali Behfarnia on 10/24.

// Packaged_task:
// It is a template class that wraps a callable object (like a function, lambda, or functor) and allows its execution to be deferred and handled asynchronously.

// Use cases:
// a. Ideal for asynchronous programming where you want to start a task on a new thread and retrieve the result later.
// b. Often used in scenarios where tasks need to run in parallel or concurrently, and you want to manage the result from the main thread.


#include <iostream>
#include <future>
#include <thread>

using namespace std;

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    
    packaged_task<int(int)> task(factorial);
    future<int> result = task.get_future(); // Get a future associated with the packaged_task

    // Start a new thread and move the packaged_task to it, passing an argument (5 in this case)
    thread t(std::move(task), 5);

    // Main thread can perform other tasks here if needed
    cout << "Calculating factorial in a separate thread...\n";
    cout << "Factorial of 5 is " << result.get() << '\n';

    // Join the thread to ensure it finishes before main exits
    t.join();

    return 0;
}

// Results:
// Calculating factorial in a separate thread...
// Factorial of 5 is 120
