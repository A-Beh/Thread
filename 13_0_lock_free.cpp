// Editted Ali Behfarnia

// Lock free programmming
// A lock-free program is a multi-threaded program which does not rely on locking and unlocking mutexes.

// Pros:
// a. If done correctly, threads can never block each other
// b. No possibility of deadlock or livelock
// c. Useful if work must be completed within a time limit (e.g. real time systems)

// Cons:
// a. Programs can be hard to understand, with very subtle bugs.
// b. Can be very difficult to write correct, efficient lock-free code and data structures
// c. For many applications, the extra complexity is often not justified

// Example: Product and consumer
// Broken implementation of lock-free queue (has data race)


// Broken implementation of lock-free queue (has data race)
#include <vector>
#include <list>
#include <thread>
#include <iostream>

using namespace std;

template <typename T>
struct LockFreeQueue {
private:
    list<T> lst;
    typename list<T>::iterator iHead, iTail;

public:
    
    LockFreeQueue()
    {
        lst.push_back(T());
        iHead = lst.begin();
        iTail = lst.end();
    }

    // Producer thread function
    void Produce(const T& t)
    {
        lst.push_back(t);
        iTail = lst.end(); // Update iTail
        lst.erase(lst.begin(), iHead); // Erase the removed elements
    }

    // Consumer thread function
    bool Consume(T& t)
    {
        auto iFirst = iHead;     // Go to the first element
        ++iFirst;
        
        if (iFirst != iTail) { // If queue is not empty
            iHead = iFirst;
            t = *iHead;
            return true;
        }

        
        return false; // No elements to fetch
    }

    // Function to display all the elements
    void Print()
    {
        // Go to the first element
        auto head = iHead;
        ++head;

        // We cannot use a range-for loop, because we only access some of the elements
        for (auto el = head; el != iTail; ++el)
            cout << *el << ", ";
        cout << '\n';
    }
}; // End of class definition




void producerThread(LockFreeQueue<int>& queue)
{
    for (int i = 1; i <= 10; ++i) {
        queue.Produce(i);
        this_thread::sleep_for(chrono::milliseconds(50)); // Small delay to simulate production time
    }
}

void consumerThread(LockFreeQueue<int>& queue)
{
    int value;
    for (int i = 1; i <= 10; ++i) {
        if (queue.Consume(value)) {
            cout << "Consumed: " << value << endl;
        } else {
            cout << "Queue empty, nothing to consume." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(80)); // Small delay to simulate consumption time
    }
}

int main()
{
    LockFreeQueue<int> lfq;

    thread producer(producerThread, ref(lfq));
    thread consumer(consumerThread, ref(lfq));

    producer.join();
    consumer.join();

    cout << "Final queue contents: ";
    lfq.Print();

    return 0;
}
