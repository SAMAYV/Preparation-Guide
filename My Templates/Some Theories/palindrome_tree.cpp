Claim ->    Given, a string of size N,
            Number of distinct palindromes in a string is atmost N.

Proof ->    By Induction, on the length of the string 
            for length = 1, ans is 1
            Let for length = i, ans <= i
            if s[i+1] is appended to the previous string,
            then either s[i+1] has either occured earlier or Not.
            if Not, then length = i+1, ans <= i+1
            Else, we check for the 
