lli bins(lli arr[],lli l,lli r,lli x) 
{ 
    if (r >= l) { 
        lli mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid; 
        if (arr[mid] > x) 
            return bins(arr, l, mid - 1, x);
        return bins(arr, mid + 1, r, x); 
    } 
    return -1; 
} 