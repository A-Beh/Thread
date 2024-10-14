// Editted 09/2024
// Sum of numbers with thread
// By: Ali Behfarnia

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int sum_e = 0;
int sum_o = 0;

// Function to calculate and return the sum of even numbers between a and b
void sumEven(int a, int b) {
    for (int e = a; e <= b; ++e) {
        if ((e & 1) == 0) {
            sum_e += e;
        }
    }
}

// Function to calculate and return the sum of odd numbers between a and b
void sumOdd(int a, int b) {
    for (int o = a; o <= b; ++o) {
        if ((o & 1) == 1) {
            sum_o += o;
        }
    }
}

int main() {
    int start = 0, finish = 1900;

    auto start_time = high_resolution_clock::now();

    // Create threads for summing even and odd numbers
    std::thread t1(sumEven, start, finish);
    std::thread t2(sumOdd, start, finish);

    // Join threads to wait for their completion
    t1.join();
    t2.join();

    auto stop_time = high_resolution_clock::now();
    auto duration_time = duration_cast<microseconds>(stop_time - start_time);

    cout << "Sum of Even Numbers: " << sum_e << endl;
    cout << "Sum of Odd Numbers: " << sum_o << endl;
    cout << "Duration of two functions with threads: " << duration_time.count() << " microseconds" << endl;

    return 0;
}
