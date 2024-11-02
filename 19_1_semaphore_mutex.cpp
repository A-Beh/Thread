// Editted by Ali Behfarnia on 10/24.

// Why Mutex with Semaphores?
// When accessing or modifying shared resources involves more than a single atomic operation,
// a mutex provides additional protection around this sequence.

// In this example, threads are adding elements to a shared std::vector.
// The semaphore limits the number of threads that can access the critical section at any given time.
// However, the mutex ensures that only one thread can modify the vector safely.

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore>

using namespace std;

vector<int> shared_data;
counting_semaphore<3> sem(3); // Semaphore allows up to 3 threads in the critical section
mutex m;                      // Mutex to protect sharedData vector

void add_data(int value) {
    sem.acquire();            // Only 3 threads can enter the critical section at a time
    {
        lock_guard<mutex> lock(m); // Ensures exclusive access to sharedData
        shared_data.push_back(value);
        cout << "Thread " << this_thread::get_id() << " added " << value << endl;
    }
    sem.release(); // Release permit, allowing another thread to enter
}

int main() {
    const int num_threads = 6;
    vector<thread> t;

    // Launch threads to add data to sharedData
    for (int i = 0; i < num_threads; ++i) {
        t.push_back(thread(add_data, i * 10)); // Each thread adds a multiple of 10
    }

    // Join threads
    for (auto& thr : t) {
        thr.join();
    }

    // Print the shared data
    cout << "Final shared data: ";
    for (const auto& val : shared_data) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

// Sample Results:
// Thread 0x700002d40000 added 20
// Thread 0x700002c3a000 added 0
// Thread 0x700002e46000 added 40
// Thread 0x700002ec9000 added 50
// Thread 0x700002dc3000 added 30
// Thread 0x700002cbd000 added 10
// Final shared data: 20 0 40 50 30 10
// Program ended with exit code: 0
