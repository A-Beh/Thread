// Editted by Ali Behfarnia on 10/24.

// Monitor Class
// It is a programming construct that helps manage access to shared resources among multiple threads in a safe and organized way.
// A monitor class encapsulates both the shared resource and the mechanisms to synchronize access to that resource (e.g., mutex).

// Private usually includes: i) shared data, ii) mutex, iii) condition variables (optionally)


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class CounterMonitor {
    
private:
    int count;                        // Shared data
    mutex m;                        // Mutex for synchronization
    condition_variable cv;            // Condition variable for waiting
    
public:
    CounterMonitor() {
        count = 0;
    }


    void increment() {
        lock_guard<mutex> lock(m);
        ++count;
        cv.notify_all();  // Notify any waiting threads
    }

    void decrement() {
        lock_guard<mutex> lock(m);
        --count;
        cv.notify_all();  // Notify any waiting threads
    }

    int get_count() {
        lock_guard<mutex> lock(m);
        return count;
    }

    // Wait until the count reaches a specific value
    void wait_for_count(int target) {
        unique_lock<mutex> lock(m);
//      [&] is used to capture all outer-scope variables by reference, which means that both count and target are captured by reference.
        cv.wait(lock, [&]() { return count == target; });
    }

};

void incrementTask(CounterMonitor& monitor) {
    for (int i = 0; i < 5; ++i) {
        monitor.increment();
        cout << "Incremented, count: " << monitor.get_count() << endl;
    }
}

void decrementTask(CounterMonitor& monitor) {
    for (int i = 0; i < 5; ++i) {
        monitor.decrement();
        cout << "Decremented, count: " << monitor.get_count() << endl;
    }
}

int main() {
    CounterMonitor monitor;

    thread t1(incrementTask, ref(monitor));
    thread t2(decrementTask, ref(monitor));

    t1.join();
    t2.join();

    cout << "Final count: " << monitor.get_count() << endl;
    return 0;
}


// Results:
// Decremented, count: 0
// Decremented, count: -1
// Decremented, count: -2
// Decremented, count: -3
// Decremented, count: -4
// Incremented, count: -4
// Incremented, count: -3
// Incremented, count: -2
// Incremented, count: -1
// Incremented, count: 0
// Final count: 0
