// BROWNIE TK

#include <bits/stdc++.h>

typedef long long int lli;
typedef unsigned long long int ulli;
typedef long double ldb;

#define pb push_back
#define popb pop_back
#define pf push_front
#define popf pop_front
#define si size()
#define be begin()
#define en end()
#define all(v) v.be, v.en
#define le length()
#define mp make_pair
#define mt make_tuple
#define F first
#define S second

#define forz(i, n) for (int i = 0; i < n; i++)
#define bui(i, m, n) for (int i = m; i < n; i++)
#define rforz(i, n) for (int i = n - 1; i >= 0; i--)
#define mui(i, m, n) for (int i = n - 1; i >= m; i--)
#define deci(n) fixed << setprecision(n)
#define high(n) __builtin_popcount(n)
#define parity(n) __builtin_parity(n)
#define ctz(n) __builtin_ctz(n)
#define lb lower_bound
#define ub upper_bound
#define er equal_range
#define maxe *max_element
#define mine *min_element
#define mod 1000000007
#define mod2 998244353
#define kira ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl

using namespace std;

/*STD fucntions*/
lli power(lli x,lli y,lli p)
{
	lli res=1;
	x=x%p;
	while(y>0)
	{
		if(y&1)
			res=(res*x)%p;
		//y must be even now
		y=y>>1; //y=y/2
		x=(x*x)%p;
	}
	return res;
}
lli gcd(lli a, lli b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
lli lcm(lli a, lli b)
{ return a * b / gcd(a, b); }
lli max(lli a, lli b)
{
  if (a > b)
    return a;
  return b;
}
lli min(lli a, lli b)
{
  if (a < b)
    return a;
  return b;
}
lli bins(lli arr[], lli l, lli r, lli x)
{
  if (r >= l) {
    lli mid = l + (r - l) / 2;
    if (arr[mid] == x)
      return mid;
    if (arr[mid] > x)
      return bins(arr, l, mid - 1, x);
    return bins(arr, mid + 1, r, x);
  }
  return -1;
}
lli modi(lli a,lli m)
{
// fermat little thm where m is prime
return power(a,m-2,m);
}
/*CODE BEGINS*/
struct lyric
{
  string s;
  int v;
  char c;
};
int main()
{
 kira;
 lli n;
 cin>>n;
 string a;
 vector<lyric>v,v1,v2;
 forz(i,n)
 {
   cin>>a;
   int l=a.si;
   int cnt=0;
   char ch;
   forz(i,l)
   {
     if(a[i]=='a'||a[i]=='e'||a[i]=='i'||a[i]=='o'||a[i]=='u')
     {
       ch=a[i];
       cnt++;
     }
   }
   v.pb({a,cnt,ch});
 }
 for(lyric x:v)
 {
   p3(x.s,x.v,x.c);
 }
 return 0;
}
