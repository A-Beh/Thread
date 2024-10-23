// Created by Ali Behfarnia on 10/24.

// Wrapper around std::vector
// This allows you to control access to the vector's functionality,
//  providing a more controlled interface.


#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::literals;

class Vector {
    mutex mut;
    vector<int> vec;
public:
    // Method to add an element to the vector
    void add_element(const int& i) {
        mut.lock();
        // Start of critical section
        vec.push_back(i); // Push_back act like .append() in the list
        // End of critical section
        mut.unlock();
    }

    // Method to print the final elements of the vector
    void print() {
        mut.lock();
        // Start of critical section
        for (auto i : vec) {
            cout << i << " ";
        }
        cout << endl;
        // End of critical section
        mut.unlock();
    }
};

void func(Vector& vec) {
    for (int i = 0; i < 5; ++i) {
        vec.add_element(i);  // Add elements to the vector
        this_thread::sleep_for(50ms);  // Simulate some work
    }
}

int main() {
    Vector vec;

    // Create two threads
    thread t1(func, ref(vec));
    thread t2(func, ref(vec));

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Print the final content of the vector
    vec.print();

    return 0;
}

// Results:
// 0 0 1 1 2 2 3 3 4 4 

