// Editted by Ali Behfarnia on 10/24.
// Unique_guard

// Unique_guard:
// It can be used to lock and unlock a mutex explicitly, giving more control over the locking mechanism.
// unique_lock is a more flexible for handling locks compared to lock_guard

// Notes:
// It Allows using try_lock_for, try_lock_until
// It allows using defer_lock, try_try_to_lock, etc.

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;  // Shared mutex
int a = 0;  // Shared variable
const int repeat_count = 5; // Number of increments

void criticalSection(int thread_id) {
    unique_lock<mutex> lock(mtx, defer_lock);  // Create lock without acquiring the mutex

    cout << "Thread " << thread_id << " is doing some work outside the critical section\n";

    // Lock the mutex explicitly when needed
    lock.lock();
    cout << "Thread " << thread_id << " in critical section\n";

    // Loop to increment the shared variable 'a'
    for (int i = 1; i <= repeat_count; ++i) {
        a++;
        cout << "Thread " << thread_id << " incrementing value to: " << a << endl;
    }

    // Automatically unlock when 'lock' goes out of scope
}

int main() {
    thread t1(criticalSection, 1);
    thread t2(criticalSection, 2);

    t1.join();
    t2.join();

    cout << "Final value of a: " << a << endl; // Print the final value of 'a'
    return 0;
}
