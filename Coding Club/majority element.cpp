#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    cin>>n;
    int* a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    
    int index = 0;
    int count = 1;
    for(int i=1;i<n;i++){
        if(a[i]==a[index]){
            count++;
        }
        else if(count==0){
            index = i;
            count = 1;
        }
        else {
            count--;
        }
    }
    count = 0;
    for(int i=0;i<n;i++){
        if(a[i]==a[index])
            count++;
    }
    if(count > n/2)
        cout<<"YES "<<a[index]<<endl;
    else cout<<"NO"<<endl;
	return 0;
}