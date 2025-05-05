#pragma once // instead of doing the ifndef endif thing

#include <chrono>
#include <iostream>

using namespace std;

using Clock = chrono::high_resolution_clock;
typedef chrono::time_point<Clock> clockTime;
typedef chrono::milliseconds milliSeconds;

struct ControlTimedSharedPtr { // heap based control structure
    void *          ptr; // the pointer itself
    long            myUseCount; // the pointer's use count
    clockTime       TimedSharedPtrStartTime; // creation time
    milliSeconds    deletePtrInMs; // time to expire

    ControlTimedSharedPtr(void * p, long deleteMeInMilliseconds) : ptr(p), 
                                                        myUseCount(1),
                                                        TimedSharedPtrStartTime(Clock::now()),
                                                        deletePtrInMs{milliSeconds(deleteMeInMilliseconds)}
                                                        { 
        cout << "ControlTimedSharedPtr " << ptr
             << " start: " << chrono::duration_cast<chrono::milliseconds>(Clock::now() - TimedSharedPtrStartTime).count() 
             << " ms " << endl;
    }

    ~ControlTimedSharedPtr() {
        cout << "ControlTimedSharedPtr " << ptr // modified from static_cast<void *>(ptr)
             << " end: " 
             << chrono::duration_cast<chrono::milliseconds>(Clock::now().time_since_epoch() - TimedSharedPtrStartTime.time_since_epoch()).count() 
             << " ms " << endl;
    }
};