// Editted by Ali Behfarnia on 10/24.
// Lost_wakeup

// A lost wakeup occurs in multithreading when a thread sends a notification before another thread begins waiting on a condition variable.
// As a result, the waiting thread never receives the notification and remains blocked indefinitely

// Solution?
// Use a Boolean Flag. For example, using "data_ready" boolean flag. Once the signal generated we put "data_ready = true" in function, then
// we use "cond_var.wait(lock, [] { return data_ready; });" in the other fucntion to check the flag before waiting, so it only waits if the condition is true


#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::chrono;
using namespace std;


string signal_data; // The shared signal data
mutex mut;          // Mutex to protect critical sections
condition_variable cv; // Condition variable for synchronization


// Generator thread that generates signal data
void signalGenerator()
{
    lock_guard<mutex> lck_guard(mut);
    cout << "Signal Generator has locked the mutex\n";
    this_thread::sleep_for(2s); // Simulate data generation delay
    cout << "Signal Generator generating signal data...\n"; // Modify the signal data
    signal_data = "QAM_generated";
    cout << "Signal Generator sends notification\n";        // Notify the Signal Processor
    cv.notify_one();
}


void signalProcessor() // Processor thread that processes the received signal
{
    cout << "Signal Processor locking mutex\n";
    unique_lock<mutex> uniq_lck(mut);
    cout << "Signal Processor has locked the mutex\n";
    
    cout << "Signal Processor waiting for signal data...\n";
    cv.wait(uniq_lck);

    // Woken up and mutex re-locked
    cout << "Signal Processor wakes up and processes the data\n";

    // Process the new signal data
    cout << "Processing signal data: \"" << signal_data << "\"\n";
}



int main()
{
    
    signal_data = "NoSignal";

    
    cout << "Initial Signal Data: \"" << signal_data << "\"\n";

    // Start the threads
    // If the generator sends a notification before the processor waits, the notification is lost
    thread t1(signalGenerator);
    this_thread::sleep_for(500ms); // This delay helps to simulate the lost_wakeup
    thread t2(signalProcessor);

    t1.join();
    t2.join();
}

// Result:
// Initial Signal Data: "NoSignal"
// Signal Generator has locked the mutex
// Signal Processor locking mutex
// Signal Generator generating signal data...
// Signal Generator sends notification
// Signal Processor has locked the mutex
// Signal Processor waiting for signal data...


