//############################################################################
/*
 *  Concurrent C++
 *
 */

// First example:
void thread1() {
	std::cout << "Helldo, Worlds" << std::endl;
}

int main() {
	std::thread t1(thread1);
	t1.join();   // main thread wait for t1 to finish
	//t1.detach();  // main thread let t1 to run on its own: t1 is a daemon process.
                   // C++ runtime library is responsible returning t1's resources
                   // and main thread may finish before t2 prints "Hello"

	return 0;
}
// If neither detach nor join is called, terminate() will be called for the t1.
// A thread can only be joined once or detached once. After it is joined on detached
// it becomes unjoinable ( t.joinable() returns false )






// Second Example: Racing condition
class Fctor {
	ofstream& m_str;
public:
	Fctor(ofstream& s):m_str(s) {}   // Reference member can only be initialized
	void operator()() {
		for (int i=0; i>-100; i--)
			m_str << "from t1: " << i << endl;
	}
};

int main() {
	cout << "Hollo Bo" << endl;
	ofstream f;
	f.open("log.txt");

	Fctor fctor(f);
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		f << "from main: " << i << endl;

	t1.join();
	f.close();

	return 0;
}




// 1. expeirment with t1.join()
// 2. expeirment with t1.detach()
// 3. expeirment with t1 closing file
// 4. expeirment with  cout instead of f and m_str
// 4. experiment with t1.get_id();
// 4. experiment with thread::hardware_concurrentcy();

// A common solution: do not share, make a copy.


// If exception happens in the main()'s for loop, t1.join() will not be called.
int main() {
	cout << "Hollo Bo" << endl;
	ofstream f;
	f.open("log.txt");

	Fctor fctor(f);
	std::thread t1(fctor);

	try {
		for (int i=0; i<100; i++)
			cout << "from main: " << i << endl;  // Exception may happen here
	} catch (...) {
		t1.join();
		throw;
	}

	t1.join();
	f.close();

	return 0;
}




// Alternative way: RAII
class ThreadJoiner {
	thread& m_th;
public:
	explicit ThreadJoiner(thread& t):m_th(t) {}
	~ThreadJoiner() {
		if(m_th.joinable()) {
			m_th.join();
		}
	}
};

int main() {
	cout << "Hollo Bo" << endl;
	ofstream f;
	f.open("log.txt");

	Fctor fctor(f);
	std::thread t1(fctor);
	ThreadJoiner tj(t1);

	for (int i=0; i<100; i++)
		cout << "from main: " << i << endl;

	f.close();
	return 0;
}








// We can also create a ThreadDetacher class
// Prerequisit: join() or detach() can happen at the end of the function




// Passing parameters to a thread

void call_from_thread(string& msg) {
	msg = "Beauty is only skin-deep";
	cout << "t1 says: " << msg << endl;
}

int main() {
	
	string s = "A friend in need is a friend indeed.";
	std::thread t1(call_from_thread, std::ref(s));
	// Function templates ref and cref are helper functions that generate an object of type std::reference_wrapper

	t1.join();

	cout << "main says: " << s << endl;
	return 0;
}
// Paramters are always passed by value (copied).  why? same reason as bind(): deferred execution means the parmeter objects might not be valid at the time of execution
// To pass by reference:
// 1. use std::ref
// 2. use pointer



// To pass a class method as thread's initial function, use pointers
class A {
public:
	void call_from_thread(string* msg) {
		*msg = "Beauty is only skin-deep";
		cout << "t1 says: " << *msg << endl;
	}
};

int main() {

	string s = "A friend in need is a friend indeed.";
	A a;
	std::thread t1(&A::call_from_thread, &a, &s);
	t1.detach();

	cout << "main says: " << s << endl;
	return 0;
}



// Thread with moving parameters
void call_from_thread(string msg) {
	cout << "t1 says: " << msg << endl;
}

int main() {
	string* ps = new string("A friend in need is a friend indeed.");
	std::thread t1(call_from_thread,  std::move(*ps));
	t1.join();

	cout << "main: " << *ps << endl;
	return 0;
}



// A thread object cannot be copied
// But it can be moved.  Like fstream, unique_ptr, etc.

//Case 1:
std::thread t1(call_from_thread);
std::thread t2 = move(t1);  // t2 become the owner of the thread
t2.join();

//Case 2:
thread f() {
   // ...
   return std::thread(call_from_thread);   // move semantics 
}

//Case 3:
void f(std::thread t);
int main() {
   f(std::thread(call_from_thread));  // move semantics
   //...
}

// Revisit the RAII example with move semantics


// Indication that how many threads can be truly running concurrenctly for my program (e.g. can give no of cpu cores)
int main() {
	cout << std::thread::hardware_concurrency();
	return 0;
}

