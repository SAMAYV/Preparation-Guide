    #include <cmath>
    #include <vector>
int allWays(int x, int n, vector<int> v) {
    if(x==0)
        return 1;

    int sum = 0;
    for(int i=1; i<=pow(x,1/n); i++)
    {
        int flag=0;
        for(auto it = v.begin();it!=v.end();it++){
            if(*it == i){
                flag = 1;
                break;
            }
        }
        if(flag==0){
            v.push_back(i);
            sum += allWays(x - pow(i,n), n, v);
        }
            
    }
    return sum;
}
int allWays(int x, int n) {
    /* Don't write main().
     * Don't read input, it is passed as function argument.
     * Return output and don't print it.
     * Taking input and printing output is handled automatically.
     */
    vector<int>v;
    return allWays(x,n,v);
}