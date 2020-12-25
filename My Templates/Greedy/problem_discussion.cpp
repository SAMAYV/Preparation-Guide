/*
Harshit gave Aahad an array of size N and asked to minimize the difference between the maximum value and minimum value by modifying the array under the condition that each array element either increase or decrease by k(only once).
It seems difficult for Aahad so he asked for your help

Input Format
The First line contains two space-separated integers: N,K
Next lines contain N space-separated integers denoting elements of the array

Output Format
The output contains a single integer denoting the minimum difference between maximum value and the minimum value in the array

Constraints
1 =< N <= 10^5 
1 <= Ai,K <= 10^9

Sample Input1:
3 6
1 15 10

Sample Output1:
5

Explaination
We change from 1 to 6, 15 to  9 and 10 to 4. Maximum difference is 5 (between 4 and 9). We can't get a lower difference.
*/

int main() 
{
    ll n,k;
    cin>>n>>k;
    vector<ll> arr(n);
    REP(i,0,n){
        cin>>arr[i];
    }
    sort(arr.begin(),arr.end());
    ll min = a[0] + k, max = a[n-1] - k;
    if(min > max){
        swap(min,max);
    }
    if(max - min > a[n-1] - a[0]){
        max = a[n-1] + k;
        min = a[0] + k;
    }
    REP(i,1,n-1){
        ll min1 = a[i] - k;
        ll max1 = a[i] + k;
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
    cout<<max - min<<endl;
}
         
