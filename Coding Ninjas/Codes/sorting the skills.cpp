/*There is a company named James Peterson & Co. The company has ‘n’ employees. The employees have skills from 0 to n-1. 
All the employees have distinct skills. The manager of James Peterson & Co. wants to sort the employees on the basis of their 
skills in ascending order. He is only allowed to swap two employees which are adjacent to each other. He is given the skills 
of employees in an array of size ‘n’. He can swap the skills as long as the absolute difference between their skills is 1. 
You need to help the manager out and tell whether it is possible to sort the skills of employees or not.*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int* a = new int[n];
        for(int i=0;i<n;i++)
            cin>>a[i];
        for(int i=0;i<n-1;i++){
            if(a[i+1]==a[i]-1)
                swap(a[i+1],a[i]);
        }
        int flag = 0;
        for(int i=0;i<n-1;i++){
            if(a[i]>a[i+1]){
                cout<<"No"<<endl;
                flag = 1;
                break;
            }
        }
        if(flag==0)
            cout<<"Yes"<<endl;
    }
	return 0;
}
