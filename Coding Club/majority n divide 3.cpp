#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    cin>>n;
    int* a = new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    
    int count1 = 0, count2 = 0;
    int ele1,ele2;
    for(int i=0;i<n;i++){
        if(a[i]==ele1){
            count1++;
        }
        else if(a[i]==ele2){
            count2++;
        }
        else if(count1==0){
            ele1 = a[i];
            count1 = 1;
        }
        else if(count2==0){
            ele2 = a[i];
            count2 = 1;
        }
        else {
            count1--; count2--;
        }
    }
    count1 = 0; count2 = 0;
    for(int i=0;i<n;i++){
        if(a[i]==ele1){
            count1++;
        }
        else if(a[i]==ele2){
            count2++;
        }
    }
    if(count1 > n/3)
        cout<<"YES "<<ele1<<endl;
    else if(count2 > n/3)
        cout<<"YES "<<ele2<<endl;
    else
        cout<<"NO"<<endl;
	return 0;
}