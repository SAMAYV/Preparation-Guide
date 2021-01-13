// https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/maximal-subsequence-c9f19b0a/description/

ll const maxn = 26;
ll arr[maxn];
bool compare(ll a,ll b){
	if(arr[a] == arr[b]) return a < b;
	return arr[a] > arr[b];
}
int main()
{
    i_os;
	ll t;
	cin>>t;
	while(t--){
		ll n,k;
		cin>>n>>k;
		string s;
		cin>>s;
		ll order[26];
		REP(i,0,26){
			cin>>arr[i];
			order[i] = i;
		}
		sort(order,order+maxn,compare);
		vector<ll> temp[26];
		REP(i,0,n){
			temp[s[i]-'a'].push_back(i);
		}
		set<ll> mark;
		REP(i,0,26){
			REP(j,0,temp[order[i]].size()){
				if(temp[order[i]].size() - j <= k){
					mark.insert(temp[order[i]][j]);
					k--;
				}
				else if(k > 0) {
					auto it = mark.lower_bound(temp[order[i]][j]);
					if(it != mark.end() && order[i] < s[*it]-'a'){
						k--;
						mark.insert(temp[order[i]][j]);
					}
				}
			}
		}
		for(auto it:mark){
			cout<<s[it];
		}
		cout<<endl;
	}
    return 0;
}