// Editted by Ali Behfarnia on 10/24.

// shared_mutex:
// A shared_mutex allows multiple threads to acquire a shared lock for reading

// Use case:
// This is useful in situations where you have frequent read operations but less frequent write operations,
// and you want to allow multiple threads to read concurrently while preventing race conditions when writing.

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <vector>

using namespace std;

shared_mutex shared_mut;

// Shared variable
int x = 0;

void write(int id)
{
    lock_guard<shared_mutex> lck_guard(shared_mut);

    // Start of critical section
    ++x;
    cout << "Writer " << id << " incremented x to " << x << endl;
    // End of critical section
}

void read(int id)
{
    shared_lock<shared_mutex> lck_guard(shared_mut);

    // Start of critical section
    cout << "Reader " << id << " is reading x = " << x << endl;
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate time spent reading
    cout << "Reader " << id << " finished reading." << endl;
    // End of critical section
}

int main()
{
    vector<thread> threads;

    // Reduced to 3 reader threads
    for (int i = 0; i < 3; ++i)
        threads.push_back(thread(read, i + 1));

    // Two writer threads
    threads.push_back(thread(write, 1));
    threads.push_back(thread(write, 2));

    // Reduced to 2 reader threads
    for (int i = 0; i < 2; ++i)
        threads.push_back(thread(read, i + 4));

    // Join all threads
    for (auto& thr : threads)
        thr.join();
}

// Results: with shared_mutex
//Reader 1 is reading x = 0
//Reader 2 is reading x = 0
//Reader 3 is reading x = 0
//Reader 1 finished reading.
//Reader 2 finished reading.
//Reader 3 finished reading.
//Writer 1 incremented x to 1
//Writer 2 incremented x to 2
//Reader 4 is reading x = 2
//Reader 5 is reading x = 2
//Reader 4 finished reading.
//Reader 5 finished reading.

//************************
//************************
//************************

//Results: if not shared_mutex, and used
// lock_guard<shared_mutex> lck_guard(shmut) for reader

//Reader 1 is reading x = 0
//Reader 1 finished reading.
//Reader 2 is reading x = 0
//Reader 2 finished reading.
//Reader 3 is reading x = 0
//Reader 3 finished reading.
//Writer 1 incremented x to 1
//Writer 2 incremented x to 2
//Reader 4 is reading x = 2
//Reader 4 finished reading.
//Reader 5 is reading x = 2
//Reader 5 finished reading.
