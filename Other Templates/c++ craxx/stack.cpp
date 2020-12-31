#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
#define ll long long
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vll vector<long long>
class STACK
{
private:
	int arr[100000];
	int len = 0;

public:
	int size()
	{
		return len;
	}
	int top()
	{
		if (len != 0)
			return arr[len - 1];
		return -1;
	}
	void push(int x)
	{
		len++;
		arr[len - 1] = x;
	}
	void pop()
	{
		if (len == 0)
			return;
		len--;
	}
};

int main()
{
	STACK s;
	s.push(1);
	cout << s.size() << "\n";
	cout << s.top() << "\n";
	s.push(2);
	s.push(3);
	cout << s.size() << "\n";
	s.push(5);
	s.pop();
	cout << s.size() << "\n";
	s.pop();
	cout << s.top() << "\n";
	return 0;
}