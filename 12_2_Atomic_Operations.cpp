// Editted aby Ali Behfarnia

// Atomic Operations:
// 1. load(): Retrieves the current value atomically.
// 2. store(value): Sets a new value atomically.
// 3. exchange(value): Sets a new value and returns the old one in a single atomic operation.
// 4. fetch_add(value): Atomically adds and returns the old value. Similarly, for fetch_sub(value).
// 5. fetch_and(value), fetch_or(value), fetch_xor(value): Perform bitwise operations.

#include <iostream>
#include <atomic>

using namespace std;

int main() {
    atomic<int> x = 0;
    cout << "After initialization: x = " << x << '\n';
    
    // Atomic assignment to x
    x = 2;
    
    // Atomic assignment from x. y can be non-atomic
    int y = x;
    
    cout << "After assignment: x = " << x << ", y = " << y << '\n';
    
    x.store(3);
    cout << "After store: x = " << x.load() << '\n';
    
    cout << "Exchange returns the old value of the x: " << x.exchange(y) << '\n';
    cout << "After exchange: x = " << x << ", y = " << y << '\n';
}
