lli lowerIndex(lli arr[],lli n,lli x) 
{ 
    int l = 0, h = n - 1; 
    while (l <= h) { 
        int mid = (l + h) / 2; 
        if (arr[mid] >= x) 
            h = mid - 1; 
        else
            l = mid + 1; 
    } 
    return l; 
} 
lli upperIndex(lli arr[],lli n,lli y) 
{ 
    int l = 0, h = n - 1; 
    while (l <= h) { 
        int mid = (l + h) / 2; 
        if (arr[mid] <= y) 
            l = mid + 1; 
        else
            h = mid - 1; 
    } 
    return h; 
} 
lli cir(lli arr[],lli n,lli x,lli y) 
{ 
    int count = 0; 
    count = upperIndex(arr, n, y) - lowerIndex(arr, n, x) + 1; 
    return count; 
} 