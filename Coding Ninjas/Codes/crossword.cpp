#include<bits/stdc++.h>
using namespace std;

bool ispossible_row(char** a,int i,int j,string* cross,int index){
    int count = 1;
    for(int k=j+1;k<10;k++){
        if(a[i][k]=='+')
            return false;
        else if(a[i][k]=='-' || a[i][k]==cross[index][k-j])
            count+=1;
        if(count==cross[index].size())
            return true;
    }
    return false;
}
bool ispossible_col(char** a,int i,int j,string* cross,int index){
    int count = 1;
    for(int k=i+1;k<10;k++){
        if(a[k][j]=='+')
            return false;
        else if(a[k][j]=='-' || a[k][j]==cross[index][k-i])
            count+=1;
        if(count==cross[index].size())
            return true;
    }
    return false;
}
void setrow(char** a,int i,int j,string* cross,int index,bool* b){
    for(int k=0;k<cross[index].size();k++){
        if(a[i][k+j]==cross[index][k])
            b[k] = false;
        else {
            b[k] = true;
            a[i][k+j] = cross[index][k];
        }
    }
}
void setcol(char** a,int i,int j,string* cross,int index,bool* b){
    for(int k=0;k<cross[index].size();k++){
        if(a[k+i][j]==cross[index][k])
            b[k] = false;
        else {
            b[k] = true;
            a[i+k][j] = cross[index][k];
        }
    }
}
void resetrow(char** a,int i,int j,string* cross,int index,bool* b){
    for(int k=0;k<cross[index].size();k++){
        if(b[k]==true)
            a[i][k+j] = '-';
    }    
}
void resetcol(char** a,int i,int j,string* cross,int index,bool* b){
    for(int k=0;k<cross[index].size();k++){
        if(b[k]==true)
            a[i+k][j] = '-';
    }    
}
void print(char** a){
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                cout<<a[i][j];
            }
         cout<<endl;
    }
}
bool crossword(char** a,string* cross,int size,int index){
    if(index==size){
        print(a);
        return true;
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(a[i][j]=='-' || a[i][j]==cross[index][0])
            {
                if(ispossible_row(a,i,j,cross,index)){
                    bool b[cross[index].size()];
                    setrow(a,i,j,cross,index,b);
                    if(crossword(a,cross,size,index+1)){
                        return true;
                    }
                    resetrow(a,i,j,cross,index,b);
                }
                if(ispossible_col(a,i,j,cross,index)){
                    bool b[cross[index].size()];
                    setcol(a,i,j,cross,index,b);
                    if(crossword(a,cross,size,index+1)){
                        return true;
                    }
                    resetcol(a,i,j,cross,index,b);
                }
            }
        }
    }
    return false;
}
int main() {

    char** a = new char*[10];
    for(int i=0;i<10;i++){
        a[i] = new char[10];
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cin>>a[i][j];
        }
    }
    string s,T;
    getline(cin,s);
    getline(cin,s);
    int count = 1;
    for(int i=0;i<s.length();i++){
        if(s[i]==';')
            count++;
    }
    stringstream X(s);
    string cross[count];
    int i=0;
    while(getline(X,T, ';')){
        cross[i] = T;
        i++;
    }
    // for(int i=0;i<count;i++)
    //     cout<<cross[i]<<endl;
    
    crossword(a,cross,count,0);
    
     
}