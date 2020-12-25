#include<bits/stdc++.h>
using namespace std;
bool search(int** a,int& i,int& j){
	for(int w=0;w<9;w++){
		for(int e=0;e<9;e++){
			if(a[w][e]==0){
				i = w;
				j = e;
				return true;
			}
		}
	}
	return false;
}
bool row(int** a,int i,int j,int k){
	for(int r=0;r<9;r++){
		if(a[i][r]==k)
			return false;
	}
	return true;
}
bool col(int** a,int i,int j,int k){
	for(int r=0;r<9;r++){
		if(a[r][j]==k)
			return false;
	}
	return true;
}
bool block(int** a,int i,int j,int k){
	int r = i - i%3;
	int c = j - j%3;
	for(int m=0;m<3;m++){
		for(int n=0;n<3;n++){
			if(a[m+r][n+c]==k)
				return false;
		}
	}
	return true;
}

bool isvalid(int k,int** a,int i,int j){
	return row(a,i,j,k) && col(a,i,j,k) && block(a,i,j,k);
}
bool sudoku(int** a){
	int i,j;
	if(!search(a,i,j))
		return true;
	for(int k=1;k<10;k++)
	{
		if(isvalid(k,a,i,j))
		{
			a[i][j] = k;
			if(sudoku(a))
				return true;
			a[i][j] = 0;
		}
	}		
	return false;				
}
int main(){

	int** a = new int*[9];
	for(int i=0;i<9;i++){
		a[i] = new int[9]; 
	}
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cin>>a[i][j];
		}
	}
	if(sudoku(a))
		cout<<"true";
	else
		cout<<"false";
	return 0;
}