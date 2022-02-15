#include <bits/stdc++.h>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <unistd.h>
using namespace std;

// This program provides a possible solution for first readers writers problem using mutex and semaphore.
// I have used 10 readers and 5 producers to demonstrate the solution. You can always play with these values.

sem_t wrt;
mutex m;
int cnt = 1;
int numreader = 0;

void writer(int wno)
{   
    sem_wait(&wrt);
    cnt = cnt*2 + 1;
    this_thread::sleep_for(std::chrono::seconds(wno + 1));
    printf("Writer no %d modified cnt to %d\n", wno, cnt);
    sem_post(&wrt);
}
void reader(int rno)
{   
    // Reader acquire the lock before modifying numreader
    unique_lock<mutex> ul(m);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); // If this id the first reader, then it will block the writer
    }
    ul.unlock();

    // Reading Section
    printf("Reader %d: read cnt as %d\n", rno, cnt);
    this_thread::sleep_for(std::chrono::seconds(rno*2 + 2));

    // Reader acquire the lock before modifying numreader
    ul.lock();
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    ul.unlock();
}
int main()
{   
    thread read[10], write[5];
    sem_init(&wrt, 0, 1);

    auto th1 = thread([&](){
        for(int i = 0; i < 5; i++) {
            write[i] = thread(writer, i);
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
    
    sem_destroy(&wrt);
    return 0;
}