// Editted aby Ali Behfarnia

// Atomic:
//  provides lock-free, thread-safe operations on single variables, typically using hardware support.
// Normally only integer types and pointers types are used
// Best for individual variables with simple atomic operations like increments, reads, and writes.

// Volatile:
// In C++, the volatile keyword tells the compiler that a variable’s value may change at any time,
// even if the code itself doesn’t modify it directly.
// It avoiding Compiler Optimization, ensuring that every read or write to that variable actually happens.
// Notes- Use cases:
//      a. Memory-Mapped I/O Registers: volatile forces the CPU to check the I/O values directly instead of using a cached value.
//      b. Multithreading (in Limited Cases): Volatile doesn’t make access thread-safe, but can be used with atomic or mutexes
//      c. Interrupt Service Routines (ISRs): Using the lates value

// ==========================
// Atomic Example:
// ==========================
//
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> cnt=0;

void increment_with_atomic() {
    for (int i = 0; i < 1000; ++i) {
        ++cnt;              // Atomic increment, no lock needed
    }
}

int main() {
    thread t1(increment_with_atomic);
    thread t2(increment_with_atomic);

    t1.join();
    t2.join();

    cout << "Final counter with atomic: " << cnt.load() << endl;
    return 0;
}

// Result:
// Final counter with atomic: 2000



// ==========================
// Volatile: Example with flag
// ==========================

//#include <iostream>
//#include <thread>
//#include <atomic>
//#include <chrono>
//
//using namespace std;
//
//volatile bool work_done = false;    // Volatile flag to signal completion
//atomic<int> counter=0;             // Atomic counter for thread-safe updates
//
//void worker_thread() {
//    for (int i = 0; i < 1000; ++i) {
//        ++counter;                  // Thread-safe increment
//    }
//    work_done = true;               // Signal that work is done
//}
//
//void monitor_thread() {
//    while (!work_done) {            // Wait until worker thread completes
//        cout << "Waiting for work to complete...\n";
//        this_thread::sleep_for(chrono::milliseconds(1000));  // Check periodically
//    }
//    cout << "Work completed. Counter value: " << counter << endl;
//}
//
//int main() {
//    thread t1(worker_thread);
//    thread t2(monitor_thread);
//
//    t1.join();
//    t2.join();
//
//    return 0;
//}
