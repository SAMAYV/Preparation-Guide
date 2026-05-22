/* Synchrosizing Operations */
#include "stdafx.h"

#include <deque>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

deque<int> q;
mutex mu;

void function_1() {
	int count = 10;
	while (count > 0) {
		unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function_2() {
	int data = 0;
	while ( data != 1) {
		unique_lock<mutex> locker(mu);
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "t2 got a value from t1: " << data << endl;
		} else {
			locker.unlock();
		}
		this_thread::sleep_for(chrono::milliseconds(10));
	}
}
// It is hard to set the sleep time.
int main() {
	thread t1(function_1);
	thread t2(function_2);
	t1.join();
	t2.join();
	return 0;
}



// Using conditional variable and mutex
void function_1() {
	int count = 10;
	while (count > 0) {
		unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		cond.notify_one();  // Notify one waiting thread, if there is one.
		this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function_2() {
	int data = 0;
	while ( data != 1) {
		unique_lock<mutex> locker(mu);
		cond.wait(locker, [](){ return !q.empty();} );  // Unlock mu and wait to be notified
		// if queue is empty after being notified, it will sleep again until notified.
		// relock mu after being notified
		data = q.back();
		q.pop_back();
		locker.unlock();
		cout << "t2 got a value from t1: " << data << endl;
	}
}







/* For threads to return values: future */
int factorial(int N) {
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	//future<int> fu = async(factorial, 4); 
	future<int> fu = async(launch::deferred | launch::async, factorial, 4); // default: implementation defined
	// future<int> fu2 = async(launch::deferred, factorial, 4); // deferred: lazy evaluation in same thread, async: create a child thread
	cout << "Got from child thread #: " << fu.get() << endl;
	// fu.get();  // crash
	return 0;
}



/* Asynchronously provide data with promise */
int factorial(future<int>& f) {
	// do something else

	int N = f.get();     // If promise is distroyed, exception: future_errc::broken_promise
	cout << "Got from parent: " << N << endl; 
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	promise<int> p;
	future<int> f = p.get_future();
	p.set_value(5); // providing data from parent to child thread

	future<int> fu = async(launch::async, factorial, ref(f));

	// Do something else
	this_thread::sleep_for(chrono::milliseconds(20));
	//p.set_value(28);  // It can only be set once
	p.set_exception(make_exception_ptr(runtime_error("To error is human")));

	cout << "Got from child thread #: " << fu.get() << endl;
	return 0;
}




/* shared_future */
int factorial(shared_future<int> f) {
	// do something else

	int N = f.get();     // If promise is distroyed, exception: future_errc::broken_promise
	f.get();
	cout << "Got from parent: " << N << endl; 
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	// Both promise and future cannot be copied, they can only be moved.
	promise<int> p;
	future<int> f = p.get_future();
	shared_future<int> sf = f.share();

	future<int> fu = async(launch::async, factorial, sf);
	future<int> fu2 = async(launch::async, factorial, sf);

	// Do something else
	this_thread::sleep_for(chrono::milliseconds(20));
	p.set_value(5);

	cout << "Got from child thread #: " << fu.get() << endl;
	cout << "Got from child thread #: " << fu2.get() << endl;
	return 0;
}










/* async() are used in the same ways as thread(), bind() */
class A {
public:
	string note;
	void f(int x, char c) { }
	long g(double x) { note = "changed"; return 0;}
	int operator()(int N) { return 0;}
};
A a;

int main() {
	a.note = "Original"; 
	future<int> fu3 = async(A(), 4);    // A tmpA;  tmpA is moved to async(); create a task/thread with tmpA(4);
	future<int> fu4 = async(a, 7);    
	future<int> fu4 = async(ref(a), 7); // a(7);  Must use reference wrapper
	future<int> fu5 = async(&a, 7); // Won't compile

	future<void> fu1 = async(&A::f, a, 56, 'z'); // A copy of a invokes f(56, 'z')
	future<long> fu2 = async(&A::g, &a, 5.6);    // a.g(5.6);  a is passed by reference
		// note: the parameter of the invocable are always passed by value, but the invokeable itself can be passed by ref.
	cout << a.note << endl;
	return 0;
}
/*
	thread t1(a, 6);   
	async(a, 6);   
    bind(a, 6);
    call_once(once_flag, a, 6);

	thread t2(a, 6);  // creates copy_of_a() in a different thread
	thread t3(ref(a), 6); // a() in a different thread
	thread t4(move(a), 6); // move a from main thread to t4 thread. a is not usable in main thread any more
	thread t4([](int x){return x*x;}, 6);

	thread t5(&A::f, a, 56, 'z');  // copy_of_a.f(56, 'z') in a different thread
	thread t6(&A::f, &a, 56, 'z');  // a.f(56, 'z') in a different thread
*/



/* packaged_task */

mutex mu;
deque<packaged_task<int()> > task_q;

int factorial(int N) {
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

void thread_1() {
	for (int i=0; i<10000; i++) {
		packaged_task<int()> t;
		{
			lock_guard<mutex> locker(mu);
			if (task_q.empty()) 
				continue;
			t = move(task_q.front());
			task_q.pop_front();
		}
		t();
	}
}

int main() {
	thread th(thread_1);

	packaged_task<int()> t(bind(factorial, 6));  
	future<int> ret = t.get_future();
	packaged_task<int()> t2(bind(factorial, 9));
	future<int> ret2 = t2.get_future();
	{
		lock_guard<mutex> locker(mu);
		task_q.push_back(move(t));
		task_q.push_back(move(t2));
	}
	cout << "I see: " << ret.get() << endl;
	cout << "I see: " << ret2.get() << endl;

	th.join();
	return 0;
}



/* Summary
 * 3 ways to get a future:
 * - promise::get_future()
 * - packaged_task::get_future()
 * - async() returns a future
 */












/* threads with time constrains */

int main() {
    /* thread */
    thread t1(factorial, 6);
    this_thread::sleep_for(chrono::milliseconds(3));
    chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
    this_thread::sleep_until(tp);

    /* Mutex */
    mutex mu;
    lock_guard<mutex> locker(mu);
    unique_lock<mutex> ulocker(mu);
    ulocker.try_lock();
    ulocker.try_lock_for(chrono::nanoseconds(500));
    ulocker.try_lock_until(tp);

    /* Condition Variable */
    std:condition_variable cond;
    cond.wait_for(ulocker, chrono::microseconds(2));
    cond.wait_until(ulocker, tp);

    /* Future and Promise */
    promise<int> p; 
    future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(chrono::milliseconds(2));
    f.wait_until(tp);

    /* async() */
    future<int> fu = async(factorial, 6);

    /* Packaged Task */
    packaged_task<int(int)> t(factorial);
    future<int> fu2 = t.get_future();
    t(6);
 	
	 return 0;
}





   // Together with thread library 
	this_thread::sleep_until(steady_clock::now() + seconds(3));

	future<int> fu;
	fu.wait_for(seconds(3));
	fu.wait_until(steady_clock::now() + seconds(3));

	condition_variable c;
	mutex mu;
	unique_lock<mutex> locker(mu);
	c.wait_for(locker, seconds(3));
	c.wait_until(locker, steady_clock::now() + seconds(3));
 
