vector<ll> sort_cyclic_shifts(string const& s,vector<vector<ll>>& c){
    ll n = s.size(), alphabet = 256;

    // p[i] stores the index from which suffix string starts and suffix strings of 2^h length are in increasing order
    vector<ll> p(n);
    // c[i] stores the equivalence class of the string starting at index i  
    // cnt[i] stores the number of strings having equivalence class as i
    vector<ll> cnt(max(alphabet,n),0);

    REP(i,0,n){
        cnt[s[i]]++;
    }
    REP(i,1,alphabet){
        cnt[i] += cnt[i-1];
    }
    REP(i,0,n){
        p[--cnt[s[i]]] = i;
    }
    c[0][p[0]] = 0;
    ll classes = 1;
    REP(i,1,n){
        if(s[p[i]] != s[p[i-1]])
            classes++;
        c[0][p[i]] = classes - 1;
    }

    vector<ll> pn(n);
    for(ll h = 0; (1LL << h) < n; ++h){
        REP(i,0,n){
            pn[i] = p[i] - (1LL << h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        REP(i,0,n){
            cnt[c[h][pn[i]]]++;
        }
        REP(i,1,classes){
            cnt[i] += cnt[i-1];
        }
        REPI(i,0,n){
            p[--cnt[c[h][pn[i]]]] = pn[i];
        }
        c[h+1][p[0]] = 0;
        classes = 1;
        REP(i,1,n){
            pair<ll,ll> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
            pair<ll,ll> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1 << h)) % n]};
            if(cur != prev)
                ++classes;
            c[h+1][p[i]] = classes - 1;
        }
    }
    return p;
}

vector<ll> suffix_array_construction(string s,vector<vector<ll>>& c){
    s += "$";
    ll n = s.size();
    c.resize(20,vector<ll>(n,0));
    vector<ll> sorted_shifts = sort_cyclic_shifts(s,c);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

ll compare(ll i,ll j,ll l,ll k,vector<vector<ll>>& c){
    pair<ll,ll> a = {c[k][i], c[k][(i + l - (1 << k)) % n]};
    pair<ll,ll> b = {c[k][j], c[k][(j + l - (1 << k)) % n]};
    return (a == b) ? 0 : ((a < b) ? -1 : 1);
}

vector<ll> compare_two_substrings(string s,vector<vector<ll>> queries){
	vector<vector<ll>> c;
	vector<ll> v = suffix_array_construction(s,c);
	vector<ll> ans;
	REP(i,0,queries.size()){
		ll k = 0;
		while(powl(k,2) <= queries[i][2]){
			k++;
		}
		k--;
		ans.push_back(compare(queries[i][0],queries[i][1],queries[i][2],k,c));
	}
	return ans; 
}