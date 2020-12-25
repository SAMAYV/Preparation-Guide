lli lps(char*x)
{
        lli n=strlen(x);
        lli l[n][n];
        for(int i=0;i<n;i++)
        {
                l[i][i]=1;
        }
        for(int len=2;len<=n;len++)
        {
         for(int i=0;i<n-len+1;i++)
         {
          int j=i+len-1;
          if(x[i]==x[j]&&len==2)
          l[i][j]=2;
          else if(x[i]==x[j])
          l[i][j]=l[i+1][j-1]+2;
          else
          l[i][j]=max(l[i][j-1],l[i+1][j]);
         }
        }
        return l[0][n-1];
}