// Here's the implementation, the vectors being represented by bitmasks of length d:

// Let, f(v) be the first position in the vector's binary representation, where the bit is set. We make sure that all the basis vectors each have a different f value.

ll basis[d]; 	// basis[i] keeps the mask of the vector whose f value is i
ll sz; 			// Current size of the basis

void insertVector(ll mask)
{
	REP(i,0,d)
	{
		if(((mask >> i) & 1) == 0){
			continue;
		}  
		// If there is no basis vector with the i'th bit set, then insert this vector into the basis
		if(!basis[i]){ 
			basis[i] = mask;
			++sz;	
			return;
		}
		mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
	}
}