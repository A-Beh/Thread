//  main.cpp
//  Sample1_Multi-Thread: weather example
//  Created by Ali Behfarnia on 09/28/24.

#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono_literals;

void RefreshForcast(map<string, int>& forecastMap){ // Pass by reference
    while(true){
        for(auto& item: forecastMap){
            item.second++;
            cout<< item.first << " - " <<item.second <<endl;
            
            this_thread::sleep_for(2000ms);
        }
    }
}

int main() {
    map<string, int> forecastMap = {
        {"NY", 67},
        {"TN", 90},
        {"CA", 74}
    };
    thread bckworker(RefreshForcast, ref(forecastMap)); // Use std::ref to pass by reference

    // cin.get() to wait for user input on macOS or Linux
    cin.get();  // Wait for Enter key before the program ends
}
