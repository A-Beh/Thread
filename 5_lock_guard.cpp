// Editted by Ali Behfarnia on 10/24.
// Lock_guard

// Lock_guard:
// It is used to automatically acquire a lock on a mutex when the lock_guard object is created and
// automatically release the lock when the lock_guard object goes out of scope.

// Key features: 1) Automatic Locking, 2) Automatic Unlocking, 
// 3) Resource Acquisition Is Initialization (e.g., release of resources like memory)
// 4) Exception Safety (this means the code behaves correctly even in the presence of exceptions, e.g., you want to ensure that the mutex is still released even though the program flow is interrupted.)

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex mtx;
int a = 0;
void criticalSection(int thread_id, int repeat_count) {
    lock_guard<std::mutex> lock(mtx);  // Lock is acquired here
    
    for (int i = 1; i <= repeat_count; ++i) {
        a++;
        cout << "Thread " << thread_id << " incrementing value: " << i << std::endl;
    }
    // The mutex will be automatically released when the function ends
}

int main() {
    int repeat_for_thread1 = 5;  // Define how many times thread 1 will repeat
    int repeat_for_thread2 = 7;  // Define how many times thread 2 will repeat

    thread t1(criticalSection, 1, repeat_for_thread1);  // Thread 1 repeats 5 times
    thread t2(criticalSection, 2, repeat_for_thread2);  // Thread 2 repeats 7 times

    t1.join();
    t2.join();

    cout<< "Final number for the a: "<< a <<endl;
    return 0;
}
