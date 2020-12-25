/*According to Ancient Ninjas , string making is an art form . There are various methods of string making , one of them uses previously generated strings to make the new one . Suppose you have two strings A and B , to generate a new string C , you can pick a subsequence of characters from A and a subsequence of characters from B and then merge these two subsequences to form the new string.
Though while merging the two subsequences you can not change the relative order of individual subsequences. What this means is - suppose there two characters Ai and Aj in the subsequence chosen from A , where i < j , then after merging if i acquires position k and j acquires p then k<p should be true and the same apply for subsequence from C.
Given string A , B , C can you count the number of ways to form string C from the two strings A and B by the method described above. Two ways are different if any of the chosen subsequence is different .
As the answer could be large so return it after modulo 10^9+7 .*/
#define ll long long
int mod = 1e9 + 7;
int solve(string a,string b,string c)
{
	int a1 = a.size();
    int b1 = b.size();
    int c1 = c.size();
    ll*** dp = new ll**[c1+1];
    for(int i=0;i<c1+1;i++){
        dp[i] = new ll*[a1+1];
        for(int j=0;j<a1+1;j++)
            dp[i][j] = new ll[b1+1]();
    }
    for(int i=0;i<a1+1;i++){
        for(int j=0;j<b1+1;j++)
            dp[0][i][j] = 1;
    }
    for(int i=1;i<c1+1;i++){
        for(int j=0;j<a1+1;j++){
            for(int k=0;k<b1+1;k++){
                if(i > j+k)
                    dp[i][j][k] = 0;
                // a has j length and b has k length and c has i length
                char ch = c[i-1];
                for(int l=j;l>0;l--){
                    if(a[l-1]==ch)
                        dp[i][j][k] = (dp[i][j][k] + dp[i-1][l-1][k]) % mod;
                }
                for(int l=k;l>0;l--){
                    if(b[l-1]==ch)
                        dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][l-1]) % mod;
                }
            }
        }
    }
    return dp[c1][a1][b1];
    
}