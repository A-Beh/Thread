// Created by Ali Behfarnia on 10/24.

// 1) Passing by Move: (Explicit Move)
// In C++, certain objects like std::thread are move-only. This means they cannot be copied but can be moved from one context to another.
// std::thread cannot be copied because each thread object represents a unique system resource, allowing multiple thread objects to manage the same system thread would lead to problems.
// When we move an object (using std::move), we transfer its resources (like memory or a thread handle) to another object.

// 2) Return by fucntion object: (Implicit Move)
// In this case, the thread is created locally within the function and then returned to the caller.
// The ownership remains in the main() and so the .join() should be be done in the main().

// =============================
// Explicit Move: The owenership is for processThread() function
// =============================

#include <thread>
#include <iostream>

using namespace std;

// Task function to print numbers
void printNumbers() {
    for (int i = 1; i <= 3; ++i) {
        cout << "Number: " << i << endl;
    }
}

// Function that takes ownership of the thread
void processThread(thread thr) {
    cout << "Processing thread with ID " << thr.get_id() << endl;

    // Ensure the thread finishes by calling join()
    thr.join();
}

int main() {

    // Create a thread to print numbers
    thread t1(printNumbers);

    // Pass the thread to the function by moving it
    processThread(std::move(t1));

    // Display the thread's ID in main
    cout << "Number printing thread has ID " << t1.get_id() << endl;
    
    return 0;
}

// =============================
// Implicit Move: Returning thread object
// The owenership is for main() function
// =============================


//#include <iostream>
//#include <thread>
//#include <chrono>
//
//using namespace std;
//
//void hello() {
//    std::cout << "Hello, Thread!\n";
//}
//
//
//thread func() {
//    // Start the thread
//    thread thr(hello);
//
//    // Return a local variable
//    return thr;
//
//    // Return a temporary object
//    // return std::thread(hello);
//}
//
//int main() {
//    // Call a function which return an std::thread object
//    thread t1 = func();
//
//    // Our thr object now "owns" the system thread
//    // It is responsible for calling join()
//    t1.join();
//    
//    cout << "Received thread with ID is: " << t1.get_id() << '\n';
//}
