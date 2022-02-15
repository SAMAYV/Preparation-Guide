#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include "timer.h"
using namespace std;

int parse_arguments(int argc, char** argv);

/* There should be only one copy of the variable */
class atomic_int 
{
private:
	static int val;
	static mutex mtx;
public:
	static void increment(int id) {
		mtx.lock();
		val = val + 1;
		mtx.unlock();
	}
	static void decrement() {
		mtx.lock();
		val = val - 1;
		mtx.unlock();
	}
	static int get() {
		int tmp;
		mtx.lock();
		tmp = val;
		mtx.unlock();
		return tmp;
	}
	static void set(int x) {
		mtx.lock();
		val = x;
		mtx.unlock();
	}
};

atomic_int cnt;
mutex atomic_int::mtx;   // static members need to be defined.

// Removing this line shows compilation error
int atomic_int::val = 0;

void run(int id, int num_threads) {
	for(int i = 0; i < 1000 / num_threads; i++) {
		sleep(1); 			// sleep the CPU for 1 millisecond.
		cnt.increment(id);
	}
}
int main(int argc, char** argv) 
{
	ScopedTimer timer;
	int num_threads = parse_arguments(argc, argv);
	
	thread threads[num_threads];
	cout << "Number of threads used: " << num_threads << "\n";

	for(int i = 0; i < num_threads; i++) {
		threads[i] = thread(run, i, num_threads);
	}
	for(auto &th : threads)th.join();
	cout << cnt.get() << "\n";
	return 0;
}
int parse_arguments(int argc, char** argv) {
	--argc;
	++argv;
	if(argc != 1) {
		cout << "Requires 1 argument: number of threads\n";
		exit(-1);
	}
	int num_threads = stoi(argv[0]);
	return num_threads;
}