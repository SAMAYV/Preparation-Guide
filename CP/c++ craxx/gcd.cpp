int gcd(int a, int b) 
{ //Eucildean algo
    if (b == 0) 
        return a; 
    return gcd(b, a % b);       
} 