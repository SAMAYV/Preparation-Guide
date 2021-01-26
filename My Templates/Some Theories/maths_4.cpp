Combinatorics:

-> nCr = number of subsets of size of r, from a set of size n. 
    Use dp to calculate nCr.
    nCr = (n-1)C(r-1)+(n-1)Cr.

-> Catalan Numbers:
    Cat(n) = ((2*n)Cn)/(n+1)
    Find Cat(n) using dp.
    Cat(m) = ((2*m)*(2*m-1)/((m+1)*m))*Cat(m-1) 

    Applications:
        -> Cat(n) counts the number of distinct binary trees with n vertices.
        -> Cat(n) counts the number of expressions containing n pairs of
            parentheses correctly matched.
        -> Cat(n) counts number of different ways (n+1) factors can be 
            completely parenthesized. 
        -> Cat(n) counts the number of ways a convex polygon with 
            n+2 sides can be triangulated.
        -> Cat(n) counts the number of monotonic paths in a nxn grid.

-> Inclusion-Exclusion:


-> Dearrangement:
    Number of ways of distributing balls in boxes such that no ball,
    goes to its original box.
    Using inclusion-exclusion principle, solve.
    Follows the recursion,
    f(1) = 0;
    f(2) = 1;
    f(n) = (n-1)(f(n-2)+f(n-1)), otherwise. 

-> Prufer Code:
    Sequence of n-2 numbers that describes a labelled tree.
-> Cayleys formula:
    The number of labelled trees of n nodes equals n^(n-2).

-> Stirling Numbers:

-> Burnside Lemma:



