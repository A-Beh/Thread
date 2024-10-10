// Editted 09/2024
// Sum of numbers without thread
// By: Ali Behfarnia

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int sum_e = 0;
int sum_o = 0;

void sumEven(int a, int b, int& result) {
    for (int e = a; e <= b; ++e) {
        if ((e & 1) == 0) {
            result += e;
        }
    }
}
void sumOdd(int a, int b, int& result) {
    for (int o = a; o <= b; ++o) {
        if ((o & 1) == 1) {
            result += o;
        }
    }
}

int main() {
    int start = 0, finish = 1900;

    auto start_time = high_resolution_clock::now();

    // Create threads for summing even and odd numbers
//    std::thread t1(sumEven, start, finish);
//    std::thread t2(sumOdd, start, finish);

    int even_sum = 0, odd_sum = 0;
    std::thread t1(sumEven, start, finish, std::ref(even_sum));
    std::thread t2(sumOdd, start, finish, std::ref(odd_sum));
    
    // Join threads to wait for their completion
    t1.join();
    t2.join();

    auto stop_time = high_resolution_clock::now();
    auto duration_time = duration_cast<microseconds>(stop_time - start_time);
    
    cout << "Sum of Even Numbers: " << sum_e << endl;
    cout << "Sum of Odd Numbers: " << sum_o << endl;
    cout << "Duration of two functions with threads: " << duration_time.count() << " microsecond"<< endl;

    return 0;
}
