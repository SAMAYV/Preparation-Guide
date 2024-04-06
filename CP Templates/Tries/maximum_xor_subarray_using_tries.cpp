class Trienode {
    public:
    Trienode* left;
    Trienode* right;
};

void insert(ll val,Trienode* root){
    Trienode* curr = root;
    REPI(i,0,60){
        ll b = ((val >> i) & 1);
        if(b == 0){
            if(!curr->left)
                curr->left = new Trienode();
            curr = curr->left;
        }
        else {
            if(!curr->right)
                curr->right = new Trienode();
            curr = curr->right;
        }
    }
}

ll query(ll val,Trienode* root){
    Trienode* curr = root;
    ll curr_xor = 0;
    REPI(i,0,60){
        ll b = ((val >> i) & 1);
        if(b == 0){
            if(curr->right){
                curr_xor += (1 << i);
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }
        else {
            if(curr->left){
                curr_xor += (1 << i);
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
    }
    return curr_xor;
}

ll maxor(ll* a,ll n,Trienode* root){
    ll x[n];
    x[0] = a[0];
    insert(a[0],root);
    ll maxor = a[0];
    REP(i,1,n){
        x[i] = (x[i-1] ^ a[i]);
        insert(x[i],root);
        ll curr_xor = query(x[i],root);
        if(curr_xor < x[i])
            curr_xor = x[i];
        if(maxor < curr_xor)
            maxor = curr_xor;
    }
    return maxor;
}

int main() 
{
    ll n;
    cin>>n;
    ll a[n];
    REP(i,0,n) cin>>a[i];
    Trienode* root = new Trienode();
	cout<<maxor(a,n,root)<<endl;
	return 0;
}