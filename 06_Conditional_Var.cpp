// Editted by Ali Behfarnia on 10/24.
// Conditional Variables

// Notes:
// Condition variables allow threads to wait for specific conditions to be met before proceeding.
// They prevent threads from continuously checking the condition in a busy loop (which wastes CPU cycles).
// The mutex prevents race conditions, and the condition variable ensures that the thread doesn't proceed until it's safe to do so.
// One Result: Coordination Between Threads

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;                          // Mutex for shared data protection
condition_variable cv;              // Condition variable to signal sensor data readiness
bool sensor_data_ready = false;     // Flag to indicate when sensor data is ready
int sensor_data = 0;                // Simulated sensor data


void read_sensor() {
    // Lock the mutex before modifying shared data
    unique_lock<mutex> lock(mtx);

    // Simulate sensor data reading
    cout << "1 - Reading sensor data..." << endl;
    this_thread::sleep_for(chrono::seconds(2));  // Simulating sensor read delay
    sensor_data = 75;                            // Simulating a temperature reading of 75°F

    // Sensor data is ready now
    sensor_data_ready = true;

    cout << "2 - Sensor data ready, notifying the processing thread...\n";
    cv.notify_one();                            // Notify the processing thread that sensor data is available
}


void process_data() {
    // Lock the mutex to safely check the condition
    unique_lock<mutex> lock(mtx);

    // Wait until sensor data is ready (sensor_data_ready == true)
    cv.wait(lock, [] ()->bool { return sensor_data_ready; });

    // Once data is ready, process it
    cout << "3 - Processing sensor data: " << sensor_data << "°C" << endl;

    // Simulate further data processing (e.g., sending to another module)
    this_thread::sleep_for(chrono::seconds(1));
    cout << "4 - Data processed successfully!\n";
}

int main() {
    // Create threads for reading sensor data and processing it
    thread sensor_thread(read_sensor);
    thread processing_thread(process_data);

    sensor_thread.join();
    processing_thread.join();
    
    return 0;
}
