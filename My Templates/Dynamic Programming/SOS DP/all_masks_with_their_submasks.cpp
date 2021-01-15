int main()
{   
    for(ll m = 0; m < (1LL << n); ++m){
        for(ll s = m; s; s = (s - 1) & m){
            //... s and m ...
        }
    }
    /*
    Let's prove that the inner loop will execute a total of O(3^n) iterations.
    First proof: Consider the i-th bit. There are exactly three options for it:
    it is not included in the mask m (and therefore not included in submask s),
    it is included in m, but not included in s, or
    it is included in both m and s.
    As there are a total of n bits, there will be 3^n different combinations.
    */
    return 0;
}   
    