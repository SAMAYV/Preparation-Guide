// A suffix array will contain integers that represent the starting indexes of the all the suffixes of a given string, after the aforementioned suffixes are sorted.

vector<ll> sort_cyclic_shifts(string const& s){
    ll n = s.size(), alphabet = 256;

    // p[i] stores the index from which suffix string starts and suffix strings of 2^h length are in increasing order
    vector<ll> p(n);
    // c[i] stores the equivalence class of the string starting at index i 
    vector<ll> c(n); 
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
    c[p[0]] = 0;
    ll classes = 1;
    REP(i,1,n){
        if(s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vector<ll> pn(n), cn(n);
    for(ll h = 0; (1LL << h) < n; ++h){
        REP(i,0,n){
            pn[i] = p[i] - (1LL << h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        REP(i,0,n){
            cnt[c[pn[i]]]++;
        }
        REP(i,1,classes){
            cnt[i] += cnt[i-1];
        }
        REPI(i,0,n){
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        REP(i,1,n){
            pair<ll,ll> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<ll,ll> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if(cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<ll> suffix_array_construction(string s){
    s += "$";
    vector<ll> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

// The algorithm requires O(nlogn) time and O(n) memory. However if we take the size of the alphabet k 
// into account, then it uses O((n+k)logn) time and O(n+k) memory.

// For simplicity we used the complete ASCII range as alphabet. If we know that the string only contains a subset of characters, 
// e.g. only lowercase letters, then this implementation can obviously be optimized. However not by much, since the alphabet 
// size only appears with a factor of O(logn) in the complexity.
