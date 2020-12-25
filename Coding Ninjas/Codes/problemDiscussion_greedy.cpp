/*Harshit gave Aahad an array of size N and asked to minimize the difference between the maximum value and minimum value by modifying the array under the condition that each array element either increase or decrease by k(only once).
It seems difficult for Aahad so he asked for your help*/
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n,k;
    cin>>n>>k;
    int* a = new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    int min = a[0] + k;
    int max = a[n-1] - k;
    if(min>max){
        swap(min,max);
    }
    if(max-min > a[n-1] - a[0]){
        max = a[n-1] + k;
        min = a[0] + k;
    }
    for(int i=1;i<n-1;i++){
        int min1 = a[i] - k;
        int max1 = a[i] + k;
        if(min1 >= min || max1 <= max)
            continue;
        else {
            if(max - min1 <= max1 - min){
                min = min1;
            }
            else {
                max = max1;
            }
        }
    }
    cout<<max-min;
}