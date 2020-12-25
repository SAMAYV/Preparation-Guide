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
//1. order_of_key(k) : number of elements strictly lesser than k
//2. find_by_order(k) : k-th element in the set

/*

Sum Of Squares
Send Feedback
Segment trees are extremely useful. In particular "Lazy Propagation" (i.e. see here, for example) allows one to compute sums over a range in O(lg(n)), and update ranges in O(lg(n)) as well. In this problem you will compute something much harder:
The sum of squares over a range with range updates of 2 types:
1) increment in a range
2) set all numbers the same in a range.
Input

There will be T (T <= 25) test cases in the input file. First line of the input contains two positive integers, N (N <= 100,000) and Q (Q <= 100,000). 
The next line contains N integers, each at most 1000. Each of the next Q lines starts with a number, which indicates the type of operation:

2 st nd -- return the sum of the squares of the numbers with indices in [st, nd] {i.e., from st to nd inclusive} (1 <= st <= nd <= N).

1 st nd x -- add "x" to all numbers with indices in [st, nd] (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

0 st nd x -- set all numbers with indices in [st, nd] to "x" (1 <= st <= nd <= N, and -1,000 <= x <= 1,000).

Output

For each test case output the “Case <caseno>:” in the first line and from the second line output the sum of squares for each operation of type 2. Intermediate overflow will not occur with proper use of 64-bit signed integer.

Input:

2
4 5
1 2 3 4
2 1 4
0 3 4 1
2 1 4
1 3 4 1
2 1 4
1 1
1
2 1 1

Output:

Case 1:
30
7
13
Case 2:
1

*/

struct node {
    int ss;
    int s;
};
struct nodelazy {
    int type;
    int value;
};
void buildtree(int* a,node* tree,int start,int end,int Treenode){
    if(start==end){
        tree[Treenode].ss = a[start]*a[start];
        tree[Treenode].s = a[start];
        return;
    }
    int mid = (start+end)/2;
    buildtree(a,tree,start,mid,2*Treenode);
    buildtree(a,tree,mid+1,end,2*Treenode + 1);
    tree[Treenode].ss = tree[2*Treenode].ss + tree[2*Treenode + 1].ss;
    tree[Treenode].s = tree[2*Treenode].s + tree[2*Treenode + 1].s;
}
void lazytree(node* tree,nodelazy* lazy,int start,int end,int Treenode){
    if(lazy[Treenode].type == 1){
        int val = lazy[Treenode].value;
        tree[Treenode].ss += 2*val*tree[Treenode].s + (end-start+1)*val*val;
        tree[Treenode].s += (end-start+1)*val;
        if(start!=end){
            if(lazy[2*Treenode].type == 0)
                lazy[2*Treenode].type = 1;
            if(lazy[2*Treenode+1].type == 0)
                lazy[2*Treenode+1].type = 1;
            
            lazy[2*Treenode].value += val;
            lazy[2*Treenode+1].value += val;
        } 
        lazy[Treenode].type = 0;
        lazy[Treenode].value = 0;
    }
    else if(lazy[Treenode].type == 2){
        int val = lazy[Treenode].value;
        tree[Treenode].ss = (end-start+1)*val*val;
        tree[Treenode].s = (end-start+1)*val;
        if(start!=end){
            lazy[2*Treenode].type = 2;
            lazy[2*Treenode+1].type = 2;
            lazy[2*Treenode].value = val;
            lazy[2*Treenode+1].value = val;
        } 
        lazy[Treenode].type = 0;
        lazy[Treenode].value = 0;
    }
}
node query(int* a,node* tree,nodelazy* lazy,int start,int end,int Treenode,int left,int right){
    lazytree(tree,lazy,start,end,Treenode);
    if(end < left || start > right){
        node n;
        n.ss = 0;
        n.s = 0;
        return n;
    }
    
    if(start>=left && right>=end){
        return tree[Treenode];
    }
    
    int mid = (start+end)/2;
    node n1 = query(a,tree,lazy,start,mid,2*Treenode,left,right);
    node n2 = query(a,tree,lazy,mid+1,end,2*Treenode+1,left,right);
    node n3;
    n3.ss = n1.ss + n2.ss;
    n3.s = n1.s + n2.s;
    return n3;
}
void update1(int* a,node* tree,nodelazy* lazy,int start,int end,int Treenode,int left,int right,int v){
    lazytree(tree,lazy,start,end,Treenode);
    
    if(start > right || left > end){
        return;
    }
    if(start>=left && end<=right){
        
        tree[Treenode].ss += 2*v*tree[Treenode].s + (end-start+1)*v*v;
        tree[Treenode].s += (end-start+1)*v;
        
        if(start!=end){
            if(lazy[2*Treenode].type == 0)
                lazy[2*Treenode].type = 1;
            if(lazy[2*Treenode+1].type == 0)
                lazy[2*Treenode+1].type = 1;
            
            lazy[2*Treenode].value += v;
            lazy[2*Treenode+1].value += v;
        } 
        return;
    }
    
    int mid = (start+end)/2;
    update1(a,tree,lazy,start,mid,2*Treenode,left,right,v);
    update1(a,tree,lazy,mid+1,end,2*Treenode+1,left,right,v);
    tree[Treenode].ss = tree[2*Treenode].ss + tree[2*Treenode+1].ss;
    tree[Treenode].s = tree[2*Treenode].s + tree[2*Treenode+1].s;
}
void update2(int* a,node* tree,nodelazy* lazy,int start,int end,int Treenode,int left,int right,int v){
    lazytree(tree,lazy,start,end,Treenode);
    
    if(start > right || left > end){
        return;
    }
    if(start>=left && end<=right){
        tree[Treenode].ss = (end-start+1)*v*v;
        tree[Treenode].s = (end-start+1)*v;
        
        if(start!=end){
            lazy[2*Treenode].type = 2;
            lazy[2*Treenode+1].type = 2;
            lazy[2*Treenode].value = v;
            lazy[2*Treenode+1].value = v;
        } 
        return;
    }
    
    int mid = (start+end)/2;
    update2(a,tree,lazy,start,mid,2*Treenode,left,right,v);
    update2(a,tree,lazy,mid+1,end,2*Treenode+1,left,right,v);
    tree[Treenode].ss = tree[2*Treenode].ss + tree[2*Treenode+1].ss;
    tree[Treenode].s = tree[2*Treenode].s + tree[2*Treenode+1].s;
}
int main() 
{
	int t;
    cin>>t;
    for(int j=0;j<t;j++){
        int n,q;
        cin>>n>>q;
        int* a = new int[n];
        node* tree = new node[4*n];
        nodelazy* lazy = new nodelazy[4*n];
        for(int i=0;i<4*n;i++){
            lazy[i].type = 0;
            lazy[i].value = 0;
        }
        for(int i=0;i<n;i++)
            cin>>a[i];
        buildtree(a,tree,0,n-1,1);
        cout<<"Case "<<j+1<<":"<<endl;
        for(int i=0;i<q;i++){
            int x,y,z;
            cin>>x>>y>>z;
            if(x==2){
                node nd = query(a,tree,lazy,0,n-1,1,y-1,z-1);
                cout<<nd.ss<<endl;
            } else if(x==1) {
                int w;
                cin>>w;
                update1(a,tree,lazy,0,n-1,1,y-1,z-1,w);
            } else {
                int w;
                cin>>w;
                update2(a,tree,lazy,0,n-1,1,y-1,z-1,w);
            }
        }
    }
}  
