#include <bits/stdc++.h>
#include <thread>
using namespace std;

class Semaphore {
	int ctr;
public:
	Semaphore() {
		ctr = 1;
	}
	void wait() {
		while(ctr == 0); // issue here is busy waiting and we are wasting CPU cycles.
		// instead we can use ready queue for binary semaphores.
		ctr--;
	}
	void signal(){
		ctr++;
	}
};

class Atomic_var {
	int val;
	Semaphore sm;
public:
	void increment(char x) {
		// we will use semaphore here.
		sm.wait();
		cout << this_thread::get_id() << " " << x << "\n";
		val = val + 1;
		sm.signal();
	}
	int print() {
		return val;
	}
};

int main() 
{
	Atomic_var atomic_var; // Either declare globally or pass the object by reference.

	auto cnt = [&atomic_var](char x) {
		for (int i = 0; i < 50; i++) atomic_var.increment(x);
	};
	thread A(cnt, 'A');
	thread B(cnt, 'B');

	A.join();
	B.join();
	cout << atomic_var.print() << "\n";

	return 0;
}
// Run:  g++ -pthread -std=c++14 main.cpp