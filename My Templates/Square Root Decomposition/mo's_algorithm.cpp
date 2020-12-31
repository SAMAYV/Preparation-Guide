ll const block_size = 1000;

struct Query {
    ll l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

bool cmp(Query p,Query q) {
    if((p.l / block_size) != (q.l / block_size))
        return p < q;
    return ((p.l / block_size) & 1) ? (p.r < q.r) : (p.r > q.r);
}

vector<ll> mo_s_algorithm(vector<Query> queries) {
    vector<ll> answers(queries.size());
    sort(queries.begin(), queries.end(), cmp);

    ll cur_l = 0, cur_r = -1;

    for(Query q : queries) {
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

int main()
{   

    return 0;
}   
    