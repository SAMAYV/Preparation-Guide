#include<bits/stdc++.h>
using namespace std;
void swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
int partition(int arr[],int low,int high)
{
    int pivot=arr[high];
    int i=(low-1);
    for(int j=low;j<=high-1;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}
void quick(int arr[],int low,int high)
{
    if(low<high)
    {
        int q=partition(arr,low,high);
        quick(arr,low,q-1);
        quick(arr,q+1,high);
    }
}
int main()
{
    int a[10]={9,2,1,3,7,4,5,0,6,9};
    quick(a,0,9);
    for(int i=0;i<10;i++)cout<<a[i]<<" ";
    return 0;
}