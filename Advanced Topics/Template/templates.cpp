#include<iostream>
using namespace std;

// Function templates
template<typename T>
T GetMax(T a, T b) {
	T result;
	result = (a > b) ? a : b;
	return result;
}

// Class templates
template<class T>
class mypair {
	T a, b;
public:
	mypair(T first, T second) {a = first, b = second;}
	T getmax();
};

template<class T>
T mypair<T>::getmax()
{
	T retval;
	retval = (a > b) ? a : b;
	return retval;
}

// Class template specialization
// Herein we want to have a different implementation for a particular type
template <class T>
class mycontainer {
	T element;
public:
	mycontainer (T arg) {element = arg;}
	T increase() {return ++element;}
};

template<>
class mycontainer<char> {
	char element;
public:
	mycontainer (char arg) {element = arg;}
	char uppercase() {
		if ((element >= 'a') && (element <= 'z')) {
			element += 'A' - 'a';
		}
		return element;
	}
};

template <class T, int N>
class mysequence {
	T memblock[N];
public:
	void setmember (int x, T value);
	T getmember (int x);
};
template <class T, int N>
void mysequence<T, N>::setmember(int x, T value) {
	memblock[x] = value;
}
template <class T, int N>
T mysequence<T, N>::getmember(int x) {
	return memblock[x];
}

int main() 
{
	cout << GetMax(5, 10) << "\n";
	cout << GetMax('a', 'z') << "\n";

	mypair<int> myobject(100, 10);
	cout << myobject.getmax() << "\n";

	mycontainer<int>myint(7);
	mycontainer<char>mychar('j');
	cout << myint.increase() << "\n";
	cout << mychar.uppercase() << "\n";

	mysequence<int, 5> myints;
	mysequence<double, 5> myfloats;
	myints.setmember(0, 100);
	myfloats.setmember(3, 3.1416);
	cout << myints.getmember(0) << '\n';
	cout << myfloats.getmember(3) << '\n';
	return 0;
}

/* Format for declaring function templates with type parameters is:
template <class identifier> function_declaration;
template <typename identifier> function_declaration;
*/