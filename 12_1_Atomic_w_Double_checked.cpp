// Editted aby Ali Behfarnia

// Lazy Initialization with Double-Checked Locking:
// Double-checked locking guarantees that only one some_type object is created,
// even with multiple threads accessing process().

#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

using namespace std;

class some_type {
public:
    void do_it() {
        cout << "Doing work in thread " << this_thread::get_id() << endl;
    }
};

atomic<some_type *> ptr=nullptr;  // Variable to be lazily initialized
mutex m;

void process() {
    if (!ptr) {
        
        lock_guard<mutex> lk_g(m);
        
        if (!ptr) {
            cout << "Thread " << this_thread::get_id() << " is initializing ptr\n";
            ptr = new some_type;
        }
    }
    
    some_type *sp = ptr;
    sp->do_it(); // atomic type don't support . or -> operators
}

int main() {
    vector<thread> ts;
    
    for (int i = 0; i < 3; ++i)
        ts.push_back(thread{process});
        
    for (auto &t : ts)
        t.join();

    cout << "All threads have completed their work." << endl;
    return 0;
}
