// Created by Ali Behfarnia on 10/24.

// Motivation:
// Thread does not provide a way to return values.
// Using conditional variable, a thread can signal another thread that shared data is modified. However, they
// can NOT directly transfer data from one thread to another.

// Promise and Future: (Classes to transfer data between threads, provide a shared state)
// A promise is an object that holds a value or exception that is set by one thread and retrieved by main or another thread.
// Its associated future is a placeholder for the result, allowing the receiving thread to access the value once it's ready.
// No explicy locking

// Notes: (acts like setter and getter)
// 1. promise:
//    a. Used to set values or exceptions
//       .set_value()
// 2. future
//    a. Used to get values from promise. E.e., p.get_future()
//    b. Ask promise if the value is available.
//    c. Wait for the promise. E.g., f.get();



#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

void calculate(int a, int b, promise<int>&& resultPromise) { 
    // && indicates that resultPromise is an rvalue reference.
    // Regarding &&, this move transfers ownership of the promise to the thread function, preventing unnecessary copying of the promise, which is efficient and suitable for single-use, temporary objects like a promise
    int ss;
    this_thread::sleep_for(chrono::seconds(2)); // To show the simulation of some processing
    ss =  a + b;
    resultPromise.set_value(ss);
}

int main() {
    promise<int> p;
    future<int> f = p.get_future();

    thread t(calculate, 5, 10, std::move(p));

    cout << "Doing other work in the main thread...\n";

    // Get the result (blocks until it's ready)
    int result = f.get();
    cout << "Result from the thread: " << result << endl;

    t.join();
    return 0;
}
