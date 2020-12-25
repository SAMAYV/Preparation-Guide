#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ll long long
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define i_os ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
#define INF (ll)1e18 + 100
#define endl "\n"
#define p0(a) cout << a << " "
#define p1(a) cout << a << endl
#define p2(a, b) cout << a << " " << b << endl
#define p3(a, b, c) cout << a << " " << b << " " << c << endl
#define p4(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl

void transpose(int** arr,int r,int c){
	unordered_map<int,bool> um;
	um[0] = true;  um[r*c - 1] = true;
	int ct = 2;
	int start_cycle = 1, curr_index = 1;
	int next_index;
	int cr = 0, cc = 1;
	int value = arr[cr][cc];
	int val;
	while(ct < r*c){
		do {
			next_index = (curr_index*r) % (r*c - 1);
			int nc = next_index % c;
			int nr = next_index / c;
			val = arr[nr][nc];
			arr[nr][nc] = value;
			um[curr_index] = true;
			ct++;
			cr = nr;
			cc = nc;
			curr_index = next_index;
			value = val;
		} while(curr_index != start_cycle);
		
		int flag = 0;
		REP(i,0,r){
			REP(j,0,c){
				if(um[i*c + j]==false){
					start_cycle = i*c + j;
					curr_index = i*c + j;
					cr = i;
					cc = j;
					value = arr[cr][cc];
					flag = 1;
					break;
				}
			}
			if(flag==1)
				break;
		}
	}
}
int main()
{
	int r,c;
	cin>>r>>c;
	int** arr = new int*[r];
	REP(i,0,r){
		arr[i] = new int[c];
		REP(j,0,c){
			cin>>arr[i][j];
		}
	}
	cout<<endl;
	transpose(arr,r,c);	
	if(r < c){
		REP(i,0,r){
			REP(j,0,c){
				cout<<arr[i][j]<<" ";
				if((i*c+j+1) % r == 0)
					cout<<endl;
			}
		}
	}
	else if(r > c){
		REP(i,0,r){
			REP(j,0,c){
				cout<<arr[i][j]<<" ";
				if((i*c+j+1) % r == 0)
					cout<<endl;
			}
		}
	}
	else {
		REP(i,0,r){
			REP(j,0,c){
				cout<<arr[i][j]<<" ";
			}
			cout<<endl;
		}	
	}
	return 0;
}