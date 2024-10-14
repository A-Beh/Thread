// Editted by Ali Behfarnia on 10/24.
// Goal: Understanding the trylock() on Mutex

// What does try_lock() do and why we use it?
// The try_lock() function in C++ mutex threading is used to attempt to acquire a mutex lock without blocking the current thread.
// Unlike the regular lock() function, which blocks the thread until the mutex is acquired, try_lock() returns immediately if the
// mutex is already locked by another thread.

// Benefits:
// 1) Avoiding Deadlocks: Deadlocks occur when multiple threads are waiting for each other to release mutexes.
// 2) Non-Blocking Operations: When you need to perform an operation that doesn't require blocking the current thread.
// Timeouts: One can use try_lock() with a timeout to limit the amount of time a thread is willing to wait for the mutex.
//           If the mutex is not acquired within the specified timeout, the thread can proceed with alternative actions or retry later.


 #include <iostream>
 #include <thread>
 #include <mutex>
 #include <chrono>
 using namespace std;

 int numbo = 20;
mutex m;

void decrease_counter(int thread_id){
    for (int a = 0; a < 6; a++){
        // Try to acquire the lock
        if (m.try_lock()) {
            cout << "Thread " << thread_id << " acquired the lock.\n";
            numbo--;          // Safely decrement numbo
            m.unlock();        // Unlock the mutex
        } else {
            // If lock is not acquired, print a message
            cout << "Thread " << thread_id << " could not acquire the lock, doing other work...\n";
            // Simulate doing other work by sleeping
            this_thread::sleep_for(chrono::milliseconds(20));
        }
    }
}

int main() {
    // Create two threads and pass unique IDs to them
    thread t1(decrease_counter, 1);
    thread t2(decrease_counter, 2);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Print the final value of numbo
    cout << "Final value of numbo: " << numbo << endl;
    return 0;
}

// Results:Thread Thread 1 acquired the lock.
//Thread 1 acquired the lock.
//Thread 1 acquired the lock.
//Thread 1 acquired the lock.
//Thread 1 acquired the lock.
//Thread 1 acquired the lock.
//2 could not acquire the lock, doing other work...
//Thread 2 acquired the lock.
//Thread 2 acquired the lock.
//Thread 2 acquired the lock.
//Thread 2 acquired the lock.
//Thread 2 acquired the lock.
//Final value of numbo: 9

// The results should be 8 if they ran completely correct.
// This result is exactly what you should expect with try_lock(). The final value of numbo will depend on how many times each thread manages to successfully acquire the lock, and since some lock acquisition attempts fail, the total number of decrements can be less than 12 (the expected value if both threads always succeed).
