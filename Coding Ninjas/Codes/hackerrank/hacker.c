#include<stdio.h>
#include<string.h>
int main()
{
 char s[1000];
 scanf("%s",s);
 int n=strlen(s);
    int a[n];
    char b[n];
    b[0]=s[0];
    a[0]=1;
   for(int i=1;i<n;i++)
   {   int c=0;
       for(int j=0;j<i;j++)
       {
          if(s[i]==s[j])
            c=1;
          if(c==1)
            break;
       }
       if(c==1)
        {
           int l=0;
           while(b[l]!=s[i])
            l++;
           a[l]++;
        }
       else
       {
           int j=strlen(b);
           b[j]=s[i];
           a[j]=1;
       }
   }
   int k=0;    
   int ct=0;
   while(a[k])
   {
       if(a[k]%2==1)
        ct++;
       if(ct>1)
        break;
   }
   if(ct==1)
    printf("YES");
   else printf("NO");
 return 0;
}
