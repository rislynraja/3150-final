#pragma once

#include "ControlTimedSharedPtr.h"

template<typename T>
class TimedSharedPtr {

    private:
        ControlTimedSharedPtr* _ptrToControl;

    public:

    TimedSharedPtr() : _ptrToControl(nullptr) {}

    TimedSharedPtr(T* raw, long deleteMeInMilliseconds ) 
      : _ptrToControl( new ControlTimedSharedPtr(raw, deleteMeInMilliseconds) )
    {}

    TimedSharedPtr(T* raw) : TimedSharedPtr(raw, 1000) {} // default to 1000 - i rewrote the other constructor

    TimedSharedPtr(const TimedSharedPtr& other) { // copy constructor
        _ptrToControl = other._ptrToControl;
        if (_ptrToControl)
            ++_ptrToControl->myUseCount;
    }

    ~TimedSharedPtr() { // implemented this !
        if (_ptrToControl) {
            --_ptrToControl->myUseCount;
            if (_ptrToControl->myUseCount == 0) {
                delete static_cast<T*>(_ptrToControl->ptr);
                delete _ptrToControl;
            }
        }
    }

    long use_count() const noexcept {
        return _ptrToControl ? _ptrToControl->myUseCount : 0;
    }

    T* get() const {
        if (!_ptrToControl) return nullptr; // just in case - edge case

        auto milliseondsSinceStart = Clock::now().time_since_epoch() - _ptrToControl->TimedSharedPtrStartTime.time_since_epoch();
        if (milliseondsSinceStart > _ptrToControl->deletePtrInMs ) {
            cout << "Yeo! Expired " ;
            return nullptr;
            
        } else {
            return _ptrToControl ? static_cast<T*>(_ptrToControl->ptr) : nullptr;
        }
    }

};