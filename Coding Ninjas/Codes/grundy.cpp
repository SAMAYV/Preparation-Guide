/*Calculate the Grundy Number for the given 'n' in the game.
The game starts with a number- ‘n’ and the player to move divides the number- ‘n’ with 2, 3 or 6 and then takes the floor. 
If the integer becomes 0, it is removed. The last player to move wins. Which player wins the game?*/
#include<bits/stdc++.h>
using namespace std;
int grundy(int n){
    int* g = new int[n+1];
    g[0] = 0;
    for(int i=1;i<=n;i++){
        int* a = new int[10000]();
        a[g[i/2]] = 1;
        a[g[i/3]] = 1;
        a[g[i/6]] = 1;
        int j = 0;
        while(1){
            if(a[j]!=1)
                break;
            j++;
        }
        g[i] = j;
        delete [] a;
    }
    return g[n];
}
int main() {

	int n;
    cin>>n;
    cout<<grundy(n);
}