ll const block_size = 500;

struct Query {
    ll l, r, idx;
    bool operator <(const Query& n) const {
        ll p1 = (l/sz);
        ll p2 = (n.l/sz);
        if(p1 == p2){
            if(p1 & 1){
                return r > n.r;
            }
            else {
                return r < n.r;
            }
        }
        return p1 < p2;
    }
};

vector<ll> mo_s_algorithm(vector<Query>& queries,ll n){
    vector<ll> answers(queries.size());
    sort(queries.begin(),queries.end());

    ll cur_l = 0, cur_r = -1;

    for(Query q : queries){
        while(cur_l > q.l){
            cur_l--;
            add(cur_l);
        }
        while(cur_r < q.r){
            cur_r++;
            add(cur_r);
        }
        while(cur_l < q.l){
            remove(cur_l);
            cur_l++;
        }
        while(cur_r > q.r){
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

/*

We do O((n/S)∗n + S∗q) with S = n/sqrt(q) we get O(n∗sqrt(q)) and that's really good. 
Sorting all queries will take O(QlogQ).
How about the other operations? How many times will the add and remove be called?
Let's say the block size is S.
If we only look at all queries having the left index in the same block, the queries are sorted by the right index. Therefore we will call add(cur_r) and remove(cur_r) only O(N)
times for all these queries combined. This gives O(N/S*N)calls for all blocks.
The value of cur_l can change by at most O(S) during between two queries. Therefore we have an additional O(SQ) calls of add(cur_l) and remove(cur_l).

*/ 
    