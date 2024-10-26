// Created by Ali Behfarnia on 10/24.

// Promise_Future Example
// Throw an exception

// In below code:
// 1. If data is valid, it calculates the average power by summing the squares of each sample and divides by the number of samples.
// 2. If the signal vector is empty, it throws a runtime_error, simulating an error in processing.
// 3. Sets the computed average power on resultPromise if successful, or sets an exception on it if an error occurs.

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <stdexcept>

using namespace std;

void calculate_signal_power(promise<double>&& result_promise, const vector<double>& signal_data) {
    try {
        if (signal_data.empty()) {
            throw runtime_error("Signal data is empty, cannot calculate power.");
        }
        double sum = 0;
        for (double sample : signal_data) {
            sum += sample * sample;  // Power calculation for each sample
        }
        double avg_power = sum / signal_data.size();
        result_promise.set_value(avg_power);
    } catch (...) {
        result_promise.set_exception(current_exception());
    }
}

int main() {
    vector<double> signal_data = {};  // Empty to simulate an error, catch; To avoid an error we can put an example like {2, 4, 8}
    promise<double> power_promise;
    future<double> power_future = power_promise.get_future();
    
    thread t1(calculate_signal_power, std::move(power_promise), cref(signal_data)); // cref constat reference

    try {
        // Get the result (or exception) from the future
        double avg_power = power_future.get();
        cout << "Average Signal Power: " << avg_power << " W" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    t1.join();
    return 0;
}

// Result:
// Error: Signal data is empty, cannot calculate power.

// =========================
// Async
// =========================

// Using async can reduce processing time in certain scenarios:
// 1. Parallelism: It allows independent tasks to run in parallel on multiple CPU
//                 cores, reducing the total execution time for CPU-bound tasks.
// 2. I/O-Bound: It lets program continue processing while doing for I/O operations

// #include <iostream>
// #include <vector>
// #include <future>
// #include <stdexcept>

// using namespace std;

// double calculate_signal_power(const vector<double>& signal_data) {
//     if (signal_data.empty()) {
//         throw runtime_error("Signal data is empty, cannot calculate power.");
//     }

//     // Calculate the power by summing squares of each sample
//     double sum = 0;
//     for (double sample : signal_data) {
//         sum += sample * sample;  // Power calculation for each sample
//     }
//     return sum / signal_data.size();  // Average power
// }

// int main() {
//     vector<double> signal_data = {1.0, 2.0, 3.0, 4.0};  // Example signal data

//     // Launch asynchronous task to calculate the signal power
//     future<double> power_future = async(launch::async, calculate_signal_power, cref(signal_data));

//     try {
//         // Retrieve the result of the asynchronous computation
//         double avg_power = power_future.get();
//         cout << "Average Signal Power: " << avg_power << " W" << endl;
//     } catch (const exception& e) {
//         cout << "Error: " << e.what() << endl;
//     }

//     return 0;
// }
