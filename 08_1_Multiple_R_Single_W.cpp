// Editted by Ali Behfarnia on 10/24.

// Multiple Reads_Single Write
// Multiple readers and single writer synchronization is a common scenario in multithreading.
// In the below code, the loop is used for read, becase it simulates a more realistic case where 
// reads are frequent and writes are infrequent.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

mutex mut;

// Shared variable
int x = 0;

void write()
{
    lock_guard<mutex> lck_guard(mut);  // Lock mutex during the write operation

    // Start of critical section
    ++x;  // Increment the shared variable
    cout << "Writer incremented x to " << x << endl;
    // End of critical section
}

void read()
{
    lock_guard<mutex> lck_guard(mut);  // Lock mutex during the read operation

    // Start of critical section
    cout << "Reader accessed x with value: " << x << endl;
    this_thread::sleep_for(chrono::milliseconds(100));  // Simulate reading time
    // End of critical section
}

int main()
{
    vector<thread> t;

    // Start multiple reader threads
    for (int i = 0; i < 3; ++i)
        t.push_back(thread(read));

    // Start two writer threads
    t.push_back(thread(write));
    t.push_back(thread(write));

    // Start more reader threads
    for (int i = 0; i < 2; ++i)
        t.push_back(thread(read));

    // Join all threads (wait for all of them to finish)
    for (auto& threads : t)
        threads.join();

    return 0;
}

// Results: 
// Reader accessed x with value: 0
// Reader accessed x with value: 0
// Reader accessed x with value: 0
// Writer incremented x to 1
// Writer incremented x to 2
// Reader accessed x with value: 2
// Reader accessed x with value: 2
// Program ended with exit code: 0