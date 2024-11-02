// Editted by Ali Behfarnia on 10/24.

// Concurrent Queue:
// Motivation: std::queue is not suitable for use as a concurrent queue, Data race happens if
// the same instance is accessed from threads. Also, race condition between front() and pop()

// Concurrent Queue:
// It allows multiple threads to safely add (produce) and remove (consume) data from the same queue without causing race conditions or data corruption.
// It is a good idea to write a wrapper class, q instance, mutex and cv (optional)

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class ConcurrentQueue {
private:
    queue<int> q;
    mutex mtx;
    condition_variable cv;

public:
    void enqueue(int value) {
        lock_guard<mutex> lock(mtx);
        q.push(value);
        cv.notify_one(); // Notify one waiting thread
    }

    int dequeue() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return !q.empty(); }); // Wait until queue is not empty
        int value = q.front();
        q.pop();
        return value;
    }
};

void producer(ConcurrentQueue& cq) {
    for (int i = 0; i < 5; ++i) {
        cq.enqueue(i);
        cout << "Produced: " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    }
}

void consumer(ConcurrentQueue& cq) {
    for (int i = 0; i < 10; ++i) {
        int value = cq.dequeue();
        cout << "Consumed: " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate work
    }
}

int main() {
    ConcurrentQueue cq;
    thread t1(producer, ref(cq));
    thread t2(consumer, ref(cq));

    t1.join();
    t2.join();

    return 0;
}

// Sample Result:
//Produced: 1
//Consumed: 1
//Produced: 2
//Consumed: 2
//Produced: 3
//Produced: 4
//Consumed: 3
//Consumed: 4
