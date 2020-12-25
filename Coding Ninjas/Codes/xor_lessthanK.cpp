/*A straightforward question. Given an array of positive integers you have to print the number of subarrays whose XOR is less than K. Subarrays are defined as a sequence of continuous elements Ai, Ai+1, ..., Aj . XOR of a subarray is defined as Ai ^ Ai+1 ^ ... ^ Aj. Symbol ^ is Exclusive Or.*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
class treenode {
    public:
    int leafNodes;
    int value;
    treenode* left;
    treenode* right;
    treenode() {
        this->leafNodes = 0;
        this->left = NULL;
        this->right = NULL;
        this->value = 0;
    }
};
void insert(treenode* root, int num) {
    for(int i = 31; i >= 0; i--) {
        int temp = (num >> i) & 1;
        if(temp == 0) {
            if(!root->left) {
                root->left = new treenode();
            }
            root->left->leafNodes++;
            root = root->left;
        } 
        else {
            if(!root->right) {
                root->right = new treenode();
            }
            root->right->leafNodes++;
            root = root->right;
        }
    }
    root->value = num;
}
ll sub(treenode* root, int num, int k) {
    ll ans = 0;
    for(int i = 31; i >= 0; i--) 
    {
        int temp1 = (num >> i) & 1;
        int temp2 = (k >> i) & 1;
        if(temp1 == 1 && temp2 == 1) {
            if(root->right)
                ans += root->right->leafNodes;
            if(root->left)
                root = root->left;
            else
                return ans;
        } 
        else {
            if(temp1 == 0 && temp2 == 0) {
                if(root->left)
                    root = root->left; 
                else
                    return ans;
            } 
            else 
            {
                if(temp1 == 1 && temp2 == 0) {
                    if(root->right)
                        root = root->right;
                    else
                        return ans;
                } 
                else {
                    if(root->left)
                        ans += root->left->leafNodes;
                    if(root->right)
                        root = root->right;
                    else 
                        return ans;
                }
            }
        }
    }
    return ans;
}
ll subxor(int* a,int n,int k,treenode* root){
    int* x = new int[n];
    x[0] = a[0];
    insert(root,x[0]);
    ll count = 0;
    if(a[0]<k)
        count++;
    for(int i=1;i<n;i++){
        x[i] = x[i-1] ^ a[i];
        if(x[i] < k)
            count++;
        count = count + sub(root,x[i],k);
        insert(root,x[i]);
    }
    return count;
}
int main()
{
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        int* a = new int[n];
        treenode* root = new treenode();
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        cout<<subxor(a,n,k,root)<<endl;
    }
    return 0;
}
