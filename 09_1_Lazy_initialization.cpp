// Editted by Ali Behfarnia on 10/24.

// Lazy initialization:
// It defers the creation of an object or resource until it is actually needed.

// Notes:
// 1) On-Demand Creation: The resource is created only when it is first accessed.
// 2) Resource Optimization: Reduces the memory footprint by avoiding unnecessary object creation.
// 3) Improved Performance: Can lead to faster startup times since not all resources are initialized upfront.

#include <iostream>
#include <memory> // Includes smart pointers like unique_ptr to manage the memory automatically.
#include <vector> // vector class to store signals.

using namespace std;


class SignalProcessor {
public:
    SignalProcessor() {
        // Simulate an expensive initialization (say configuring DSP hardware)
        cout << "Signal Processor initialized!" << endl;
    }

    //Adding const ensures that the function does not modify the vector signal.
    // passing the vector by reference (&) to avoid making a copy
    void print_signal(const vector<int>& signal) {
        cout << "Processing signal: ";
        for (int val : signal) {
            cout << val << " ";
        }
        cout << endl;
    }
};

class CommunicationSystem {
private:
    unique_ptr<SignalProcessor> signal_Processor;  // Lazy-initialized signal processor
    // This smart pointer holds the SignalProcessor object.
    // Initially, it’s set to nullptr, meaning no signal processor is created until a signal is received.
public:
    
    void receiveSignal(const vector<int>& signal) {
        // Lazy initialization: Signal processor is only initialized when needed
        if (!signal_Processor) {
            signal_Processor = make_unique<SignalProcessor>();
        }

        // Process the received signal
        signal_Processor->print_signal(signal);
    }
};

int main() {
    CommunicationSystem commSystem;

    // No signal processor initialized yet
    cout << "Receiving first signal..." << endl;
    vector<int> signal1 = {1, 2, 3, 4, 5};
    commSystem.receiveSignal(signal1);  // Signal processor initialized here

    // Receiving another signal
    cout << "Receiving second signal..." << endl;
    vector<int> signal2 = {6, 7, 8, 9, 10};
    commSystem.receiveSignal(signal2);  // Reuses the initialized signal processor

    return 0;
}

// Receiving first signal...
// Signal Processor initialized!
// Processing signal: 1 2 3 4 5
// Receiving second signal...
// Processing signal: 6 7 8 9 10
