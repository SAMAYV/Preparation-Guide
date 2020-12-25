int main()
{   
    // Finding the modular inverse for every number modulo m in O(m)
    // However for this specific algorithm we require that the modulus m is prime
    vector<ll> inv(m+1);
    inv[1] = 1; 
    REP(i,2,m+1){
        inv[i] = (m - (m/i)*inv[m % i]) % m;    
    }
    return 0;
}   
    