/*You want to paint your house. The total area of your house is D units. There are a total of N workers. The ith worker is available after time Ti, has hiring cost Xi and speed Yi. This means he becomes available for hiring from time Ti and remains available after that. Once available, you can hire him with cost Xi, after which he will start painting the house immediately, covering exactly Yi units of house with paint per time unit. You may or may not hire a worker and can also hire or fire him at any later point of time. However, no more than 1 worker can be painting the house at a given time.
Since you want the work to be done as fast as possible, figure out a way to hire the workers, such that your house gets painted at the earliest possible time, with minimum cost to spend for hiring workers.
Note: You can hire a previously hired worker without paying him again.*/
#include<bits/stdc++.h>
using namespace std;
struct fracknap{
    int t,x,y;
};
bool compare(fracknap f1,fracknap f2){
    if(f1.t == f2.t && f1.y == f2.y)
        return f1.x < f2.x;
    else if(f1.t == f2.t && f1.y != f2.y)
        return f1.y > f2.y;
    return f1.t < f2.t;
}
int main()
{
    int n;
    long d;
    cin>>n>>d;
    fracknap* arr = new fracknap[n];
    for(int i=0;i<n;i++){
        cin>>arr[i].t>>arr[i].x>>arr[i].y;
    }
    sort(arr,arr+n,compare);
    long area = 0;
    long cost = 0;
    int i=0;
    int time = 0;
    while(i < n && area < d){
        if(i==n-1){
            cost += arr[i].x;
            break;
        }
        cost += arr[i].x;
        area += arr[i].y;
        time++;
        int j = i+1;
        while(j < n && arr[j].y <= arr[i].y){
            time++;
            area += arr[i].y;
            j++;
        }
        while(j < n && time < arr[j].t){
            time++;
            area += arr[i].y;
        }
        i = j;
    }
    cout<<cost<<endl;
    return 0;
}