// Editted by Ali Behfarnia on 10/24.
// Goal: Understanding the Mutex (Mutual Exculsion) in C++ Threading

// Why mutex is needed?
// Mutexes are synchronization primitives used in C++ multithreading to ensure that only one thread at a time can access a shared resource. Using mutex prevents data corruption and race conditions.

// Race conditions:
//  occur in multithreaded programs when two or more threads access a shared resource simultaneously and try to MODIFY it in a way that leads to unexpected or incorrect results. This happens when the outcome of a program depends on the timing of thread execution.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int numbo = 10;
mutex m;

void minus_one() {
    m.lock();
    numbo--;
    m.unlock();
}

int main() {
    thread t1(minus_one);
    thread t2(minus_one);

    t1.join();
    t2.join();

    cout << "The updated number is: " << numbo << endl;
    return 0;
}
