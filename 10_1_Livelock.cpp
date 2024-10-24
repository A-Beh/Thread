//  Created by Ali Behfarnia on 10/24.

// Livelock:
// It is a situation in multithreading where two or more threads are actively responding to each other's
// actions, but none of them is able to make progress.

// Unlike a deadlock, threads are not blocked, but they constantly change their states in response to each other, 
// leading to no useful work being done.

// ************
// Solution
// A common solution to avoid livelock is to introduce some level of random delay or a more sophisticated locking
// mechanism like lock hierarchy or back-off strategy. 


// ************
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex freq_band_A, freq_band_B;

void transmitter1() {
    while (true) {
        if (freq_band_A.try_lock()) {
            if (freq_band_B.try_lock()) {
                // Both frequency bands acquired
                cout << "Transmitter 1 is sending data...\n";
                this_thread::sleep_for(chrono::milliseconds(100)); // Simulate transmission time
                
                // Release frequency bands
                freq_band_B.unlock();
                freq_band_A.unlock();
                break;
            } else {
                // Couldn't get both frequency bands, release and retry
                freq_band_A.unlock();
                cout << "Transmitter 1 couldn't get both frequency bands, retrying...\n";
                this_thread::sleep_for(chrono::milliseconds(50)); // Wait before retrying
            }
        }
    }
}

void transmitter2() {
    while (true) {
        if (freq_band_B.try_lock()) {
            if (freq_band_A.try_lock()) {
                // Both frequency bands acquired
                cout << "Transmitter 2 is sending data...\n";
                this_thread::sleep_for(chrono::milliseconds(100)); // Simulate transmission time
                
                // Release frequency bands
                freq_band_A.unlock();
                freq_band_B.unlock();
                break;
            } else {
                // Couldn't get both frequency bands, release and retry
                freq_band_B.unlock();
                cout << "Transmitter 2 couldn't get both frequency bands, retrying...\n";
                this_thread::sleep_for(chrono::milliseconds(50)); // Wait before retrying
            }
        }
    }
}

int main() {
    // Two threads represent two RF transmitters trying to send data over two shared frequency bands
    thread t1(transmitter1);
    thread t2(transmitter2);

    t1.join();
    t2.join();

    return 0;
}
