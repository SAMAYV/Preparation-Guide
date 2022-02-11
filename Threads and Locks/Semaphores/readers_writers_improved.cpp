#include <thread>
#include <mutex>
#include <bits/stdc++.h>
#include <condition_variable>
using namespace std;

class Semaphore {
private:
    mutex mtx;
    condition_variable cv;
    int count;
public:
    Semaphore(int count_ = 0) : count(count_){}

    inline void wait(){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){
            return count > 0;
        });
        count--;
    }
    inline void notify(){
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

Semaphore rw_mtx(1);    // common to both reader and writer
Semaphore mtx(1);       // ensure mutual exclusion when variable read_count is updated
int read_count = 0;
int value = 0;          // the value for readers and writers

void reader(int rno)
{
    mtx.wait();
    read_count += 1;
    if(read_count == 1){
        rw_mtx.wait();
    }
    mtx.notify();

    printf("Reader %d: read value as %d\n", rno, value);
    this_thread::sleep_for(std::chrono::seconds(rno*2 + 2));
    
    mtx.wait();
    read_count -= 1;
    if(read_count == 0){
        rw_mtx.notify();
    }
    mtx.notify();
}
void writer(int wno, int v) 
{
    rw_mtx.wait();
    value = v;
    this_thread::sleep_for(std::chrono::seconds(wno % 3 + 1));
    printf("Writer no %d modified cnt to %d\n", wno, v);
    rw_mtx.notify();
}
int main()
{
    thread read[10], write[5];

    auto th1 = thread([&](){
        for(int i = 0; i < 5; i++) {
            write[i] = thread(writer, i, i*i);
        }
        for(int i = 0; i < 5; i++) {
            write[i].join();
        }
    });
    
    auto th2 = thread([&](){
        for(int i = 0; i < 10; i++) {
            read[i] = thread(reader, i);
        }
        for(int i = 0; i < 10; i++) {
            read[i].join();
        }
    });
    th1.join();
    th2.join();
    return 0;
}