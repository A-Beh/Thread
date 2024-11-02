// Editted by Ali Behfarnia on 10/24.

// Semaphore:
// A semaphore is a synchronization mechanism used to control access to a shared resource by multiple threads,

// Notes:
// 1. Counter-Based Control: Semaphores maintain a count indicating the number of threads that can access a shared resource.
// 2. Acquire (wait): Decreases the semaphore count. It acts like .lock() in mutex.
// 3. Release (signal): Increases the semaphore count and wakes up a blocked thread if any waiting. Acts like .unblock() in mutex.
// 4. If zero, the calling thread is blocked until the semaphore is available.
// 5. Atomic Operations: acquire() and release() are typically implemented using atomic operations.

#include <iostream>
#include <thread>
#include <semaphore>  // C++20: std::counting_semaphore
#include <vector>

using namespace std;


counting_semaphore<3> sema(3); // <3> specifies the maximum count, and (3) specifies the initial count of the semaphore
//

void access_resource(int threadID) {
    sema.acquire();
    cout << "Thread " << threadID << " is accessing the resource.\n";
    this_thread::sleep_for(chrono::seconds(1)); // Simulate work by the thread
    cout << "Thread " << threadID << " has finished using the resource.\n";
    sema.release();
}

int main() {
    vector<thread> threads;
    
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(access_resource, i + 1); // Create 5 threads that attempt to access the resource
    }
    
    for (auto& t : threads) {
        t.join();
    }


// Sample Result:

// Thread 1 is accessing the resource.
// Thread 2 is accessing the resource.
// Thread 3 is accessing the resource.
// Thread 1 has finished using the resource.
// Thread 4 is accessing the resource.
// Thread 2 has finished using the resource.
// Thread 3 has finished using the resource.
// Thread 4 has finished using the resource.