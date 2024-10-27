// Editted aby Ali Behfarnia

// Spin Lock:
// A spin lock is a type of lock where a thread repeatedly checks a condition until it can acquire the lock.

// Notes:
// a. It is an alternate to locking a mutex or using a conditional variable.
// b. It is basically an infinite loop.
// c. We can use atomic_flag to implement a basic spin lock.
// d. test_and_set() is used to return true/false of the flag.

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::literals;

atomic_flag my_flag = ATOMIC_FLAG_INIT; // It's initialized to false. Using the flag has less overlead.

void task(int n)
{
    // Returns true if another thread set the flag
    // Returns false if this thread set the flag
    while (my_flag.test_and_set()) {}
    
    std::this_thread::sleep_for(50ms);     // do some work
    std::cout << "I'm a task with argument " << n << '\n';
        
    // Clear the flag, so another thread can set it
    my_flag.clear();
}

int main()
{
    std::vector<std::thread> threads;
    
    for (int i = 1; i <= 5; ++i)
        threads.push_back(std::thread(task, i));
    
    for (auto& thr : threads)
        thr.join();
}
