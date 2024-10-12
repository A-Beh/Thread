// Editted by Ali Behfarnia on 10/24.

// Goal: Practice the use of join, detach, and joinable in thread

// JOIN:
// 1. After starting a thread, use join() to wait for it to finish.
// 2. Calling join() twice will terminate the program, so check if the thread is joinable with joinable() before
//    calling join().

// DETACH:
// 1. Use detach() to separate a new thread from the parent thread, but always check if the thread is joinable before detaching to avoid program termination.
// 2. Detached threads will have their execution suspended if the main function returns before they finish.

// Resource management: leak memory with join/detach?
// Note: If we create a thread, we need to either put the join or detach for it.
// join() is generally preferred because it automatically handles resource reclamation, preventing memory leaks.
// detach() requires manual resource management to avoid leaks, and should be used with caution.


#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

// ===============================
// Join Practice
// ===============================

void func(int a) {
    while(a++ < 12)
        cout << a << " Samples." << endl;
    std::this_thread::sleep_for(chrono::seconds(6));
//    cout << "thread finished" << endl;
}

int main() {
    thread t1(func, 7);
    cout << "before the delay" << endl;
    t1.join(); // the join waits for the thread to be completed, then the program moves forward
    
    if (t1.joinable()){ // We use this joinable to see for example if join has been already used
        t1.join();      // as two join() over the same function terminates the program
    }
    cout << "after the delay" << endl;
    
    return 0;
}

// ===============================
// Detach Practice
// ===============================

//void func(int a) {
//    while(a++ < 12)
//        cout << a << " Samples." << endl;
////    std::this_thread::sleep_for(chrono::seconds(6));
//    cout << "thread finished" << endl;
//}
//
//
//int main() {
//    std::thread t1(func, 6);
//    cout << "before the delay" << endl;
//    t1.detach();
//    cout << "after the detach" << endl;
////    std::this_thread::sleep_for(chrono::seconds(5));
//    return 0;
//}
