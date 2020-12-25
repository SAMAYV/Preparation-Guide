class trie {
    public:
    bool leaf;
    trie** children;
    trie() {
        this->leaf = false;
        this->children = new trie*[26];
        for(int i=0;i<26;i++)
            children[i] = NULL;
    }
};
void insert(trie* root,string s,int index){
    if(s.size() == index){
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
int search(trie* root,string s,int index){
    if(s.size() == index){
        return 1;
    }
    int i = s[index] - 'a';
    if(root->children[i]){
        return search(root->children[i],s,index+1);
    }
    else {
        return 0;
    }
}
bool compare(string a,string b){
	return a.size() > b.size();
}
int main()
{
	int n;
	cin>>n;
	string arr[n];
	for(int i=0;i<n;i++) cin>>arr[i];
	sort(arr,arr+n,compare);

	for(int i=0;i<n;i++){
		string p;
		p = arr[i];
		reverse(p.begin(),p.end());
		if(arr[i] == p){
			cout<<"true"<<endl;
			return 0;
		}
	}

	trie* root = new trie();
	for(int i=0;i<n;i++){
		if(search(root,arr[i],0)){
			cout<<"true"<<endl;
			return 0;
		}
		else {
			string p;
			p = arr[i];
			reverse(p.begin(),p.end());
			insert(root,p,0);
			insert(root,p.substr(1),0); // i will come after
		}
	}
	trie* root1 = new trie();
	for(int i=0;i<n;i++){
		if(search(root1,arr[i],0)){
			cout<<"true"<<endl;
			return 0;
		}
		else {
			string p;
			p = arr[i];
			reverse(p.begin(),p.end());
			insert(root1,p,0);
			insert(root1,p.substr(0,p.size()-1),0); // i will come before 
		}
	}
	return 0;
}