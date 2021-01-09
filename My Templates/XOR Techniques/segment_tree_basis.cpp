// https://www.hackerearth.com/problem/algorithm/chef-f59c8115/description/

ll const k = 26;
ll const maxn = 200005;
ll const mod = 1e9 + 7;

struct node {
	vector<ll> basis;
	ll sz = 0; 
	node(){
	    basis.resize(k,0);
	}
};
node t[4*maxn];

ll insertBasis(vector<ll>& basis,ll mask){
	REP(i,0,k){
		if(!(mask & (1 << i)))
			continue;
		if(!basis[i]){
			basis[i] = mask;
			return 1;
		}
		mask ^= basis[i]; 
	}
	return 0; 
}

node merge(node a, node b){
	node cur;
	if(a.sz < b.sz){
		swap(a,b);
	}
	cur = a; 
	REP(i,0,k){
		if(!b.basis[i]) continue;
		if(insertBasis(cur.basis,b.basis[i]))
			cur.sz++; 
	}
	return cur; 
}

node query(ll start,ll end,ll left,ll right,ll treenode){
    if(right < start || end < left){
        return node();
    }
    if(left <= start && right >= end){
        return t[treenode];
    }
    ll mid = (start + end)/2;
    node q1 = query(start,mid,left,right,2*treenode);
    node q2 = query(mid+1,end,left,right,2*treenode+1);
    return merge(q1,q2);    
}

void buildtree(ll start,ll end,ll treenode,ll* arr){
    if(start == end){
        if(insertBasis(t[treenode].basis, arr[start])){
        	t[treenode].sz++;	
        } 
        return;
    }
    ll mid = (start+end)/2;
    buildtree(start,mid,2*treenode,arr);
    buildtree(mid+1,end,2*treenode+1,arr);
    t[treenode] = merge(t[2*treenode],t[2*treenode + 1]);
}

void update(ll start,ll end,ll treenode,ll ind,ll val){
    if(ind < start || ind > end){
        return;
    }
    if(start == end){
        t[treenode].basis.clear(); 
        t[treenode].basis.resize(k,0); 
        t[treenode].sz = 0; 
		if(insertBasis(t[treenode].basis, val)){
			t[treenode].sz++;	
		}  
        return;
    }
    ll mid = (start + end)/2;
    update(start,mid,2*treenode,ind,val);
    update(mid+1,end,2*treenode+1,ind,val);
    t[treenode] = merge(t[2*treenode],t[2*treenode+1]);    
}

ll independent(vector<ll> basics,ll mask){
    return !insertBasis(basics, mask);
}

int main()
{
	i_os;
	ll n,q;
	cin>>n>>q;
	ll powers[n+1];
	powers[0] = 1;
	REP(i,1,n+1){
		powers[i] = (powers[i-1]*2) % mod;
	}
	ll arr[n];
	REP(i,0,n){
		string s;
		cin>>s;
		ll mask = 0;
		REP(j,0,s.size()){
			ll p = s[j]-'a';
			mask ^= (1 << p);
		}
		arr[i] = mask;
	}
	buildtree(0,n-1,1,arr);
	REP(i,0,q){
		ll t;
		cin>>t;
		if(t == 1){
			ll l;
			string s;
			cin>>l>>s;
			l--;
			ll mask = 0;
			REP(j,0,s.size()){
				ll p = s[j]-'a';
				mask ^= (1 << p);
			}
			arr[l] = mask;
			update(0,n-1,1,l,mask);
		}
		else {
			ll l,r;
			cin>>l>>r;
			l--; r--;
			node n1 = query(0,n-1,l,r,1);
			ll ans = 1;
			REP(i,0,k){
				if(independent(n1.basis,(1 << i))) ans++;
			}
			ans = ans*powers[r-l+1-n1.sz];
			ans--;
			ans += mod;
			ans %= mod;
			cout<<ans<<endl;
		}
	}
    return 0;
}
