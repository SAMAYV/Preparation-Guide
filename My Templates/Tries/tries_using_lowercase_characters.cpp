/*

Pradyumn is tired of using auto - correct feature in his smartphone. He needs to correct his auto - correct more times than the auto - 
correct corrects him. Pradyumn is thinking to make his own app for mobile which will restrict auto - correct feature, instead it will 
provide auto - completion. Whenever Pradyumn types factorial, auto - correct changes it to fact. Pradyumn's App will show options such 
as fact, factorial, factory. Now, he can chose from any of these options. As Pradyumn is busy with his front - end work of his App. 
He asks you to help him. He said "You will be given set of words(words may repeat too but counted as one only). Now, as user starts the 
app, he will make queries(in lowercase letters only). So, you have to print all the words of dictionary which have the prefix same as 
given by user as input. And if no such words are available, add this word to your dictionary." As you know, Pradyumn want this app to 
be as smart as him :P So, implement a program for him such that he can release it on Fun Store.

INPUT CONSTRAINTS
1≤N≤30000
sum(len(string[i]))≤2∗10^5
1≤Q≤10^3

INPUT FORMAT
Single integer N which denotes the size of words which are input as dictionary
N lines of input, where each line is a string of consisting lowercase letter
Single integer Q which denotes the number of queries.
Q number of lines describing the query string on each line given by user

OUTPUT FORMAT
If auto - completions exists, output all of them in lexicographical order else output "No suggestions" without quotes
NOTE: All strings are lowercase

SAMPLE INPUT
3
fact
factorial
factory
2
fact
pradyumn

SAMPLE OUTPUT
fact
factorial
factory
No suggestions

*/

class trie {
    public:
    bool leaf;
    trie** children;
    trie(){
        this->leaf = false;
        this->children = new trie*[26];
        for(int i=0;i<26;i++)
            children[i] = NULL;
    }
};

void insert(trie* root,string s,int index){
    if(s.length()==index){
        root->leaf = true;
        return;    
    }
    int i = s[index] - 'a';
    if(root->children[i]){
        insert(root->children[i],s,index+1);
    }
    else {
        root->children[i] = new trie();
        insert(root->children[i],s,index+1);
    }
}

void print(trie* root,string out){
    if(root->leaf){
        cout<<out<<endl;
    }
    for(int i=0;i<26;i++){
        char t = i + 'a';
        if(root->children[i])
            print(root->children[i],out + t);
    }
}
int search(trie* root,string s,int index,string out){
    if(s.length()==index){
        print(root,out);
        return 0;
    }
    int i = s[index] - 'a';
    if(root->children[i]){
        out += s[index];
        return search(root->children[i],s,index+1,out);
    }
    else {
        return -1;
    }
}
int main()
{
    int n;
    cin>>n;
    trie* root = new trie();
    while(n--){
        string s;
        cin>>s;
        insert(root,s,0);
    }
    int q;
    cin>>q;
    while(q--){
        string s;
        cin>>s;
        if(search(root,s,0,"")==-1){
            cout<<"No suggestions"<<endl;
            insert(root,s,0);
        }
    }
    return 0;
}
