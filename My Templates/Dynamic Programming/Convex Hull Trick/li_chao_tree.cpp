// You're given a set S containing function of the same "type" (ex. lines, y=ax+b). The type of function need to have the transcending 
// property. You need to handle two type of queries:
// 1. Add a function to S
// 2. Answer the maximum/minimum value at x=t considering all functions in S

// A type of function has transcending property if:
// Given two functions f(x),g(x) of that type, if f(t) is greater than/smaller than g(t) for some x=t, then f(x) will be greater 
// than/smaller than g(x) for x>t. In other words, once f(x) "win/lose" g(x), f(x) will continue to "win/lose" g(x).

// On every node of the segment tree, we store the line that maximize(or minimize) the value of the middle i.e. 
// if the interval of the node is [L,R), then the line stored on it maximize(or minimize) L+R/2.

const ll C = 1e5 + 5;

struct Line {
	ld m, b;
  	ld operator()(ld x){ 
  		return m*x + b; 
  	}
} a[4 * C];

// for maximum value of function
void insert(ll l,ll r,Line seg,ll treenode = 1){
  	if(l + 1 == r){
    	if(seg(l) > a[treenode](l)) a[treenode] = seg;
    	return;
  	}
  	ll mid = (l + r) / 2;
  	if(a[treenode].m > seg.m){
  		swap(a[treenode], seg);	
  	} 
  	if(a[treenode](mid) < seg(mid)){
    	swap(a[treenode], seg);
    	insert(l, mid, seg, 2*treenode);
  	}
  	else {
  		insert(mid, r, seg, 2*treenode + 1);
  	}
}

ld query(ll l,ll r,ll x,ll treenode = 1){
  	if(l + 1 == r){
  		return a[treenode](x);
  	} 
  	ll mid = (l + r) / 2;
  	if(x < mid){
  		return max(a[treenode](x), query(l, mid, x, lson));
  	} 
  	else {
  		return max(a[treenode](x), query(mid, r, x, rson));	
  	} 
}