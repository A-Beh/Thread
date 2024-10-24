// Editted by Ali Behfarnia on 10/24.
// Multiple Mutexes

// Why multiple Mutexes
// 1. Resource:
// We use multiple mutexes in situations where different resources (data, variables, or objects) are shared between multiple threads, but each resource needs to be protected independently.

// 2. Concurrency:
// By using multiple mutexes, different parts of a program can execute in parallel, improving performance.

// Note: Deadlock
// Deadlock can be avoided by establishing a consistent locking order; using lock(m1, m2), using lock_guard, etc.


#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1, m2;  // Two mutexes to lock

void threadFunc1() {
    // Lock both m1 and m2 simultaneously using std::lock()
    lock(m1, m2);

    // After locking, you must use lock_guard with adopt_lock to indicate that the mutex is already locked
    lock_guard<mutex> lg1(m1, adopt_lock);  // Adopt lock for m1
    lock_guard<mutex> lg2(m2, adopt_lock);  // Adopt lock for m2

    cout << "Thread 1: locked both m1 and m2\n";

    // Simulate work
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread 1: done with work\n";
}

void threadFunc2() {
    // Lock both m1 and m2 simultaneously using std::lock()
    lock(m1, m2);

    // After locking, use adopt_lock
    lock_guard<mutex> lg1(m1, adopt_lock);  // Adopt lock for m1
    lock_guard<mutex> lg2(m2, adopt_lock);  // Adopt lock for m2

    cout << "Thread 2: locked both m1 and m2\n";

    // Simulate work
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread 2: done with work\n";
}

int main() {
    thread t1(threadFunc1);
    thread t2(threadFunc2);

    t1.join();
    t2.join();

    return 0;
}
