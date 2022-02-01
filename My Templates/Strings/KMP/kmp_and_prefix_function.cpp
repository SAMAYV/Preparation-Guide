// pi[i] stores length of longest prefix which is also a suffix of the string ending at index i
// This is an online algorithm, i.e. it processes the data as it arrives

vector<ll> prefix_function(string s) 
{
    ll n = s.length();
    vector<ll> pi(n,0);
    REP(i,1,n){
        ll j = pi[i-1];
        while(j > 0 && s[i] != s[j]){
            j = pi[j-1];
        }
        if(s[i] == s[j]){
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

// We generate the string s+#+t, where # is a separator that appears neither in s nor in t. Let us calculate the prefix function for this string. 
// Thus if at some position i we have π[i]=n, then at the position i−(n+1)−n+1=i−2n in the string t the string s appears.

vector<ll> KMP(string patt,string text){
    string c = patt + "#" + text;
    vector<ll> v = prefix_function(c);
    vector<ll> indices;
    REP(i,patt.size()+1,c.size()){
        if(v[i] == patt.size()){
            indices.push_back(i - (patt.size()+1) - patt.size()+1);
        }
    }
    return indices;
}

vector<ll> KMP(string patt,string text){
    vector<ll> v = prefix_function(patt);
    ll j = 0;
    ll n = text.size();

    // arr[i] stores length of longest suffix of text ending at index i which is also a prefix of string patt
    vector<ll> arr(n,0);
    REP(i,0,n+1){
        if(j == patt.size()){
            j = v[j-1];
        }
        if(i == n){
            break;
        }
        if(text[i] == patt[j]){
            j++;
            arr[i] = j;
        }
        else {
            while(j > 0){
                j = v[j-1];
                if(patt[j] == text[i]){
                    j++;
                    arr[i] = j;
                    break;
                }
            }
        }
    }
    return arr;
}