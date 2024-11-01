// Editted by Ali Behfarnia on 10/24.

// shared_ptr:
// 1. Automatic Memory Management: It manages dynamic memory, ensuring the object is deleted automatically when no pointers remain.
// 2. Reference Counting: Each shared_ptr maintains an atomic reference count, allowing safe use across threads without needing locks for the pointer itself.
// 3. Pointer Ownership: The reference count is thread-safe, so creating or destroying copies is safe across threads.
// 4. Pointed-to Data: The data the shared_ptr points to is not thread-safe; concurrent modifications need explicit synchronization (e.g., a mutex).

#include <memory>
#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

// shared_ptr has an "atomic" reference counter
shared_ptr<int> shptr = make_shared<int>(42);

mutex m1;

void func1()
{
    // Potentially conflicting access - must be protected
    lock_guard<mutex> lgd(m1);
    *shptr = 5;
    cout << "shptr data: " << *shptr << '\n';
}

void func2()
{
    // Potentially conflicting access - must be protected
    lock_guard<mutex> lgd(m1);
    *shptr = 7;
    cout << "shptr data: " << *shptr << '\n';
}

int main()
{
    cout << "shptr data: " << *shptr << '\n';

    thread t1(func1);
    thread t2(func2);

    t1.join();
    t2.join();

}
