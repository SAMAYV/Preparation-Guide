/*Professor Jain has a class full of notorious students. To get anything done from them is a herculean task. Prof Jain wanted to organize a test. He gave this responsibility to Aahad. Aahad did an excellent job of organizing the test. As a reward, the professor gave him an sequence of numbers to play with. But Aahad likes playing with "interesting" sequence of numbers, which are sequences that have equal elements.
Now, the problem is - Prof Jain has a sequence with elements, and that sequence isn't always "interesting”. To ensure sequence has equal elements, Prof Jain has 2 options:
1) Choose two elements of sequence . DECREASE the first element by 1 and INCREASE the second element by 1. This operation costs 'k' coins.
2) Choose one element of array and INCREASE it by 1. This operation costs 'l' coins.
What’s the minimum number of coins Prof Jain needs to turn his sequence into a “interesting" sequence for Aahad?*/
#include<bits/stdc++.h>
using namespace std;
int main() {

	int n,k,l;
    cin>>n>>k>>l;
    int* a = new int[n];
    int max = INT_MIN;
    int min = INT_MAX;
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(max < a[i])
            max = a[i];
        if(min > a[i])
            min = a[i];
    }
    int m = INT_MAX;
    for(int i=min;i<=max;i++){
        int cost = 0;
        int incre = 0;
        int decre = 0;
        for(int j=0;j<n;j++){
            if(a[j] < i){
                incre += i - a[j];
            } else {
                decre += a[j] - i;
            }
        }
        if(incre >= decre){
            cost += decre*k + (incre-decre)*l;
            if(cost < m)
                m = cost;
        }
    }
    cout<<m;
}