#include<bits/stdc++.h>
using namespace std;

void printNQueens(int **mat,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<mat[i][j]<<" ";
        }
    }
    cout<<endl;
}
bool ispossibleV(int** mat,int n,int row,int col){
    for(int i=n-1;i>=0;i--){
        if(mat[i][col]==1){
            return false;
        }
    }
    
    return true;
}
bool ispossibleD(int** mat,int n,int row,int col){
    
    for(int i=row-1,j=col-1;i>=0 && j>=0;i--,j--){
        if(mat[i][j]==1){
            return false;
        }
    }
    
    for(int i=row-1,j=col+1;i>=0 && j<n;i--,j++){
            if(mat[i][j]==1){
                return false;
        }
    }
    
    return true;
}
bool ispossible(int** mat,int n,int row,int col){
    
    return ispossibleV(mat,n,row,col) && ispossibleD(mat,n,row,col);
}
void placeNQueensHelper(int** mat,int n,int row){
    if(row==n){
        printNQueens(mat,n);
        return;
    }
    
    for(int i=0;i<n;i++){
        if(ispossible(mat,n,row,i))
        {
            mat[row][i]=1;
            placeNQueensHelper(mat,n,row+1);
            mat[row][i]=0;
        }
        
    }
    return;
}
void placeNQueens(int n){
    int **mat=new int*[n];
    for(int i=0;i<n;i++)
    {
        mat[i]=new int[n];
        for(int j=0;j<n;j++){
            mat[i][j]=0;
        }
    }
    
    placeNQueensHelper(mat,n,0);
}
int main(){
	int n;
	cin>>n;
	placeNQueens(n);
}