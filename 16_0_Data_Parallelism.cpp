// Editted by Ali Behfarnia on 10/24.

// Parallelism:
// a. Task Parallelism:         Split tasks. E.g., Task A on core 1, Task B on core 2, and so on.
// b. Data Parallelism:         Data can be divided to several subsets
// c. Pipelining:               Performing dependent tasks sequentially
// d. Graph Parallelism:        Similar to the pipline but with graph of dependencies


// Example of Data Parallelism using async
// Test1: One vector with 16 elements are divided to 4 of 4 elements, and then the addition of all is obtained
// test2: One random vector with 1000 elements

#include <future>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::literals;

// Random number seed and generation
static mt19937 mt;
uniform_real_distribution<double> dist(0, 100);

// Compute the sum of a range of elements
double accum(double *beg, double *end) {
    return accumulate(beg, end, 0.0);
}



// Divide the data into 4 parts
double add_parallel(vector<double>& vec) {
    auto vec0 =&vec[0];
    auto vsize = vec.size();
    
    // Start the threads: Pass the subset's range as argument to the task function
    auto fut1 = async(launch::async, accum, vec0, vec0 + vsize/4);
    auto fut2 = async(launch::async, accum, vec0 + vsize/4, vec0 + 2*vsize/4);
    auto fut3 = async(launch::async, accum, vec0 + 2*vsize/4, vec0 + 3*vsize/4);
    auto fut4 = async(launch::async, accum, vec0 + 3*vsize/4, vec0+vsize);
    
    // Reduce step: Combine the results for each subset
    return fut1.get() + fut2.get() + fut3.get() + fut4.get();
}

int main() {
    // Populate a vector with elements 1, 2, ..., 16
    vector<double> vec(16);
    iota(vec.begin(), vec.end(), 1.0);
    
    // Populate a vector with 10,000 random elements
    vector<double> vrand(1000);
    generate(vrand.begin(), vrand.end(),
             []() { return dist(mt); });
    
    // Do the calculations
    cout << "Sum of first 16 integers: " << add_parallel(vec) << '\n';
    cout << "Sum of 10,000 random numbers: " << add_parallel(vrand) << '\n';
}

// Result:
// Sum of first 16 integers: 136
// Sum of 10,000 random numbers: 50107.9