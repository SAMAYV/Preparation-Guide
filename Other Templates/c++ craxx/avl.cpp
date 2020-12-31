#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
#define N 998244353
#define ll long long
#define REP(i,a,b) for(ll i=a;i<b;i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vll vector<long long>
#define INF 1000000000
long long sum= -1;
int id=0;
struct Node{
    int key;
    int height;
    Node *left;
    Node *right;
    int val=0; //if to be used as a key->value pair.
};

int get_height(Node* curr){
    if(curr == NULL){
        return 0;
    }
    return curr->height;
}

int get_balance(Node *curr){
    if(curr==NULL){
        return 0;
    }
    return get_height(curr->left)-get_height(curr->right);
}

Node* create_node(int key, int val){
    Node *temp = new Node();
    temp->key=key;
    temp->height=1;
    temp->val=val;
    temp->left=NULL;
    temp->right=NULL;
    return (temp);
}

Node* left_left(Node* curr){
    Node* temp1 = curr->right;
    Node* temp2=temp1->left;
    curr->right= temp2;
    temp1->left=curr;

    curr->height=1+max(get_height(curr->left), get_height(curr->right));
    temp1->height=1+max(get_height(temp1->right), get_height(temp1->left));
    return temp1;
}
Node* right_right(Node* curr){
    Node* temp1 = curr->left;
    Node* temp2=temp1->right;
    curr->left= temp2;
    temp1->right=curr;

    curr->height=1+max(get_height(curr->left), get_height(curr->right));
    temp1->height=1+max(get_height(temp1->right), get_height(temp1->left));
    return temp1;

}
Node* insert_node(Node* temp, int key, int gg){
    if(temp == NULL){

        Node *tt = create_node(key, gg);
        if(tt->val > sum){id = key; sum=tt->val;}
        return create_node(key, gg);; 
    }
    if(key < temp->key){
        temp->left= insert_node(temp->left, key, gg);
    }else if(key > temp->key){
        temp->right=insert_node(temp->right, key, gg);
    }
    else{
        //cout<<temp->val<<endl;
        (temp->val) += gg;//use in case of key->value pair;
        if(temp->val > sum){id = key; sum=temp->val;}
        return temp;
    }
    temp->height = 1+max(get_height(temp->left), get_height(temp->right));
    int balance = get_balance(temp);
    // four cases of rotation.
    if(balance > 1 && key < temp->left->key){
        return right_right(temp);
    }
    if(balance > 1 && key > temp->left->key){
        temp->left = left_left(temp->left);
        return right_right(temp);
    }
    if(balance < -1 && key > temp->right->key){
        return left_left(temp);
    }
    if(balance < -1 && key < temp->right->key){
        temp->right=right_right(temp->right);
        return left_left(temp);
    }
    return temp;
}
int search(Node* root, int key){
    Node* temp=root;
    while(temp != NULL){
        if(key > temp->key){
            temp=temp->right;
        }
        else if(key < temp->key){
            temp=temp->left;
        }
        else if(key == temp->key){
            return temp->val;
        }
    }
    /*return temp->val*/  //if to return value for search of key->value pair.
    return 0;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Node* root = NULL;
    ll t;
    cin>>t;
    while(t--){
        int a;
        cin>>a;
        if(a==1){
            int b, c;
            cin>>b>>c;
            root = insert_node(root, b, c);
        }
        else if(a==3){
            int b;
            cin>>b;
            cout<<search(root, b)<<endl;
        }
        else{
            if(sum == -1){cout<<"No Data available.\n";}
            else{cout<<id<<endl;}
        }
    }
}