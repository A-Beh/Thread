//
//  main.cpp
//  6_1_Deadlock
//
//  Created by Ali Behfarnia on 10/15/24.

// Deadlock()
// A deadlock is a situation in concurrent programming where two or more threads are unable to proceed because each is waiting for the other to release a resource (e.g., a mutex). In other words, the threads are stuck and none can proceed because the resources they need are held by other threads in the same cycle.

// Possible Solutions:
// 1. Timed Locking: try_lock_for(), try_lock_until()) to avoid waiting indefinitely for a lock.
// 2. Lock Ordering:
// 3.



#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

using namespace std;


// ===============================
// Example of Deadlock Problem
// ===============================

void threadA() {
    cout << "Thread A: Trying to lock mutex1..." << endl;
    mutex1.lock();
    cout << "Thread A: Locked mutex1." << endl;

    // Simulate some work
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "Thread A: Trying to lock mutex2..." << endl;
    mutex2.lock();  // This will block if mutex2 is already locked by threadB
    cout << "Thread A: Locked mutex2." << endl;

    // Critical section
    cout << "Thread A: In critical section." << endl;

    // Unlock mutexes
    mutex2.unlock();
    mutex1.unlock();
}

void threadB() {
    cout << "Thread B: Trying to lock mutex2..." << endl;
    mutex2.lock();
    cout << "Thread B: Locked mutex2." << endl;

    // Simulate some work
    this_thread::sleep_for(chrono::milliseconds(200));

    cout << "Thread B: Trying to lock mutex1..." << endl;
    mutex1.lock();  // This will block if mutex1 is already locked by threadA
    cout << "Thread B: Locked mutex1." << endl;

    // Critical section
    cout << "Thread B: In critical section." << endl;

    // Unlock mutexes
    mutex1.unlock();
    mutex2.unlock();
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();

    std::cout << "Main thread: Program completed." << std::endl;
    return 0;
}

// Results:
//Thread B: Trying to lock mutex2...
//Thread A: Trying to lock mutex1...
//Thread A: Locked mutex1.
//Thread B: Locked mutex2.
//Thread A: Trying to lock mutex2...
//Thread B: Trying to lock mutex1...


// ===============================
// Solution of Deadlock
// ===============================

// Using order and lock_guard

//void threadA() {
//    cout << "Thread A: Trying to lock mutex1 and mutex2..." << endl;
//
//    // Lock mutex1 and mutex2 in order
//    std::lock(mutex1, mutex2);
//
//    cout << "Thread A: Locked mutex1 and mutex2." << endl;
//
//    // Use lock_guard with adopt_lock to manage the mutexes
//    lock_guard<std::mutex> lock1(mutex1, adopt_lock);
//    lock_guard<std::mutex> lock2(mutex2, adopt_lock);
//
//    // Critical section
//    cout << "Thread A: In critical section." << endl;
//
//    // Mutexes will be automatically unlocked when lock_guard goes out of scope
//}
//
//void threadB() {
//    cout << "Thread B: Trying to lock mutex1 and mutex2..." << endl;
//
//    // Lock mutex1 and mutex2 in the same order
//    lock(mutex1, mutex2);
//
//    cout << "Thread B: Locked mutex1 and mutex2." << endl;
//
//    // Use lock_guard with adopt_lock to manage the mutexes
//    lock_guard<std::mutex> lock1(mutex1, adopt_lock);
//    lock_guard<std::mutex> lock2(mutex2, adopt_lock);
//
//    // Critical section
//    cout << "Thread B: In critical section." << endl;
//
//    // Mutexes will be automatically unlocked when lock_guard goes out of scope
//}
//
//int main() {
//    std::thread t1(threadA);
//    std::thread t2(threadB);
//
//    t1.join();
//    t2.join();
//
//    std::cout << "Main thread: Program completed without deadlock." << std::endl;
//    return 0;
//}
