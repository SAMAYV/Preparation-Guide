#include<bits/stdc++.h>
using namespace std;
void buildtree(string s,int* tree,int start,int end,int treenode){
    if(start==end){
        if(s[start]=='1')
            tree[treenode] = 1;
        else
            tree[treenode] = 0;
        return;
    }
    int mid= (start+end)/2;
    buildtree(s,tree,start,mid,2*treenode);
    buildtree(s,tree,mid+1,end,2*treenode+1);

    if((end-mid) % 2 ==0){
        tree[treenode] = (tree[2*treenode] + tree[2*treenode+1]) % 3;
    }
    else {
        tree[treenode] = ((2*tree[2*treenode]) % 3 + tree[2*treenode+1]) % 3;
    }
}
int query(string s,int* tree,int start,int end,int treenode,int left,int right){
    if(start > right || end < left) 
         return 0;
    
    if(start>=left && end<=right){
        if((right-end) % 2 ==0)
            return tree[treenode];
        else
            return (2*tree[treenode]) % 3;
    }
    
    int mid = (start+end)/2;
    int n1 = query(s,tree,start,mid,2*treenode,left,right);
    int n2 = query(s,tree,mid+1,end,2*treenode+1,left,right);
    return (n1 + n2) % 3;
}
void update(string s,int* tree,int start,int end,int treenode,int index){
    if(index < start || index > end)
        return;
    if(start==end){
        s[index] = '1';
        tree[treenode] = 1;
        return;
    }
    int mid = (start+end)/2;
    update(s,tree,start,mid,2*treenode,index);
    update(s,tree,mid+1,end,2*treenode+1,index);

    if((end-mid) % 2 ==0){
        tree[treenode] = (tree[2*treenode] + tree[2*treenode+1]) % 3;
    }
    else {
        tree[treenode] = ((2*tree[2*treenode]) % 3 + tree[2*treenode+1]) % 3;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n,q;
    cin>>n;
    int* tree = new int[4*n];
    string s;
    cin>>s;
    buildtree(s,tree,0,n-1,1);
    cin>>q;
    for(int i=0;i<q;i++){
        int x,y;
        cin>>x>>y;
        if(x==0){
            int z;
            cin>>z;
            cout<<query(s,tree,0,n-1,1,y,z)<<endl;
        }
        else {
            if(s[y]=='0')
                update(s,tree,0,n-1,1,y);
        }
    }
}