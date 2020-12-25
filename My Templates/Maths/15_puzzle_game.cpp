int main()
{
	int a[16];
	for (int i=0; i<16; ++i){
	    cin>>a[i];
	}

	int inv = 0;
	for(int i=0; i<16; ++i){
	    if(a[i]){
	        for(int j=0; j<i; ++j){
	            if(a[j] > a[i]){
	                ++inv;
	            }
	        }
	    }
	}
	for(int i=0; i<16; ++i){
	    if(a[i] == 0){
	        inv += 1 + i / 4;
	    }
	}
	if(inv & 1) cout<<"Sol exists\n";
	else "No Sol exists\n";
}