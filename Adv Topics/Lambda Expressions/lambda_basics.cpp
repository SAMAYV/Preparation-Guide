#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

void Example1() 
{
	cout << "Example1: -------------------------------\n";
	auto f1 = [](int x, int y) {return x + y;};
	cout << f1(3, 4) << "\n"; // output: 7

	cout << [](int x, int y) {return x + y;}(3, 4) << "\n"; // output: 7

	function<int(int, int)> f2 = [](int x, int y) {return x + y;};
	cout << f2(3, 4) << "\n"; // output: 7
}

void Example2() 
{
	// Sorting by absolute value
	cout << "Example2: -------------------------------\n";

	int arr[] = {1, 5, 65, 23, -3, -7, -43, -2, -54, 45, 2};

	int n = sizeof(arr) / sizeof(int);
	sort(arr, arr + n, [&](int x, int y) {
		return abs(x) < abs(y);
	});
	for(int &x : arr) {
		cout << x << " ";
	}
	cout << "\n";
}

void Example3() 
{
	// compiler binds a lambda expression to its captured variables when the expression is declared instead
	// of when the expression is called.

	cout << "Example3: -------------------------------\n";

	int i = 3, j = 5;

	// The following lambda expression captures i by value and j by reference.
	function<int (void)> f = [i, &j] { return i + j; };

	// Change the values of i and j.
	i = 22;
	j = 44;

	// Call f and print its result.
	cout << f() << endl;
}

void Example4() 
{
	cout << "Example4: -------------------------------\n";

	// How to write recursive function in lambda
	int n = 12345;

	// Function itself as a parameter
	auto printReverse = [&](auto&& printReverse) {
		if(n == 0) return;
		cout << n % 10 << " ";
		n = n / 10;
		printReverse(printReverse);
	};

	// Function as an argument
	printReverse(printReverse);
	cout << "\n";

	function<void(int)> printRev = [&](int n) {
		if(n == 0) return;
		cout << n % 10 << " ";
		n /= 10;
		printRev(n);
	};
	printRev(12345);
	cout << "\n";
}

int main() 
{
	Example1();
	Example2();
	Example3();
	Example4();
	return 0;
}

// Resource: https://docs.microsoft.com/en-us/cpp/cpp/examples-of-lambda-expressions?view=msvc-160