// Created by Ali Behfarnia on 10/24.

// Timed Mutex:
// A timed mutex is a type of mutex that allows you to try locking it for a specified amount of time.
// This avoid waiting indefinitely if the lock is not available within the given time.

// Methods:
// 1. try_lock_for(duration): Attempts to lock the mutex within the duration period.
// 2.try_lock_until(time_point): Attempts to lock the mutex until a specific deadline in time.


// ===================================
// Example: try_lock_for()
// ===================================
 
#include <iostream>
 #include <thread>
 #include <mutex>
 #include <chrono>
 using namespace std;

 int numbo = 12;
 timed_mutex m;

 void decrement(int i, int work_time, int wait_time) {
     cout << "Thread " << i << ": Trying to lock the mutex..." << endl;
     if(m.try_lock_for(chrono::seconds(wait_time))){
         numbo--;
         this_thread::sleep_for (chrono::seconds(work_time));
         cout << "Thread " << i << " Entered" << endl;
         m.unlock();
         cout << "Thread " << i << ": Work done, mutex unlocked!\n";
     }else{
         cout << "Thread " << i << ": Couldn't acquire the lock within " << wait_time << " seconds.\n";
     }
 }

 int main() {
     // The watining times are set up such that if t1 acquire the lock the t2 cannot acquire becasue its waiting time is less
     thread t1(decrement, 1, 4, 2);
     thread t2(decrement, 2, 1, 1);

     t1.join();
     t2.join();

     cout << numbo << endl;
     return 0;
 }


// ===================================
// Example: try_lock_until()
// ===================================
//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <chrono>
//using namespace std;
//
//int numbo = 12;
//timed_mutex m;
//
//void decrement(int i, int work_time, int wait_seconds) {
//    cout << "Thread " << i << ": Trying to lock the mutex until a specific time point..." << endl;
//
//    // Create a time point in the future (current time + wait_seconds)
//    auto timeout_time = chrono::steady_clock::now() + chrono::seconds(wait_seconds);
//
//    // Try to lock the mutex until the specified time point
//    if (m.try_lock_until(timeout_time)) {
//        numbo--;
//        this_thread::sleep_for(chrono::seconds(work_time));  // Simulate some work
//        cout << "Thread " << i << ": Entered and modified numbo.\n";
//        m.unlock();
//        cout << "Thread " << i << ": Work done, mutex unlocked!\n";
//    } else {
//        cout << "Thread " << i << ": Couldn't acquire the lock before the deadline of " << wait_seconds << " seconds.\n";
//    }
//}
//
//int main() {
//    // Thread 1 works for 4 seconds, and Thread 2 waits for 1 second before giving up
//    thread t1(decrement, 1, 4, 3);  // Thread 1 tries to lock until 3 seconds into the future
//    thread t2(decrement, 2, 1, 1);  // Thread 2 tries to lock until 1 second into the future
//
//    t1.join();
//    t2.join();
//
//    cout << "Final value of numbo: " << numbo << endl;
//    return 0;
//}

