struct Query {
    ll L, R, idx;
};

struct subset {
	ll parent;
};

void initialise(subset* s,ll n){
	REP(i,0,n){
		s[i].parent = i;
	}
}

ll find(ll x,subset* s){
	if(s[x].parent == x)
		return x;
	s[x].parent = find(s[x].parent,s);
	return s[x].parent;
}

int main()
{
	// We are given an array a[] and we have to compute some minima in given segments of the array.
	// We will iterate over the array and when we are at the ith element we will answer all queries (L, R) with R == i. 
	// To do this efficiently we will keep a DSU using the first i elements with the following structure: 
	// the parent of an element is the next smaller element to the right of it. 
	// Then using this structure the answer to a query will be the a[find_set(L)], the smallest number to the right of L.
	// container[i] contains all queries with R == i.
	subset s[n];
	initialise(s,n);
	vector<ll> answer(q);

	stack<ll> st;
	REP(i,0,n){
    	while(st.size() && arr[st.top()] > arr[i]){
        	s[st.top()].parent = i;
        	st.pop();
    	}
    	st.push(i);
    	for(Query q : container[i]){
        	answer[q.idx] = arr[find(q.L,s)];
    	}
	}
	return 0;
}