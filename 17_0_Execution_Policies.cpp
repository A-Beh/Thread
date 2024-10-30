
// Editted by Ali Behfarnia on 10/24.

// Sequential Policy: Executes the loop sequentially, element by element.
// Vectorized Policy: Utilizes SIMD* instructions to process multiple elements simultaneously in a single core.
// Parallel Policy: Splits the workload across multiple threads to achieve parallelism.
// Parallel + Vectorized Policy: Combines both threading and SIMD for enhanced performance.
// (* SIMD stands for Single Instruction, Multiple Data.)

// Note: Error
// Policies (seq, par, unseq, and par_unseq) are part of the C++17 and later standards.
// Not yet on Xcode Compiler


#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>  // Include for execution policies

using namespace std;

int main() {
    // Initialize a vector with some values
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 1) Sequential Policy - processes elements one at a time, in order
    for_each(execution::seq, numbers.begin(), numbers.end(), [](int &n) { n *= 2; });
    cout << "Sequential Policy Result: ";
    for (const auto &n : numbers) cout << n << " ";
    cout << endl;

    // Uncomment each section below to test other execution policies:

    // 2) Vectorized Policy - leverages SIMD (Single Instruction, Multiple Data) for better performance
    /*
    for_each(execution::unseq, numbers.begin(), numbers.end(), [](int &n) { n *= 2; });
    cout << "Vectorized Policy Result: ";
    for (const auto &n : numbers) cout << n << " ";
    cout << endl;
    */

    // 3) Parallel Policy - distributes processing across multiple threads
    /*
    for_each(execution::par, numbers.begin(), numbers.end(), [](int &n) { n *= 2; });
    cout << "Parallel Policy Result: ";
    for (const auto &n : numbers) cout << n << " ";
    cout << endl;
    */

    // 4) Parallel + Vectorized Policy - combines threading with SIMD for maximum parallelism
    /*
    for_each(execution::par_unseq, numbers.begin(), numbers.end(), [](int &n) { n *= 2; });
    cout << "Parallel + Vectorized Policy Result: ";
    for (const auto &n : numbers) cout << n << " ";
    cout << endl;
    */

    return 0;
}
