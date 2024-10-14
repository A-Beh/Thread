//  Editted by Ali Behfarnia on 10/24.

// Goal: Practice of 5 different types of creating threads

// Note: If we create multiple threads simultaneosly;
//       it's not clear which one will run first.

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// ======================================
// 1. Function Pointer (basic form)
// ======================================

//void fun(int a){
//    while (a++ < 12){
//        cout<< a <<endl;
//    }
//}
//
//int main() {
//    
//    thread t1(fun, 5);
//    t1.join();
//
//    
//    return 0;
//}


// ======================================
// 2. Lambda Function
// ======================================

int main() {
    
    thread t1([](int a){
        while (a++ < 12){
            cout<< a <<endl;
        }
    }, 5);
    t1.join();
    
    return 0;
}

// ======================================
// 3. Function Object (Functor)
// ======================================

//class Base {
//public:
//    void operator()(int a){
//        while (a++ < 12){
//            cout<< a <<endl;
//        }
//    }
//};
//
//int main() {
//    thread t1((Base()),7);
//    t1.join();
//    return 0;
//}

// ======================================
// 4. Non-Static member function
// ======================================
// Requires an object, can access both static and non-static members.

//class func {
//public:
//    void run(int a){
//        while (a++ < 12){
//            cout<< a <<endl;
//        }
//    }
//};
//
//int main() {
//    func f;
//    thread t1(&func::run, &f, 7);
//    t1.join();
//    return 0;
//}

// ======================================
// 4. Static member function (we don't need any obkject and)
// ======================================
//  Does not require an object, can access only static members.

//class func {
//public:
//    static void run(int a){
//        while (a++ < 12){
//            cout<< a <<endl;
//        }
//    }
//};
//
//int main() {
//    thread t1(&func::run, 7);
//    t1.join();
//    return 0;
//}
