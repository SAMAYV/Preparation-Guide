/*Given an array of n integers, find subarray whose xor is maximum.*/
#include<bits/stdc++.h>
using namespace std;
class Trienode {
    public:
    Trienode* left;
    Trienode* right;
};
void insert(int val,Trienode* root){
    Trienode* curr = root;
    for(int i=31;i>=0;i--){
        int b = val>>i & 1;
        if(b==0){
            if(!curr->left)
                curr->left = new Trienode();
            curr = curr->left;
        }
        else {
            if(!curr->right)
                curr->right = new Trienode();
            curr = curr->right;
        }
    }
}
int query(int val,Trienode* root){
    Trienode* curr = root;
    int curr_xor = 0;
    for(int i=31;i>=0;i--){
        int b = val>>i & 1;
        if(b==0){
            if(curr->right){
                curr_xor += pow(2,i);
                curr = curr->right;
            }
            else
                curr = curr->left;
        }
        else {
            if(curr->left){
                curr_xor += pow(2,i);
                curr = curr->left;
            }
            else
                curr = curr->right;
        }
    }
    return curr_xor;
}
int maxor(int* a,int n,Trienode* root){
    int* x = new int[n];
    x[0] = a[0];
    insert(a[0],root);
    int maxor = a[0];
    for(int i=1;i<n;i++){
        x[i] = x[i-1] ^ a[i];
        insert(x[i],root);
        int curr_xor = query(x[i],root);
        
        if(curr_xor < x[i])
            curr_xor = x[i];
        if(maxor < curr_xor)
            maxor = curr_xor;
    }
    return maxor;
}
int main() {
    int n;
    cin>>n;
    int* a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    Trienode* root = new Trienode();
	cout<<maxor(a,n,root);
}