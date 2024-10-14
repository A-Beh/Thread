//  Created by Ali Behfarnia on 10/12/24.
//  4_3_Mutex_recursive

// Recursive mutex (aka reentrant mutex):
// A recursive mutex is a type of mutex that allows the same thread to lock it multiple times without causing a deadlock. 
// The thread must unlock the mutex the same number of times it locks it. Both lock and unlock are managed via stack memory.

#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex rec_mtx;

void recursiveFunction(int count, int thread_id) {
    if (count < 0) return;
    
    rec_mtx.lock();
    std::cout << "Thread " << thread_id << " acquired lock, count: " << count << std::endl;
    
    // Recursive call
    recursiveFunction(count - 1, thread_id);
    
//    std::cout << "Thread " << thread_id << " unlocking, count: " << count << std::endl;
    rec_mtx.unlock();
    std::cout << "Thread " << thread_id << " unlocking, count: " << count << std::endl;
}

int main() {
    // Create two threads, t1 and t2
    std::thread t1(recursiveFunction, 3, 1);  // Thread 1
    std::thread t2(recursiveFunction, 3, 2);  // Thread 2

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}
