// https://www.codechef.com/problems/FCTRL2
// https://www.boost.org/doc/libs/1_75_0/libs/multiprecision/doc/html/boost_multiprecision/intro.html

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
namespace mp = boost::multiprecision;
using namespace std;
 
// This library works fine on CodeChef and HackerEarth. However, it doesn’t works on HackerRank and CodeForces.
// Run it on C++14 and above

/* 
cpp_int for multiprecision integers,
cpp_rational for rational types,
cpp_bin_float and cpp_dec_float for multiprecision floating-point types,
cpp_complex for complex types.
*/

int main()
{
    ll t;
    cin>>t;
    while(t--){
    	ll n;
    	cin>>n;
    	mp::cpp_int u = 1;
    	REP(i,1,n+1) u *= i;
    	cout<<u<<"\n";
    }
}