/* Print nodes at distance k from node

Send Feedback
Given a binary tree, a node and an integer K, print nodes which are at K distance from the the given node.

Input format :
Line 1 : Elements in level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2 : Node
Line 3 : K

Output format : Answer nodes in different line

Sample Input :
5 6 10 2 3 -1 -1 -1 -1 -1 9 -1 -1
3
1

Sample Output :
9
6
*/

/*
class BinaryTreeNode {
    public : 
    T data;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;

    BinaryTreeNode(T data) {
        this -> data = data;
        left = NULL;
        right = NULL;
    }
};
*/

int lcaBinaryTree(BinaryTreeNode<int>* root,int val1,int val2){
    if(root == NULL){
        return -1;
    }
    if(root->data == val1 || root->data == val2){
        return root->data;
    }
    int v1 = lcaBinaryTree(root->left,val1,val2);
    int v2 = lcaBinaryTree(root->right,val1,val2);
    if(v1 != -1 && v2 != -1){
        return root->data;
    }
    else if(v1 == -1 && v2 != -1){
        return v2;
    }
    else if(v1 != -1 && v2 == -1){
        return v1;
    }
    else if(v1 == -1 && v2 == -1){
        return -1;
    }
}
int height(BinaryTreeNode<int> *root,int p){
    if(root == NULL){
        return -1;
    }
    if(root->data == p){
        return 0;
    }
    int l1 = height(root->left,p);
    int l2 = height(root->right,p);
    if(l1 == -1 && l2 == -1){
        return -1;
    }
    else if(l1 == -1 && l2 != -1){
        return l2 + 1;
    }
    else if(l1 != -1 && l2 == -1){
        return l1 + 1;
    } 
}
void nodes(BinaryTreeNode<int> *root,BinaryTreeNode<int> *temp,int k,int hnode,int node){
    if(temp == NULL){
        return;
    }
    nodes(root,temp->left,k,hnode,node);
    int d = temp->data;
    int h1 = height(root,d);
    int lca = lcaBinaryTree(root,d,node);
    int h2 = height(root,lca);
    if(hnode + h1 -2*h2 == k){
        cout<<d<<endl;
    }
    nodes(root,temp->right,k,hnode,node);
}
void nodesAtDistanceK(BinaryTreeNode<int> *root,int node,int k){
    int hnode = height(root,node);
    BinaryTreeNode<int> *temp = root;
    nodes(root,temp,k,hnode,node);
}

int main()
{
		
	return 0;
}