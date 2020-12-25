/*
Pair sum in a BST

Send Feedback
Given a binary search tree and an integer S, find pair of nodes in the BST which sum to S. You can use extra space only O(log n).
Assume BST contains all unique elements. Note: In a pair, print the smaller element first.

Input format:
Line 1: Elements in the level order form (separated by space)
(If any node does not have left or right child, take -1 in its place)
Line 2: S

Output format: Each pair in a different line (pair elements separated by space)

Sample Input :
8 5 10 2 6 -1 -1 -1 -1 -1 7 -1 -1
12

Sample Output
2 10
5 7
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

int noofnodes(BinaryTreeNode<int> *root){
    if(root==NULL)
        return 0;
    return noofnodes(root->left) + noofnodes(root->right) + 1;
}

void printNodesSumToS(BinaryTreeNode<int> *root,int s){
    stack<BinaryTreeNode<int> *> inorder;
    stack<BinaryTreeNode<int> *> revinorder;
    int count = 0;
    int n = noofnodes(root);
    BinaryTreeNode<int> *temp1 = root;
    
    while(temp1!=NULL){
        inorder.push(temp1);
        temp1 = temp1->left;
    }
    
    BinaryTreeNode<int> *temp2 = root;
    while(temp2!=NULL){
        revinorder.push(temp2);
        temp2 = temp2->right;
    }
    
    while(count<n-1)
    {
        BinaryTreeNode<int> *temp1 = inorder.top();
        BinaryTreeNode<int> *temp2 = revinorder.top();
        if(temp1->data + temp2->data > s){
            revinorder.pop();
            count+=1;
            temp2 = temp2->left;
            while(temp2!=NULL){
                revinorder.push(temp2);
                temp2 = temp2->right;
            }
        }
        else if(temp1->data + temp2->data == s){
            cout<<temp1->data<<" "<<temp2->data<<endl;
            revinorder.pop();
            count++;
            temp2 = temp2->left;
            while(temp2!=NULL){
                revinorder.push(temp2);
                temp2 = temp2->right;
            }
            inorder.pop();
            count+=1;
            temp1 = temp1->right;
            while(temp1!=NULL){
                inorder.push(temp1);
                temp1 = temp1->left;
            }            
        }
        else if(temp1->data + temp2->data < s){
            inorder.pop();
            count+=1;
            temp1 = temp1->right;
            while(temp1!=NULL){
                inorder.push(temp1);
                temp1 = temp1->left;
            }
        }
    }

}
int main()
{
	
	return 0;
}