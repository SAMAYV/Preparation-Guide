void manacher_algorithm(string s)
{
	// i is the index of the center letter of the current palindrome.
	// if i exceeds r, k is initialized to 1, as a single letter is a palindrome in itself.
	// If the size of palindrome centered at i is x, then d2[i] stores (x+1)/2
	vector<ll> d1(n);
	for(ll i = 0, l = 0, r = -1; i < n; i++){
	    ll k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
	    while(i - k >= 0 && i + k < n && s[i - k] == s[i + k]){
	        k++;
	    }
	    d1[i] = k--;
	    if(i + k > r){
	        l = i - k;
	        r = i + k;
	    }
	}

	// Since an even palidrome will have two centers, i is the latter of the two center indices.
	// if i exceeds r, k is initialized to 0, as a single letter is not an even palindrome.
	// If the size of palindrome centered at i is x, then d2[i] stores x/2
	vector<ll> d2(n);
	for(ll i = 0, l = 0, r = -1; i < n; i++){
	    ll k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	    while(i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]){
	        k++;
	    }
	    d2[i] = k--;
	    if(i + k > r){
	        l = i - k - 1;
	        r = i + k ;
	    }
	}
}