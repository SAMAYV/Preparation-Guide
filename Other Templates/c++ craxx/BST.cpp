#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
#define ll long long
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define vll vector<long long>
struct node
{
    int data;
    node *left;
    node *right;
};

node *newNode(int item)
{
    node *temp = new node;
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(node *root)
{
    if (root)
    {
        inorder(root->left);       //Go to left subtree
        printf("%d ", root->data); //Printf root->data
        inorder(root->right);      //Go to right subtree
    }
}
node *insert(node *root, int data)
{
    if (root == NULL) //If the tree is empty, return a new,single node
        return newNode(data);
    else
    {
        //Otherwise, recur down the tree
        if (data <= root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
        //return the (unchanged) root pointer
        return root;
    }
}
node *successor(node *node_1)
{
    node * current = node_1;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
node *deleteNode(node *root, int key)
{
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = successor(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
int main()
{
    node *root = NULL;
    int t;
    cin >> t;
    cout << "Enter 1 to insert:\n";
    cout << "Enter 2 to delete: \n";
    cout << "Enter 3 to print inorder:\n";
    while (t--)
    {
        int a;
        cin >> a;
        if (a == 1)
        {
            int b;
            cin >> b;
            root = insert(root, b);
        }
        else if (a == 2)
        {
            int b;
            cin >> b;
            root = deleteNode(root, b);
        }
        else
        {
            inorder(root);
        }
    }
}