// Editted by Ali Behfarnia on 10/24.

// Shared_data_initialization
// It ensures that all threads have a consistent view of shared data
// It allows effective management of resources, such as memory allocation

// Application: It is particularly important when multiple threads
// will read from or write to the same data structures



#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

shared_mutex shmut; // Shared mutex for thread safety
vector<int> shared_data; // Shared data to be initialized

// Function to initialize shared data with random values
void initialize_data(int thread_id, int count) {
    
    lock_guard<shared_mutex> lck_guard(shmut);

    cout << "Thread " << thread_id << " is initializing data." << endl;
    
    // Simulate some work (e.g., random data generation)
    std::default_random_engine generator(thread_id);
    std::uniform_int_distribution<int> distribution(1, 100); // Random numbers between 1 and 100

    for (int i = 0; i < count; ++i) {
        int value = distribution(generator);
        shared_data.push_back(value);                       // Initialize shared data
        this_thread::sleep_for(chrono::milliseconds(50));   // Simulate some delay
    }

    cout << "Thread " << thread_id << " finished initializing data." << endl;
}

int main() {
    const int thread_count = 2; // Number of threads
    const int data_count = 4; // Number of data elements to initialize per thread

    
    vector<thread> t;
    for (int i = 0; i < thread_count; ++i) {
        t.push_back(thread(initialize_data, i + 1, data_count));
    }

    // Join threads
    for (auto& thr : t) {
        thr.join();
    }

    // Print the initialized shared data
    cout << "Shared Data: ";
    for (const auto& val : shared_data) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

// Result:
// Thread 1 is initializing data.
// Thread 1 finished initializing data.
// Thread 2 is initializing data.
// Thread 2 finished initializing data.
// Shared Data: 15 98 70 35 30 68 13 99 
