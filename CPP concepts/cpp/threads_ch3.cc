//############################################################################
/*
 *  Concurrent C++
 *
 */
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>
/* Using mutex to synchronize threads */
std::mutex m_mutex;

void shared_print(string id, int value) {
	std::lock_guard<std::mutex> locker(m_mutex);
   //m_mutex.lock();
   // if (m_mutex.trylock()) {...}
	cout << "From " << id << ": " << value << endl;
   //m_mutex.unlock();
}

class Fctor {
public:
	void operator()() {
		for (int i=0; i>-100; i--) 
			shared_print("t1", i);
	}
};

int main() {
	Fctor fctor;
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		shared_print("main", i);

	t1.join();

	return 0;
}


/*
 * 1. Avoid global variables
 * 2. Mutex should bundle together with the resource it is protecting.
 */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	} // Need destructor to close file
	void shared_print(string id, int value) {
		std::lock_guard<mutex> locker(m_mutex);
		f << "From " << id << ": " << value << endl;
	}
	// Never leak f to outside world, like this:
	void processf(void fun(ofstream&)) {
		fun(f);
	}
	ofstream& getStream() { return f; }  // Don't do this
};

class Fctor {
	LogFile& m_log;
public:
	Fctor(LogFile& log):m_log(log) {}
	void operator()() {
		for (int i=0; i>-100; i--) 
			m_log.shared_print("t1", i);
	}
};

int main() {
	LogFile log;
	Fctor fctor(log);
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		log.shared_print("main", i);

	t1.join();

	return 0;
}

/* the ofstream will not be protected if it is leaked out */
// Example: add a LogFile method:
	ofstream* getStream() {
		return &f;
	}
// main():
	ofstream* fs = log.getStream();
	*fs << "ddummy" << endl;  // Unprotected access

// A more hidden leakage:
	void formated_print(function<ofstream (ofstream&)> usrFunc){
		std::lock_guard<mutex> locker(m_mutex);
		usrFunc(f);
	}

/* Important: Do not let your user work on protected data directly */


/* Interface is not thread safe */
class stack {
	int* _data;
	std::mutex _mu;
public:
	int& pop(); // pops off the item on top of the stack
	int& top(); // returns the item on top
	//...
};

void function_1(stack& st) {
	int v = st.pop();
	process(v);
}

/*
Avoiding Data Race:
1. Use mutex to syncrhonize data access;
2. Never leak a handle of data to outside
3. Design interface appropriately.
*/





/* Deadlock */
class LogFile {
	std::mutex _mu;
	std::mutex _mu_2;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string id, int value) {
		std::lock_guard<mutex> locker(_mu);
		std::lock_guard<mutex> locker1(_mu_2);
		f << "From " << id << ": " << value << endl;
	}
	void shared_print_2(string id, int value) {
		std::lock_guard<mutex> locker1(_mu_2);
		std::lock_guard<mutex> locker(_mu);
		f << "From " << id << ": " << value << endl;
	}
};
// Solution: lock the mutexes in a fixed order
//

/* C++ 11 std::lock */
class LogFile {
	std::mutex m_mutex;
	std::mutex m_mutex_2;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string id, int value) {
		std::lock(m_mutex, m_mutex_2); // provides deadlock avoidance algorithm
		std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
		std::lock_guard<mutex> locker1(m_mutex_2, std::adopt_lock);
		f << "From " << id << ": " << value << endl;
	}
	void shared_print_2(string id, int value) {
		std::lock(m_mutex, m_mutex_2);
		std::lock_guard<mutex> locker1(m_mutex_2, std::adopt_lock);
		std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
		f << "From " << id << ": " << val << endl;
	}
	void shared_print_3(string id, int value) {
		{
			std::lock_guard<mutex> locker(m_mutex);
			// ...
		}
		{
			std::lock_guard<mutex> locker1(m_mutex_2);
			f << "From " << id << ": " << value << endl;
		}
	}
};

/* Avoiding deadlock
1. Prefer locking single mutex.
2. Avoid locking a mutex and then calling a user provided function.
3. Use std::lock() to lock more than one mutex.
4. Lock the mutex in same order.


Locking Granularity:
- Fine-grained lock:  protects small amount of data
- Coarse-grained lock: protects big amount of data
*/





/* Deferred Lock */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(string id, int value) {
		//m_mutex.lock();  // lock before lock_guard is created
		//std::lock_guard<mutex> locker(m_mutex, std::adopt_lock);
		std::unique_lock<mutex> locker(m_mutex, std::defer_lock);
		locker.lock();  // Now the mutex is locked
		f << "From " << id << ": " << value << endl;
		locker.unlock();  // unlock before lock_guard is destroyed
		// ...
		locker.lock();  // lock again
	}
};

// Objects cannot be copied but can be moved: thread, packaged_task, fstream, unique_ptr 
// unique_lock
// mutex can neither be copied nor moved


/* unique_lock for transferring mutex ownership */

class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	unique_lock<mutex> giveMeLock() {
		return unique_lock<mutex>(m_mutex);  // Moved
	}
	void shared_print(string id, int value) {
		std::unique_lock<mutex> locker(m_mutex); // Now m_mutex is locked
		f << "From " << id << ": " << value << endl;

		std::unique_lock<mutex> locker2 = std::move(locker);  // Now m_mutex is locked by locker2
		// ...
	}
};

int main() {
	LogFile log;
	unique_lock<mutex> locker = log.giveMeLock();
   // I don't want to shared_print anything, but I don't want anybody else to do that either untill I am done.

   // I can also release the lock before locker is destroyed
   locker.unlock();  // lock_guard can't unlock

   //...
   // allow other thread to use log

   locker.lock();  // lock again. -- finer grained lock alows more resource sharing 

	return 0;
}





/* Lock for Initialization */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	void shared_print(string id, int value) {
		if (!f.is_open()) {   // lazy initialization
			std::unique_lock<mutex> locker(m_mutex);
			f.open("log.txt");   // This must be synchronized
		}
		f << "From " << id << ": " << value << endl;  // I don't care this is not synchronized
	}
};

// Problem: log.txt still will be opened multiple times

class LogFile {
	std::mutex mutex_open;
	std::mutex m_mutex_2;
	ofstream f;
public:
	void shared_print(string id, int value) {
		if (!f.is_open()) {   // lazy initialization   -- A
			std::unique_lock<mutex> locker(mutex_open);
			if (!f.is_open()) {
				f.open("log.txt");   // This must be synchronized  -- B
			}
		}
		std::unique_lock<mutex> locker2(m_mutex_2);
		f << "From " << id << ": " << value << endl;  // I don't care this is not synchronized
	}
};
// Double-checked locking
// Problem: race condition between point A and point B


// C++ 11 solution:
class LogFile {
   static int x;
	std::mutex m_mutex;
	ofstream f;
	std::once_flag m_flag;
	void init() { f.open("log.txt"); }
public:
	void shared_print(string id, int value) {
      std::call_once(_flag, &LogFile::init, this); // init() will only be called once by one thread
		//std::call_once(m_flag, [&](){ f.open("log.txt"); });  // Lambda solution
		//std::call_once(_flag, [&](){ _f.open("log.txt"); });  // file will be opened only once by one thread
		f << "From " << id << ": " << value << endl;
	}
};
int LogFile::x = 9;

//Note: once_flag and mutex cannot be copied or moved.
//      LogFile can neither be copy constructed nor copy assigned

// static member data are guaranteed to be initialized only once.




std::recursive_mutex
// A mutex can be locked multiple times (it must be released multiple times also)







