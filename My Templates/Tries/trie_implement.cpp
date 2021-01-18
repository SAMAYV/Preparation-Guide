ll const k = 26;

class TrieNode {
    ll val;
    vector<TrieNode*> arr;
    TrieNode(){
        val = 0;
        arr.resize(k,NULL);
    }
};

void insert(TrieNode* root,ll prexor)
{
    TrieNode* curr = root;
    REPI(i,0,60){
        if((prexor >> i) & 1){
            if(curr->arr[1]){
                curr = curr->arr[1];
            }
            else {
                curr->arr[1] = new TrieNode();
                curr = curr->arr[1];
            }
        }
        else {
            if(curr->arr[0]){
                curr = curr->arr[0];
            }
            else {
                curr->arr[0] = new TrieNode();
                curr = curr->arr[0];
            }
        }
    }
    curr->val = prexor;
}

// calc element having min xor with prexor
ll query(TrieNode* root,ll prexor)
{
    TrieNode* curr = root;
    REPI(i,0,n){
        ll a = ((prexor >> i) & 1);
        if(node->arr[a]){
            node = node->arr[a];
        }
        else if(node->arr[1 - a]){
            node = node->arr[1 - a];
        }
    }
    return (prexor^(curr->val));
}
