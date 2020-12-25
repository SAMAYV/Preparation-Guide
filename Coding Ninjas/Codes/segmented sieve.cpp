#include <bits/stdc++.h>
using namespace std;
#define M 100000
#define ll long long  
vector<int>* sieve(){
	vector<int>* v = new vector<int>;
	bool* arr = new bool[M+1];
	for(int i=0;i<=M;i++)
		arr[i] = true;
	arr[0] = false;  arr[1] = false;
	for(int i=2;i<=sqrt(M);i++){
		if(arr[i]){
			for(int j=i;j<=M/i;j++){
				arr[i*j] = false;
			}
		}
	}
    for(int i=2;i<=M;i++){
        if(arr[i]){
            v->push_back(i);
        }
    }
	return v;
}
void segmented_sieve(vector<int>* v,ll left,ll right){
	int sieve_length = right - left + 1;
	bool* a = new bool[sieve_length];
	for(int i=0;i<sieve_length;i++)
		a[i] = true;       //for left+i index

    int i=0;
	while(i < v->size() && v->at(i)<=right){
		int prime = v->at(i);
		ll index = (left/prime)*prime;
		if(index < left){
			index += prime;
		}
		for(ll j=index;j<=right;j+=prime){
			a[j-left] = false;
		}
		if(index==prime)
			a[index-left] = true;
        i++;
	}
	for(int i=0;i<sieve_length;i++){
		if(a[i]==true){
			cout<<i+left<<endl;
		}
	}
    delete [] a;
}
int main()
{
    int t;
    cin>>t;
    vector<int>* v = sieve();
    while(t--){
        ll left,right;
	    cin>>left>>right;
	    segmented_sieve(v,left,right);    
    }
	return 0;
}