#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ll long long 
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
#define MAX 1e6
/*SOME BITMASK KNOWLEDGE
1)x & (x - 1):sets the last one bit of x to zero
power of two exactly when x & (x − 1) = 0.
2)x & -x:sets all the one bits to zero, except last one bit
3)x | (x - 1):inverts all the bits after the last one bit*/
#define o_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define o_setll tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
typedef tree<pair<ll, ll>,null_type,less<pair<ll, ll>>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
//member functions :
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

/*

Jon Snow now has to fight with White Walkers. He has n rangers, each of which has his own strength. Also Jon Snow has his favourite number x. Each ranger can fight with a white walker only if the strength of the white walker equals his strength. He however thinks that his rangers are weak and need to improve. Jon now thinks that if he takes the bitwise XOR of strengths of some of rangers with his favourite number x, he might get soldiers of high strength. So, he decided to do the following operation k times:

Arrange all the rangers in a straight line in the order of increasing strengths.
Take the bitwise XOR of the strength of each alternate ranger with x and update it's strength.

Suppose, Jon has 5 rangers with strengths [9, 7, 11, 15, 5] and he performs the operation 1 time with x = 2. He first arranges them in the order of their strengths, [5, 7, 9, 11, 15]. Then he does the following:

The strength of first ranger is updated to 5 xor 2, i.e. 7.
The strength of second ranger remains the same, i.e. 7.
The strength of third ranger is updated to 9 xor 2, i.e. 11.
The strength of fourth ranger remains the same, i.e. 11.
The strength of fifth ranger is updated to 15 xor 2, i.e. 13.

The new strengths of the 5 rangers are [7, 7, 11, 11, 13]
Now, Jon wants to know the maximum and minimum strength of the rangers after performing the above operations k times. He wants your help for this task. Can you help him?
Input

First line consists of three integers n, k, x (1 ≤ n ≤ 10^5, 0 ≤ k ≤ 10^5, 0 ≤ x ≤ 10^3) — number of rangers Jon has, the number of times Jon will carry out the operation and Jon's favourite number respectively.

Second line consists of n integers representing the strengths of the rangers a1, a2, ..., an (0 ≤ ai ≤ 10^3).

Output

Output two integers, the maximum and the minimum strength of the rangers after performing the operation k times.

Sample Input

5 1 2
9 7 11 15 5

Sample Output

13 7

*/

void DP(int n,int k,int x,int* a){
    int* out = new int[1024];
    for(int i=0;i<1024;i++)
        out[i] = 0;
    for(int i=0;i<n;i++){
        out[a[i]]++;
    }
    int* b = new int[1024];
    for(int i=0;i<1024;i++)
        b[i] = 0;
    
    
    for(int i=0;i<k;i++){
        int count = 0;
        for(int j=0;j<1024;j++){
            int y = out[j];
            int val = j ^ x;
            if(count%2==0){
                b[val] += (y+1)/2;
                b[j] += y - (y+1)/2;
                count += y;
            }
            else {
                b[val] += y/2;
                b[j] += y - y/2;
                count += y;                
            }
        }
        for(int j=0;j<1024;j++){
            out[j] = b[j];
            b[j] = 0;
        }
    }
    int min=0;
    int max=0;
    int flag1 = 0;
    int flag2 = 0;
    for(int i=0;i<1024;i++){
        if(out[i]!=0 && flag1==0){
            min = i; flag1=1;        
        }
        if(out[1023-i]!=0 && flag2==0){
            max = 1023-i; flag2=1;    
        }
        if(min !=0 && max!=0)
            break;
    }
    cout<<max<<" "<<min;
}
int main()
{
    int n,k,x;
    cin>>n>>k>>x;
    int* a = new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    DP(n,k,x,a);
    return 0;
}
         
