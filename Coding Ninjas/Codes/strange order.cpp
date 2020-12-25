#include<bits/stdc++.h>
using namespace std;
void func(bool* a,int n){
    vector<int> v;
    int max = n;
    while(v.size() < n){
        v.push_back(max);
        a[max] = false;
        int m = max;
        max = 1;
        for(int j=m-1;j>1;j--){
            if(a[j]==true && __gcd(m,j)!=1){
                a[j] = false;
                v.push_back(j);
            }
            else {
                if(a[j]==true && j>max)
                    max = j;
            }
        }
    }
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
}
int main() {

	int n;
    cin>>n;
    bool* a = new bool[n+1]();
    a[0] = false;
    for(int i=1;i<=n;i++)
        a[i] = true;
    func(a,n);
}