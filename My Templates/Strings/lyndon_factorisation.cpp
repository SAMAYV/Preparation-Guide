vector<string> duval(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    // i points to the beginning of s2
    // j points to the beginning of s3
    // k points to the current character that we are currently comparing to

    // s=s1s2s3 , where the Lyndon factorization for s1 is already found and finalized, 
    // the string s2 is pre-simple (and we know the length of the simple string in it), and s3 is completely untouched
    
    // In each iteration the Duval algorithm takes the first character of the string s3 and tries to append it to the string s2. 
    // It s2 is no longer pre-simple, then the Lyndon factorization for some part of s2 becomes known, and this part goes to s1.

    while(i < n){
        ll j = i + 1, k = i;
        while(j < n && s[k] <= s[j]){
            if(s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while(i <= k){
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}