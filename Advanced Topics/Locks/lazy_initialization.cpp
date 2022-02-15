#include <bits/stdc++.h>      
#include <thread>        
#include <mutex>         
#include <condition_variable>
using namespace std;

class X 
{
private:
    mutable std::once_flag initDataFlag;
    void initData() const {
        // do initialization
    }
public:
    void getData() const {
        call_once(initDataFlag, &X::initData, this);
        // do work
    }
};

/* Sometimes multi threads might not need some functionality that should get processed whenever the first thread needs it. 
A typical example is lazy initialization: the first time one of the threads needs sth that has to get processed, 
you process it (but not before, because u want to save the time to process it if it is not needed). 

The 1st argument passed to call_once() must be the crspding once_flag; further arguments are the usual arguments for callable objects: 
func, member func, func obj, or lambda, plus optional arguments for the func called. 
Thus, lazy initialization of an obj used in multi-threads might as follow. */