->  Eulers Totient function:
    Phi(n) = Number of numbers less than n, that are co-prime to n.
    Phi(n) = Product of(1-(1/p)) for all distinct primes.
    Phi(n) = n-1, if n is prime.


->  Read Modular exponentiation. 
    If x^n
    Time complexity = O(logn)

->  Fermats Little Theorem.
    (x^(p-1))mod p = 1, where x and p are co-prime, p is prime. 

->  Eulers Theorem.
    Let Phi(n) = number of numbers less than n, which are co-prime to n. 
    (x^(Phi(m))) mod m = 1, where x and m are co-prime. 
    Fermats Little theorem is a generalization, where m is prime. 

->  Modular Inverse. 
    Let a be the inverse of x(mod m).
    Then (a*x)mod m = 1.
    a exists iff gcd(x, m) = 1
    a can be found out to be x^(Phi(m)-1). 

