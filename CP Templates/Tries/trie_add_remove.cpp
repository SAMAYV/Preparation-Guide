/*

Ninja and Multiset
Our problem setter, Ninja, is fascinated by different types of sets. Quite recently, he came across a new term- Multiset. Multiset is a set, where equal elements are allowed. He started experimenting with it and has managed to frame a pretty interesting problem for you to solve.
You are given a multiset G, initially containing only 0, and a few queries q. Queries are actually of 3 types:
"+ x" — This query adds an integer x to the given multiset.
"- x" — This query erases one occurrence of x from the given multiset. Before this query is encountered, it is guaranteed that the multiset will contain integer x at least once.
"? x" — In this query, you are given integer x and you need to compute the maximum value of bitwise exclusive OR (also known as XOR) of integer x and some integer y from the given multiset.
Input Format:
First line on input contain Q (number of queries ).
Next Q line contain Q queries as defined above.
Output Format:
For each query of type '?' print the answer in new line
Constraints:
1 <= Q <= 10^5
1 <= x <= 10^9
Sample Input 1:
8
? 8
? 5
+ 10
? 5
? 4
+ 4
- 4
? 10
Sample Output 1:
8
5
15
14
10

*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long

class Trienode {
    public:
    Trienode* left;
    Trienode* right;
    int count = 0;
    Trienode() {
        left = NULL;
        right = NULL;
        count = 0;
    }
};

void insert(ll val, Trienode* root){
    Trienode* curr = root;
    curr->count++;
    for(int i = 60; i >= 0; i--){
        ll b = ((val >> i) & 1);
        if(b == 0){
            if(!curr->left)
                curr->left = new Trienode();
            curr->left->count++;
            curr = curr->left;
        }
        else {
            if(!curr->right)
                curr->right = new Trienode();
            curr->right->count++;
            curr = curr->right;
        }
    }
}

void remove(ll val, Trienode* root){
    Trienode* curr = root;
    curr->count--;
    for(int i = 60; i >= 0; i--){
        ll b = ((val >> i) & 1);
        if(b == 0){
            if(!curr->left)
                curr->left = new Trienode();
            else 
                curr->left->count--;
            curr = curr->left;
        }
        else {
            if(!curr->right)
                curr->right = new Trienode();
            else 
                curr->right->count--;
            curr = curr->right;
        }
    }
}

ll query(ll val,Trienode* root){
    Trienode* curr = root;
    ll curr_xor = 0;
    for(int i = 60; i >= 0; i--){
        ll b = ((val >> i) & 1);
        if(b == 0){
            if(curr->right && curr->right->count > 0){
                curr_xor += (1 << i);
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if(curr->left && curr->left->count > 0){
                curr_xor += (1 << i);
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
    }
    return curr_xor;
}
int main(){
    
    // write your code here
    Trienode* root = new Trienode();
    insert(0, root);
    int q;
    cin >> q;
    while(q--){
        char c;
        ll x;
        cin >> c >> x;
        if(c == '+'){
            insert(x, root);
        }
        else if(c == '-'){
            remove(x, root);
        }
        else {
            cout << query(x, root) << "\n";
        }
    }
    return 0;
}