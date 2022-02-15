#include <bits/stdc++.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <string_view>
using namespace std;

mutex g_lockprint;
const int no_of_philosophers = 5;

class fork
{
public:
    mutex mutex;
};

class table
{
public:
    atomic<bool> ready{false};
    vector<fork> forks;
    table() {
        forks.clear();
        forks.resize(no_of_philosophers, fork());
    }
};

class philosopher
{
private:
    string const name;
    table const &dinnertable;
    fork &left_fork;
    fork &right_fork;
    thread lifethread;

public:
    philosopher(string n, table const& t, fork& l, fork& r) 
    : name(n), dinnertable(t), left_fork(l), right_fork(r), lifethread(&philosopher::dine, this) {}

    ~philosopher() {
        lifethread.join();
    }
    void dine()
    {
        while(!dinnertable.ready);
        do {
            think();
            eat();
        }
        while(dinnertable.ready);
    }
    void print(string_view text)
    {
        lock_guard<mutex> cout_lock(g_lockprint);
        cout << left << setw(10) << " " << name << text << endl;
    }
    /* eat() is the method that models the eating. The left and right forks are acquired in a deadlock free manner using std::lock. 
    After the forks, i.e. mutexes, are acquired, their ownership is transfered to a std::lock_guard object, 
    so that the mutexes are correctly released when the function returns. Eating is simulated with a sleep. */
    void eat()
    {
        lock(left_fork.mutex, right_fork.mutex);

        lock_guard<mutex> left_lock(left_fork.mutex, adopt_lock);
        lock_guard<mutex> right_lock(right_fork.mutex, adopt_lock);

        print(" started eating.");
        this_thread::sleep_for(chrono::milliseconds((rand() % 100) * 50));
        print(" finished eating.");
    }
    void think()
    {
        this_thread::sleep_for(chrono::milliseconds((rand() % 100) * 150));
        print(" is thinking ");
    }
};
void dine()
{
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Dinner started!" << endl;
    {
        table table;
        vector<philosopher> philosophers = {
            { "Aristotle", table, table.forks[0], table.forks[1] },
            { "Platon",    table, table.forks[1], table.forks[2] },
            { "Descartes", table, table.forks[2], table.forks[3] },
            { "Kant",      table, table.forks[3], table.forks[4] },
            { "Nietzsche", table, table.forks[4], table.forks[0] },
        };
        table.ready = true;
        this_thread::sleep_for(chrono::seconds(5));
        table.ready = false;
    }
    cout << "Dinner done!" << endl;
}
int main()
{   
    dine();
    return 0;
}